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
### VARIABLE SCOPE

- Scope is a characteristic of a variable that defines from which functions that variable may be accessed
- For the most part local variables in C are "passed values" in function calls. The function calling this variable uses only its value to perform its function and passes the result in its own variable. So the passed variable is not altered, unless you overwrite it on purpose

**LOCAL VARIABLE**
- Can only be accessed within the function in which it was created

**GLOBAL VARIABLE**
- Can be accessed by any function in the program. To declare a global variable it has to be declared outside of a function (main() is also a function therefore declare it outside of main)
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
### WHILE LOOP

```c
while (boolean expression)
{
	// code;
}
```
- if the boolean expression evaluates to true, all lines of code between the curley braces will execute from top to bottom, as long as the boolean expression evaluates to true after each pass
***
### DO-WHILE LOOP

```c
do
{
	// code;
}
while (boolean expression);
```
- This loop will execute all lines of code between the curley braces at least once, and only then checks if the boolean expression is still true. If so, it will go back to the do part and execute the code. Compared to a regular while loop, this loop always executes at least once
***
### FOR LOOP

```c
for (int i = 0; i < 10; i++)
{
	// code;
}
```
- Syntactically unattractive, but for loops are used to repeat the body of a loop a specified number of times (here 10 times)
- The expression in the brakets is constructed as follows:
		for ( variable ; conditional; action / iteration)
- The process undertaken in a for loop is:
	- The counter variable(s) are set
	- The boolean expression is checked
	- The counter variable is incremented / decremented and then the boolean expression is checked again
***
### USE CASES

**WHILE LOOP**
- Use when you want a loop to repeat an unknown number of times and possibly not at all

**DO-WHILE**
- Use when you want a loop to repeat an uknown number of times, but at least once

**FOR LOOP**
- Use when you want a loop to repeat a discrete number of times, though you may not know the number at the instance the program was written
***

***
# FUNCTIONS
***
- So far all programs we have written, have been in main()
- C and nearly all languages developed since, allow us to write functions, sometimes als known as procedures, methods or subroutines
- A function is basically a black box that takes none or more input and returns one output
- The behaviour of a function is typically predictable by its name

**ORGANIZATION**
- Functions help break up complicated problems into more managable subparts

**SIMPLIFICATION**
- Smaller components tend to be easier to design

**REUSEABILITY**
- Functions can be recycled. You only need to write them once, but we can use them as often as you need
***
### FUNCTION DECLARATION

```c
int add_two_ints(int a, int b):
```
- The first step to creating a function is to declare it. This gives the compiler a heads up that a user-written function appears in the code
- Function declaration should always go atop of your code, before you begin writting main()
- There is a standard form, that every function declaration follows:
		**return-type name (argument-list);**
- The return type is what kind of variable the function will output (int, float, void, ..)
- The name should describe the function of the function
- The argument list is the comma-seperated set of inputs to your function, each with type and name
***
### FUNCTION DEFINITION

```c
int add_two_ints(int a, int b)
{
	int sum = a + b;
	return sum;
}
```
- The second step to creating a function is to define it. This allows for predictable behaviour when the function is called with inputs (arguments)
***
### FUNCTION CALLS

```c
int x = 5;
int y = 6;
int z = add_two_ints(x, y)
```
- To call a function, simply pass its appropriate arguments and assign its return value to something of the correct type (remember return type specified during function declaration)
***
### FUNCTION MISC

- Sometimes functions can take no inputs. In this case, we declare the function as having void argument list
- Sometimes functions can have no output, so we declare the function having a void return type
***

***
# COMMAND LINE ARGUMENTS
***

- So far all of our programs started with
```c
int main(void)
{
	// code;
}
```
- Since we have been collecting user input through in-program prompts and not from outside of the program
- To collect so called command line arguments from the user, we have to declare main as follows
```c
int main(int argc, string argv[])
{
	// code;
}
```
- These two special arguments enable you to know what data the user provided at the command line and how much data they provided
***
### ARGUMENT COUNT argc

- This integer-type variable will store the number of command line arguments the user typed when the program was executed

|  **COMMAND LINE**  | **argc** |
|:------------------:|:--------:|
|      ./program     |     1    |
| ./program 1024 C4Z |     3    |

**NOTE**
- The program name itself is counted as well!
***
### ARGUMENT VECTOR argv

- This array of strings, stores one string per element, the actual text the user typed into the command line, when the program was executed
- The first element at argv is always found at argv[0] and is the program name

| **./program 1024 C4Z** |   **argv**  |
|:----------------------:|:-----------:|
|         argv[0]        | "./program" |
|         argv[1]        |    "1024"   |
|         argv[2]        |    "C4Z"    |


***

***

# ARRAYS
***
- Arrays are fundamental data structures. We use arrays to hold **values of the same type**(string, int, char ...) at contigous memory locations
- You can access each element of an array, which can only hold a certain amount of elements, by index number
- In C, the elements of an array are indexed starting from index 0. This is one of the major reasons we count from 0 and not 1 in C
- If an array consists of n elements, the first is located at index 0. The last element at index(n-1)
***
### ARRAY DECLARATION

```c
type name[size]
```
- The type is what kind of variable at each element at the array will be
- The name is what you want the array to be called
- The size is how many elements you would like your array to contain
- If you think of a single element of an array of type data type, the same as you would any other variable of type data type, then all the familiar operations make sense
```c
bool truthable[10];
truthable[2] = false;
if (truthable[7] == true)
{
	printf("True!\n");
}
```
**CAUTION** 
- in the upper example you have 10 elements in the array, that means index 0 - (n-1) which means last index is 9. If you accessed truthable[10] you would be out of scope and find "\0" which defines the end of an array in memory

- When declaring and initializing an array simultanously, there is a special syntax that me be used to fill up the array with its starting values

**INSTANTIATION SYNTAX**
```c
bool truthable[3] = {false, true, true};
```

**INDIVIDUAL ELEMENT SYNTAX**
```c
bool truthable[3];
truthable[0] = false;
truthable[1] = true;
truthable[2] = true;
```

- You can leave the array size empty at instantiation and the compiler will figure out its size, depending on its elements
- Arrays can consist of more than a single dimension. You can have as many size specifiers as you wish.
```c
bool battleship[10][10];
```
- You can think of this as a 10 x 10 grid of cells. In memory it really just is a 100 element one-dimensional array
```c
// array bool battleship[10][10]

|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
|-|-|-|-|-|-|-|-|-|-|
```
- While we can treat individual elements of an array as variables, we cannot treat the entire arrays themselves as variables. We cannot assigne one array to another using =. Instead we must use a loop to copy each element over, one at a time
- Recall that most variables in C are "passed by value" in function calls. Arrays do not follow this rule. They are "passed by reference". The callee recieves the actual array, not a copy of the array
***

***

