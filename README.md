# Newton-Raphson-parallel
This is a parallel C program for finding multiple roots to the equation f(x) = 0 in the interval [a, b].
In the src folder you will find two separate C programs; one implmententing bisection and one a hybrid
of bisection and Newton-Raphson. Parallelization was acheived with the OpenMP API.

# Compilation
Makefile is included for compilation. Simply type 'make' or 'make all' in the command line to compile all source code.
The executeables will be stored in the newly created folder bin.

# Run
./exec a b N T, where [a, b] is the interval to look for roots, N the number of subintervals and T the number of threads.
