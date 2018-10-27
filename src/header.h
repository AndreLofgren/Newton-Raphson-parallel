#ifndef _HEADER
#define _HEADER

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#ifdef _OPENMP
    #include <omp.h>
#endif

typedef struct array {
    double *ptr;
    int size;
} array;

double derive(double (*fun_ptr)(double), double x);
double find_zero_NR(double (*fun_ptr)(double), double a, double b);
array *find_all_zeros_NR(double (*fun_ptr)(double), double a, double b, int N, int T);
double find_zero_bisection(double (*fun_ptr)(double), double a, double b);
array *find_all_zeros_bisection(double (*fun_ptr)(double), double a, double b, int N, int T);

#endif
