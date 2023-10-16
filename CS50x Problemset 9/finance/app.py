import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # Get current logged user's name and ballance
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
    # Get current portfolio and create list to pass to table
    portfolio = db.execute("SELECT * FROM stocks WHERE owner = ?", user)
    tempData = []
    tableData = []
    stockValue = 0
    for stocks in portfolio:
        tempData.append(stocks["symbol"])
        tempData.append(stocks["amount"])
        query = lookup(stocks["symbol"])["price"]
        tempData.append(f"{query:,.2f}")
        queryTotal = float(lookup(stocks["symbol"])["price"])*int(stocks["amount"])
        tempData.append(f"{queryTotal:,.2f}")
        tableData.append(tempData)
        stockValue = stockValue + float(tempData[3])
        tempData = []
    totalValue = round(stockValue + cash, 2)
    totalValue = f"{totalValue:,.2f}"
    cash = f"{cash:,.2f}"
    return render_template("index.html", user=user, cash=cash, tableData=tableData, totalValue=totalValue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    symbol = request.form.get("symbol")
    shares = request.form.get("shares")
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Please enter share name!")
        elif symbol.isalpha() == False:
            return apology("Please enter valid stock symbol")
        elif lookup(request.form.get("symbol")) == None:
            return apology("Invalid Stock")
        elif not request.form.get("shares"):
            return apology("Please enter amount of shares!")
        elif shares.find("-") != -1:
            return apology("Shares must be a positve number")
        elif shares.find(".") != -1 or shares.find(",") != -1:
            return apology("Shares must be a postive integer")
        elif shares.isnumeric() == False:
            return apology("Shares must be an integer")
        else:
            # look up value of share and get total transaction value
            result = lookup(request.form.get("symbol"))
            symbol = request.form.get("symbol")
            shares = request.form.get("shares")
            buyValue = result["price"] * float(request.form.get("shares"))
            # get current user balance
            cash = db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"]
            newBalance = cash - buyValue
            # Check if user can afford purchase
            if newBalance >= 0:
                # Check if stock already in portfolio, if not create
                if len(db.execute("SELECT symbol FROM stocks WHERE symbol = ? AND owner = ?", symbol, user)) == 0:
                    db.execute("UPDATE users SET cash = ? WHERE username = ?", newBalance, user)
                    db.execute("INSERT INTO stocks (symbol, amount, owner) VALUES (?, ?, ?)", request.form.get("symbol"), request.form.get("shares"), user)
                    # Update History
                    db.execute("INSERT INTO history (type, symbol, price, owner, amount) VALUES (?, ?, ?, ?, ?)",
                                'buy', symbol, result["price"], user, shares)
                    return redirect("/")
                # Stock found so only update amount
                else:
                    currentAmount = db.execute("SELECT amount FROM stocks WHERE symbol = ? AND owner = ?",
                                                request.form.get("symbol"), user)
                    updatedAmount = (currentAmount[0])["amount"] + int(request.form.get("shares"))
                    db.execute("UPDATE stocks SET amount = ? WHERE symbol = ? AND owner = ?", updatedAmount, request.form.get("symbol"), user)
                    db.execute("UPDATE users SET cash = ? WHERE username = ?", newBalance, user)
                    # Update History
                    queryPrice = result["price"]
                    usdFormat = f"{queryPrice:,.2f}"
                    db.execute("INSERT INTO history (type, symbol, price, owner, amount) VALUES (?, ?, ?, ?, ?)",
                                'buy', symbol, usdFormat, user, shares)
                    return redirect("/")
            else:
                return apology("Not enough cash to complete transaction!")
    else:
        user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
        cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
        return render_template("buy.html", user=user, cash=cash)


@app.route("/history")
@login_required
def history():
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    userHistory = db.execute("SELECT * FROM history WHERE owner = ?", user)
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
    return render_template("history.html", userHistory=userHistory, cash=cash, user=user)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
        cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
        return render_template("quote.html", cash=cash, user=user)
    else:
        symbol = request.form.get("symbol")
        if not request.form.get("symbol"):
            return apology("Please enter a stock symbol")
        if symbol.isalpha() == False:
            return apology("Please enter valid stock symbol")
        if lookup(request.form.get("symbol")) == None:
            return apology("Invalid Stock")
        result = lookup(request.form.get("symbol"))
        name = result["name"]
        price = ('{:.2f}'.format(round(result["price"], 2)))
        symbol = result["symbol"]
        user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
        cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
        return render_template("quoted.html", name=name, price=price, symbol=symbol, cash=cash, user=user)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Check if a username has been entered
        if not request.form.get("username"):
            return apology("Please enter a username!")
        # Check if username already exists in database
        elif db.execute("SELECT username FROM users WHERE username = ?", request.form.get("username")):
            return apology("Username already taken!")
        # Check for empty password
        elif not request.form.get("password"):
            return apology("Please set a password")
        # Check if password and repeat match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Please confirm your password. No Match!")
        # Register User in database and print message
        else:
            success = "You have registered successfully"
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"),
                        generate_password_hash(request.form.get("password")))
            return render_template("register.html", success=success)
    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    if request.method == "POST":
        print(request.form.get("symbol"))
        if not request.form.get("symbol"):
            return apology("Please enter stock symbol")
        if not request.form.get("shares"):
            return apology("Please enter how many shares")
        symbol = request.form.get("symbol")
        sharesToSell = int(request.form.get("shares"))
        # Check if user has stock
        if len(db.execute("SELECT symbol FROM stocks WHERE symbol = ? AND owner = ?", symbol, user)) != 0:
            currentAmount = (db.execute("SELECT amount FROM stocks WHERE symbol = ? AND owner = ?", symbol, user))[0]["amount"]
            # Sell some stock
            if sharesToSell < currentAmount:
                db.execute("UPDATE stocks SET amount = ? WHERE symbol = ? AND owner = ?",
                            (currentAmount - sharesToSell), symbol, user)
                sellValue = (lookup(symbol))["price"]
                sellCash = float(sellValue) * sharesToSell
                newCash = float((db.execute("SELECT cash FROM users WHERE username = ?", user))[0]["cash"]) + sellCash
                db.execute("UPDATE users SET cash = ? WHERE username = ?", newCash, user)
                # Update History
                db.execute("INSERT INTO history (type, symbol, price, owner, amount) VALUES (?, ?, ?, ?, ?)",
                            'sell', symbol, sellValue, user, sharesToSell)
            # Sell all stock
            elif sharesToSell == currentAmount:
                sellValue = (lookup(symbol))["price"]
                sellCash = float(sellValue) * sharesToSell
                newCash = float((db.execute("SELECT cash FROM users WHERE username = ?", user))[0]["cash"]) + sellCash
                db.execute("UPDATE users SET cash = ? WHERE username = ?", newCash, user)
                db.execute("DELETE FROM stocks WHERE symbol = ? AND owner = ?", symbol, user)
                # Update History
                db.execute("INSERT INTO history (type, symbol, price, owner, amount) VALUES (?, ?, ?, ?, ?)",
                            'sell', symbol, sellValue, user, sharesToSell)
            # Not enough shares
            elif sharesToSell > currentAmount:
                return apology(f"You only have {currentAmount} shares")
        # No stock of that symbol
        else:
            return apology("Stock not in portfolio")
        # Return to index to see change in portfolio
        return redirect("/")
    else:
        user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
        cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
        stocks = db.execute("SELECT symbol FROM stocks WHERE owner = ?", user)
        return render_template("sell.html", cash=cash, user=user, stocks=stocks)


@app.route("/cash", methods=["GET", "POST"])
@login_required
def cash():
    user = db.execute("SELECT username FROM users WHERE id = ?", session["user_id"])[0]["username"]
    cash = round(db.execute("SELECT cash FROM users WHERE username = ?", user)[0]["cash"], 2)
    payments = db.execute("SELECT * FROM payments WHERE user = ?", user)
    if request.method == "POST":
        cashPayment = float(request.form.get("cash"))
        newCash = cash + cashPayment
        db.execute("UPDATE users SET cash = ? WHERE username = ?", newCash, user)
        db.execute("INSERT INTO payments (amount, user) VALUES (?, ?)", cashPayment, user)
        return redirect("/cash")
    else:
        return render_template("cash.html", cash=cash, user=user, payments=payments)