# Newton-Raphson-parallel
This is a parallel C program for finding multiple roots in the interval [a, b] to the equation f(x) = 0.
In the src folder you will find two separate C programs; one implementing bisection, and one a hybrid
of bisection and Newton-Raphson. Parallelization was acheived with the OpenMP API.

# Compilation
A makefile is included for compilation. Simply type 'make' or 'make all' in the command line to compile all source code. The executables will be stored in the newly created folder bin.

# Run
./exec a b N T, where [a, b] is the interval to look for roots, N the number of subintervals and T the number of threads.

# Example runs
$ ./exec 0 100000 100000 2 <br />
Newton-bisection found 31831 zeros in 0.779270 s <br />
all zeros, z0, pased the test |fun(z0)| < 1e-6
<br />
Bisection found 31831 zeros in 0.270711 s <br />
all zeros, z0, passed the test |fun(z0)| < 1e-6

$ ./exec 0 1000000 100000 2 <br />
Newton-bisection found 100000 zeros in 0.089167 s <br />
all zeros, z0, pased the test |fun(z0)| < 1e-6
<br />
Bisection found 100000 zeros in 0.315474 s <br />
all zeros, z0, passed the test |fun(z0)| < 1e-6

# Additional notes
If you find the code helpful and want to reuse it for your homework or your project, you're free to do so. However, I leave no guarantee regarding correctness and functionality, and strongly discourage thoughtless copying a random piece of code. You're ultimately the one responsible for testing and making sure your program is correct. If you find a bug in the code, don't hesitate to contact me.
