# Get User Input and check for correc entry
while True:
    try:
        userCard = int(input("Number: "))
    except ValueError:
        userCard = int(input("Number: "))
    break

# Convert credit card number to str to make iterable
userCard = str(userCard)

# Create list of digits in credit card number
digitList = []
for digit in userCard:
    digitList.append(int(digit))

# Luhn's Algorithm
sum1 = 0
i = -2
while i >= 0 - len(digitList):
    product = digitList[i] * 2
    if product >= 10:
        product = str(product)
        sum1 = sum1 + int(product[0]) + int(product[1])
    else:
        sum1 = sum1 + product
    i = i - 2

sum2 = 0
x = -1
while x >= 0 - len(digitList):
    sum2 = sum2 + digitList[x]
    x = x - 2

checkSum = sum1 + sum2
checkSum = str(checkSum)

# If card number is valid
if checkSum[-1] == "0":
    if int(userCard[0]+userCard[1]) in range(51, 56, 1):
        print("MASTERCARD")
    elif int(userCard[0]+userCard[1]) == 34 or int(userCard[0]+userCard[1]) == 37:
        print("AMEX")
    elif int(userCard[0]) == 4 and len(userCard) >= 13:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")