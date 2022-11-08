# Lesson 0 - Introduction
***
- On the base hardware level, computers only understand 0s and 1s (binary)

| BINARY | REAL WORLD |
|:------:|:----------:|
|   000  |      0     |
|   001  |      1     |
|   010  |      2     |
|   011  |      3     |

- In real world numbers, we associate each row of a number with a certain value. The number 563 can be deconstructed to 100ths, 10ths, and 1s as: **5x100 + 6x10 + 3x1**
- In **BINARY** you only use 2 to the power

| BINARY | DECONSTRUCTED | OUTPUT  |
|:------:|---------------|---------|
|        |   0x2^2 = 0   |         |
|   010  |   1x2^1 = 2   | 2 = 010 |
|        |   0x0^2 = 0   |         |
|        |               |         |
|        |   0x2^2 = 0   |         |
|   011  |   1x2^1 = 2   | 3 = 011 |
|        |   1x2^0 = 1   |         |

- **ASCII** is short for American Standard Code for Information Interchance. It is a standard as to which sequence of 0s and 1s represent what letter, number, symbol ...

|  **ASCII** |    72    |    73    |    33    |
|:----------:|:--------:|:--------:|:--------:|
| **BINARY** | 01001000 | 01001001 | 00100001 |
| **OUTPUT** |     H    |     I    |     !    |

- 01001000 is **8bits** or **1byte**
- With 8bits, if you choose to include 0, you can only count to 255 (256 if you exclude 0)
- **UNICODE** is a superset onto **ASCII** to allow for not just 8bit character mapping (to keep backward compatability), but also 16bit mapping and therefore allows for **65.000** characters to be mapped.
- An **ALGORITHM** is a set of step by step instructions to solve a specific problem
***
***

# Lesson 1 - C Language
***

|                              **CORRECTNESS**                             |                                                                                **DESIGN & STYLE**                                                                               |
|:------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
| The code must solve the problem at <br>hand and givce a correct solution | Good designed code allows others<br>to understand you code easier, or<br>yourself after some time later.<br>Efficient algorithms are key for<br>nice and clean structured code. |

- **SOURCE CODE -> COMPILER -> MACHINE CODE**
- To inculde a variable in a print statement in C use %  followed by its datatype (i for int, s for string ...). Here %s is the placeholder for the string answer.
```c
printf("hello, %s\n", answer);
```
- On top of every C program, you will find "#include" followed by sime **headerfile**. The headerfile will point the compiler to where all the libraries are stored. Here stdio.h is the standard io library for c
```c
#include <stdio.h>

int main(void)
{
	#your program
}
```
- **DATATYPES in C**

| **BASH COMMAND** |      **DESCRIPTION**      |
|:----------------:|:-------------------------:|
|        cd        |      change directory     |
|       cd ..      |   go to parent directory  |
|        rm        |           remove          |
|       mkdir      | create directory / folder |
|       rmdir      | remove directory / folder |
|        mv        |            move           |

- **FUNCTIONS in CS50.h**

| **printf placeholder** | **Description** |
|:----------------------:|:---------------:|
|           %c           |       char      |
|           %f           |      float      |
|           %i           |       int       |
|           %li          |     long int    |
|           %s           |      string     |

- **OPERATORS in C**

| **Operator** |             **Description**            |
|:------------:|:--------------------------------------:|
|       +      |                addition                |
|       -      |               subtraction              |
|       *      |             multiplication             |
|       /      |                division                |
|       %      | remainder<br>5%2 = 1<br>5/2 = 2 Rest 1 |

