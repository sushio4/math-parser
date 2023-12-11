# Parser of mathematical expressions
## Overview
Currently it works on simpler equations involving basic operations and most common functions, but I'm planning on expanding to features like solving systems of equations, computing integrals and graphing.

## Build
For my debug builds I used
```
gcc -C *.c -o main -lm -Wall -pedantic -Werror -fsanitize=address 
```
But it's really only necessary to link math.h functions and compile all .c files

## Usage
After running you'll see prompt to enter your equation. It cannot contain implicit multiplication (yet) but can contain variables, which you will have to enter value for as such
```
Enter your equation: 2*x + sin(alpha)*x

Enter the value for x: 1

Enter the value for alpha: 3.141592
Result: 2.000001
```
Currently available operations:
- addition '+'
- subtraction '-'
- multiplication '*'
- division '/'

Currently available functions:
- pow(x,y)
- sin(x)
- cos(x)
- sqrt(x)
- tan(x)

## Future
I will be adding more functions and operators, as well as a few features such as:
- numerical integrator
- numerical equation solver
- graphing

## How it works
First it processes input string to a vector of tokens, each having its own type.
Then it creates an abstract syntax tree by calling a function recursively on all parentheses.
In the end it searches for used variables, assigns a value to them and recursively evaluates whole tree.
