#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct  {
	double re, im;
}complex_t;

typedef struct {
	complex_t first, second;
}complex_pair;

int max(double a, double b);
complex_t init_complex(double re, double im);
complex_t sum(complex_t n1, complex_t n2);
complex_t mult(complex_t n1, complex_t n2);
double norm(complex_t n);
void show_complex(complex_t num);

#endif //COMPLEX_H