- There are three ways to increment a variable by one. Here 1 is added to the variable "counter"
```c
counter = counter + 1;
counter++;
counter += 1;
```
- In C once a variable is declared with a datatype, it does not have to be declared again
```c
int counter = 0;
counter++;        // No further int counter required, only counter
```
- To declare a variable and make it not changeable later on in the code, use const followed by an all caps variable name (all caps not mandatory but convention for C)
```c
const int BASE = 2;
```
- **IF STATEMENT CONDITIONALS**
```c
if (x == 0 || x == 1)        // OR
{
	# code
}

if (x == 0 && x == 1)        // AND
{
	# code
}
```
- **WHILE LOOP IN C**
```c
int i = 0;
while (i < 3)
{
	printf("hello\n");
	i++;
}
```
- **DO WHILE LOOP IN C**
```c
do
{
	// code goes here
}
while (n < 1);
```
A while loop checks the condition **BEFORE** executing the code. A do-while loop first executes the code at least once, then checks the condition and if the conditon is true, goes to execute the code again.
- **FOR LOOP IN C
```c
for (int i = 0; i < 3; i++)
{
	printf("hello\n");
}
// for (variable; condition; update)
```
- **CREATE A FUNCTION IN C**
The first void means, that this function will not return any value or variable, hence void. The second (void) means, that this function will not take any arguments (externally passed variables). A function must be declared prior to being called, this is being called a prototype function (here void hello(void); ).
```c
#include <stdio.h>

void hello(void);             // 2nd.: this makes the function callable

int main(void)
{
	void hello(void)         // 1st.: create the function
	{
		printf("hello\n");
	}
	hello();                 // 3rd.: call the function
}
```
- **FLOATING POINT INPRECISION**
The computers inability to represent all possible real numbers, since memory is finite and real numbers aren't
***
***
# Lesson 2 - Arrays
***
### COMPILER
- We used the make command to compile hello.c to an executable. But make is not a compiler, but rather a helper to look for the right compiler and create an executable called hello
- For C you could compile the code yourself by
```bash
clang hello.c
```
- This would get a.out, which is an assembly file. You can still run it with
```bash
./ a.out
```
- a.out is the standard name clang (the c compiler) will call the executable. To specify your own name for the clang compiled executable you have to use the flag -o
```bash
clang -o hello hello.c
// compiler flag name sourcecode
```
- This only works if ony stdio.h is used. Every other headerfile (for example cs50.h) in our code, has to be manually linked for the compiler
```bash
clang -o hello hello.c -l cs50
```
- Whenever you use the make command, referred to as compiling, there are actually four things happening
	- **1. PREPROCESSING**
		All headerfiles included in your code have a # infront of them. This is known as "preprocessor directives". This tells the compiler to the those headerfiles and include them above your code, so any function out of these headerfiles can be used in your code
	- **2. COMPILING**
		Turns your C language code from top to bottom into assembly code. This is a very low level language, the computer can understand natively. Those assembly instructions (add, divide, move to memory, read from memory...) are baked into every CPU
	- **3. ASSEMBLING**
		The assembly code, generated from your high level language is now converted into binary code
	- **4. LINKING**
		Now the binary from your sourcecode is combined with the headfiles that are referenced with their respective c files

### DEBUGGING
- printf is a valuable tool to check your variables or functions to see what they do or how they behave in case you have to debug the code
- You can use **debug50** on your code to step through your code from a breakpoint and see line for line, what your code is doing and how your variables change
```bash
debug50 ./test
```

### TYPES
- We already saw some datatypes like bool / char / int / float ....
- Whenever one expression of an arithmatic is a float, all expressions of that arithmatic will be treated as a float
```c
int x = 4;
int y = 5;
float sum = x + y
// sum will now be 9.0
```

### ARRAY
- Is another datatype, that allows you to store multiple values, of the same type (int, float, char ..) back to back
```c
// create each variable on its own
int score1;
int score2;
int score3;

// create array
int scores[3];
```
- To add the scores to the array, you add them, starting at index 0
```c
scores[0] = 72;
scores[1] = 73;
scores[2] = 33;
```
- Note no further int declaration is needed, since the array was initialized as array of ints
- In C a string is nothing more than an array of chars
- In memory a nul character defines the end of a string. A nul character is written in shorthand as  \ 0  which is nothing but 8x0. So every string takes up 1 byte per character + 1 byte for the nul character to depict its end

