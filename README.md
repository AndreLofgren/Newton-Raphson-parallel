# root-finding
This is a parallel C program for finding multiple roots to the equation f(x) = 0 in the interval [a, b].
In the src folder you will find two separate C programs; one implmententing bisection and one a hybrid
of bisection and Newton-Raphson. Parallelization was acheived with the OpenMP API.

# compilation
Makefile is included for compilation. Simply type 'make all' in the command line to compile all source code.
