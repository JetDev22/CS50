# DATA TYPES
***
### INTEGER

|---------------------------------------------|---------------------------------------------|
-2^31                                                                    0                                                                       2^31 - 1

- The int datatype is used for variables that will store integers
- Integers always take up **4 bytes (32 bits)** of memory. This means the range of values they can  store is neccessarily limited to 32 bits worth of information
***
### UNSIGNED INT

|---------------------------------------------|---------------------------------------------|
0                                                                        2^31                                                                   2^31 - 1

- Unsigned is a qualifier that can be applied to certain types, which effectively doubles the positive range of variables of that type, at the cost of disallowing any negative values
***
### CHAR

|---------------------------------------------|---------------------------------------------|
-128                                                                      0                                                                           127

- Ther char data type is used for variables that will store single characters
- Characters always take up **1 byte (8 bits)** in memory. This means the range of values they can store is necessarily limited to 8 bits worth of information
- Thanks to ASCII, we've developed a mapping of characters like A, B, C ... to numeric values in the positive range
***
### FLOAT

- The float data type is used for variables that will store floating point values, also known as real numbers
- Floating point values always take up **4 bytes (32 bits)** of memory
- It is complicated to describe the range of float, but suffice to say that with 32 bits of precision, some of which might be used for an integer part, we are limited in how precise we can be
***
### DOUBLE

- The double data type is used for variables that will store floating point values
- The difference is that doubles are double precision compared to floats. They always take up **8 bytes (64 bit)** in memory
- With an additional 32 bits of precision relative to float, doubles allow us to specify much more precise real numbers
***
### VOID

- Is a type, not a data type
- Functions can have a void return type, which just means they do not return a value
- printf is an example since it does not return a value, but only prints to the terminal
- The parameter list of a function can also be void. It simply means the function takes no parameters
- Think of void more as a placeholder for "nothing"
***
### BOOL

- The bool data type is used for variables that will store a boolean value. More precisely, they are capable only of storing **true or false**
- Bool is no standard data type in C, therefore one is created in cs50.h
- Sometimes when working with boolean expressions, we will use variables of type bool, but we do not have to. In C every non zero value is equivalant to true and zero to false
***
### STRING

- The string data type is used for variables that will store a series of characters
***
***

# VARIABLES
***
### CREATING VARIABLES IN C

- To bring a variable into existance in C
```c
int number;
char letter;
```
- To create multiple variables at once in C
```c
int height, width;
float sqrt2, sqrt3, pi;
```
- The different procedures to create a variable or assign a value have following names
```c
int number;                // Declaration
number = 17;               // Assignement
int number = 17;           // Initialization
```
***
***

# CONDITIONALS
***
- Conditional expressions allow your programs to make decisions and take different forks in the code, depending on the values of variables or user input
- C provides a few different ways to implement conditional expressions

- When best to use what:
	- **if statements** use boolean expressions to make decisions
	- **switch statements** use discret cases to make decisions
	- **ternary statements** used to replace a very simple if else statement
***
### IF STATEMENT IN C

```c
if (boolean expression)
{
	// code;
}
else
{
	// other code;
}
```
- If the boolean expression evaluates to **true**, all lines of code between the curly braces will execute in order from top to bottom
- If the boolean expressions evaluates to **false**, these lines of code will not execute and pass to the following else statement
- In C it is possible to create an if-else-if-else chain
```c
if (boolean expression)
{
	// first branch;
}
else if (other boolean expression)
{
	// second branch;
}
else
{
	// third branch;
}
```
***
### SWITCH STATEMENT IN C

- C's switch statement is a conditional statement that permits enumeration of discrete cases, instead of relying on boolean expressions
- It is important to **break;** between each case, or you will "fall through" each case (unless that is your intended behaviour)
```c
int x = get_int();
switch (x)
{
	case 1:
		printf("One!\n");
		break;
	case 2:
		printf("Two!\n");
		break;
	default:
		printf("Sorry!\n");
}
```
- Here case 1 does not mean first case but get_int() returned the int 1
***
### TERNARY STATEMENT

- The following code snippets are identically
- The ternary operator **?:** is mostly a cute trick, but is useful for writing trivially short conditional branches.
```c
// Regular
int x;
if (boolean expression)
{
	x = 5;
}
else
{
	x = 6;
}

// Ternary Way first int if true, second if false
int x = (boolean expression) ? 5 : 6;
```
***
***

# OPERATORS
***
### ARITHMETIC OPERATORS

- In order to manipulate and work with variables and values in C, we have a number of operators at our disposal

|   ARITHMETIC   | SYMBOL |
|:--------------:|:------:|
|    Addition    |    +   |
|   Subtraction  |    -   |
| Multiplikation |    *   |
|    Division    |    /   |

- We also have the **modulus operator %** which gives us the remainder, when the number on the left of the operator is divided by the number on the right of the operator.
```c
int m = 13 % 4;
// m will be 1 because 13/4 is 3*4 = 12 and 13-12 = 1
```
- C also provides a shorthand way to apply an arithmetic operator to a single variable
```c
// regular
x = x * 5;

// shorthand
x *= 5;
```
- C provides a further shorthand for incrementing or decrementing a variable by 1
```c
x++;    // adds 1 to x
x--;    // subtracts 1 from x
```
***
### BOOLEAN LOGICAL OPERATORS

- Logical **AND (&&)** is true if and only if both operands are true, otherwise will return false

|   X   |   Y   | (x && y) |
|:-----:|:-----:|:--------:|
|  true |  true |   true   |
|  true | false |   false  |
| false | false |   false  |
| false |  true |   false  |

- Logical **OR (||)** is true if and only if at least one operand is true, otherwise false

|   X   |   Y   | (x \|\| y) |
|:-----:|:-----:|:----------:|
|  true |  true |    true    |
|  true | false |    true    |
| false | false |    false   |
| false |  true |    true    |

- Logical **NOT (!)** inverts the value of its operand

|   X   |   !X  |
|:-----:|:-----:|
|  true | false |
| false |  ture |

***
### BOOLEAN RELATIONAL OPERATORS

- These behave as you would expect them to and appear syntactically similar to how you may recall them from elementary arithmatic

|      Description      | Symbol |
|:---------------------:|:------:|
|       less than       |  x < y |
|   less than or equal  | x <= y |
|      greater than     |  x > y |
| greater than or equal | x >= y |

- C also can test two variables for equality and ineaquality

| Description | Symbol |
|:-----------:|:------:|
|   equality  | x == y |
|  inequality | x != y |

***
***

# LOOPS
***
- Loops allow your programs to execute lines of code repeatedly, saving you from needing to copy and paste or otherwise repeat lines of code
- Hint: if you start copy pasting code, either write a function or check if a loop helps
***
### INFINITE LOOP

```c
while (true)
{
	// code;
}
```
- This is what we call an infinite loop. The lines of code between the curley braces will execute repeatedly from top to bottom, forever unless we break out of it with a **break; statement** or kill the program
***