### Note
- C can print the ASCII value of a char
```c
char c1 = 'H';
char c2 = 'I';
char c3 = '!';

printf("%c %c %c", c1, c2, c3);

// this prints HI!
```
- But if you print these chars as int, the ASCII code of each char is printed
```c
printf("%i %i %i", c1, c2, c3);

// this prints 72 73 33
```
- Another way is **implicit type casting**. This will also print 72 73 33 but here we implicitly tell it to print the ASCII value and not rely on C to make it automatically
```c
printf("%i %i %i", (int)c1, (int)c2, (int)c3);
```
- string.h includes a function called strlen which returns the length of a given string
```c
int length = strlen(name);
```
- In ASCII every letter corresponds to an integer value. Capital letters first, then Lower case letters. Since C can also use the ASCII value for a char, we can turn letters to upper case or lower case, by manipulating their ASCII value
	=> Captial to Lower = + 32
	=> Lower to Capital = - 32
- Inside a boolean expression, if the return value = 0 it is seen as false
	=> simple arithmatic can act as true / false expression

### COMMAND LINE ARGUMENTS
```c
int main(void)
{
	// code
}
```
- The (void) means our program does **not** take command line arguments
- Command line arguments are passed to the main, after typing them behind the program execution in the command line
```bash
./program arg1 arg 2
```
- The standard arguments that are passed to main are **argc** and **argv[]**. While argc stand for argument count and argv is an array of words called argument vector
```c
int main(int argc, string argv[])
{
	// code
}
```
- argc is always atleast 1 because the first argument counted for is the program name
```bash
./program Thomas
```
```c
int main(int argc, string argv[])
{
	if (argc > 1)
	{
		printf("hello, %s\n", argv[1]);   //index 0 would be program namne
	}
	else
	{
		printf("hello word\n");
	}
}

// this prints hello, thomas
```

### EXIT STATUS
```c
int main(int argc, string argv[])
{
	if (argc != 2)
	{
		printf("Missing user input\n");
		return 1;
	}
}
```
- Whenever you break out of your programm by design (for example required input by user was not given), have main return a non 0 value, by convention use 1
- By default, if defined or not, C will return 0 to let the computer know, your programm worked fine
***
***

# Lesson 3 - Algorithms
***
- The efficiency of code or algorithms is measured in **running time**. How much time does the code / algorithm take to make the neccessary steps. The measure for this is **big O notation**

![image info](./Pictures/bigOgraph.png)
- The bigger the problem size becomes, the more similar O(n) and O(n/2) will look and only O(log2n) will stand out
- Convention is, to just refer to O(log2n) as O(logn)
- A for loop that runs n times, big O will be O(n)
- Examples for real world big O notation running times are:
	- O(n^2)
	- O(n log n)
	- O(n)
	- O(logn)
	- O(1)
- Big Ω (omega) is used to describe the lower bound of an algorithm or how few steps an algorithm might take. Big O is the upper bound, on how many steps an algorithm might take.
	- Ω(n^2)
	- Ω(n log n)
	- Ω(n)
	- Ω(logn)
	- Ω(1)
- Big Θ (theta) is used when the upper and lower bound of an algorithm running time is equal
	- Θ(n^2)
	- Θ(n log n)
	- Θ(n)
	- Θ(logn)
	- Θ(1)

| **NOTATION** |               **DESCRIPTION**              |
|:------------:|:------------------------------------------:|
|       O      |        upper bound (how many steps)        |
|       Ω      |         lower bound (how few steps)        |
|       Θ      | O = Ω (upper and lower bound are the same) |

- The input n into these expressions, is the number of steps for the algorithm to complete. Smaller means faster

|  **2** |       | **100** |       | **10.000** |
|:------:|:-----:|:-------:|:-----:|:----------:|
| log(n) | **<** |   (n)   | **<** |    (n^2)   |


### LINEAR SEARCH
![image info](./Pictures/linearSearch.png)
```c
int main (void)
{
	int numbers[] = {4, 6, 8, 2, 7, 5, 0}
	for (int i = 0; i < 7; i++) //array length -1 is 7 beacause we count from 0
	{
		if (number == 0)
		{
			printf("Found\n");
			return 0;
		}
	}
	printf("Not found\n");
	return 1;
}
```
- **O(n)** because max number of loops is n times
- **Ω(1)** because number could be found at array index 0 and therefore run only once

### BINARY SEARCH
![image info](./Pictures/binarySearch.png)
- Prerequisit is, that the array is sorted from small to big
```c
// Pseudo Code
// If nothing in array
//    return false
// If number at middle of array
//    return true
// Else if number < number[middle of array]
//    search array[0] through array[middle - 1]
// Else if number > number[middle of array]
//    search array[middle + 1] through array[arrayLength - 1]
```

-  **O(logn)** because you half the problem with every step until you find the target
-  **Ω(1)** because the first index of the array may be the number you looked for

### DATA STRUCTURES
- In C we have the ability to invent our own datatypes
```c
type def struct    //tells the compiler it is a structure
{
	string name;
	string number;
}
person;            // name of datatype

person people[2];  // new array of type person and size 2
people[0].name = "Thomas"
people[0].number = "09953-2211"
```
- This way we encapsulate all information for one person into one datatype
- This **is not a class or object** because this does not have the ability to also contain functions and C is not an object oriented programming language

### SELECTION SORT
![image info](./Pictures/selectionSort.png)
```c
// Pseudo Code
// For i from 0 to n-1
//    Find smallest num between num[i] and num[i-1]
//    Swap smallest num with num [i]
```


-  **O(n^2)** The steps are actually layed out as n + n(-1) + n(n-2) ... and since n^2/2 has the highest impact on this equation, we just consider n^2
-  **Ω(n^2)** Even if the array was already sorted, it would iterate through n times and make sure all integers are in order so n + n(-1) + n(n-2) ....
- **Θ(n^2)** Because best case scenario (array is sorted) and worst case (array not sorted) take the same time O = Ω = Θ

### BUBBLE SORT
![image info](./Pictures/bubbleSort.png)
```c
// Pseudo Code
// Repeat arrayLength - 1 times
//   For i from 0 to arrayLength -2 (because last array index has no i+1 pos)
//      If num[i] and num[i+1] not in order
//         Swap num[i] with num[i+1]
//      If no swaps
//         quit
```
- The reason to do this n-1 times and not just the inner loop, is that during each O -> n-2, the swap moves the digits only one position. If 0 was at the end, it would only move the whole array one to the left

- **O(n^2)** You have two loops so you multiply outer loop x inner loop, that is (n-1) x (n-2) = n^2 - 1n - 1n + 3 ... since only n^2 is very big, it is deemed the biggest impact and the rest of it is dropped
-  **Ω(n)** In the best case scenario (array is sorted), Bubble sort has only one pass to make and quits if no swaps are made

### MERGE SORT
![image info](./Pictures/mergeSort.png)
- Merge Sort divides the problem in half and then merges the results of the sorted halfs
```c
// Pseudo Code

// If only one number
//    quit
// Else
//    Sort left half of array
//    Sort right half of array
//    Merge sorted halfes
```
- You end up with to sorted halfes (lists) and look at the first position of each half. The smaller digit at this comparison is then transfered to the sorted list

- **O(n log n)**
- **Ω(n log n)**
- **Θ(n log n)**


### RECURSION

![image info](./Pictures/recursion.png)
- Recursion is a programming technique, whereby a function calls itslef
- An example would be our mario.c program that drew the blocks
```c
// Mario.c regular way
#include <cs50.h>
#include <stdio.h>

void draw(int n);     // prototype for our own draw function

int main(void)
{
	int height = get_int("Height: ");
	draw(height);
}

void draw(int n)      // draw function
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i+1; j++)
		{
			printf("#");
		}
		printf("\n");
	}
}
```
- And here the same program with recursion
```c
#include <cs50.h>
#include <stdio.h>

void draw(int n);     // prototype for our own draw function

int main(void)
{
	int height = get_int("Height: ");
	draw(height);
}

void draw(int n)
{
	if (n <= 0)     // Base case, a way to exit and avoid infinite loop
	{
		return;
	}
	draw(n-1);

	for (int i = 0; i < n; i++)
	{
		printf("#");
	}
	printf("\n");
}
```
