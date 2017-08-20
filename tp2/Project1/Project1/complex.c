#include "complex.h"
#include <stdio.h>
#include <math.h>

int max(double a, double b) {
	if (a > b) {
		return a;
	}else {
		return b;
	}
}

complex_t init_complex(double re, double im) {
	complex_t ans;
	ans.re = re; ans.im = im;
	return ans;
}

complex_t sum(complex_t n1, complex_t n2) {
	complex_t ans;
	ans.re = n1.re + n2.re; ans.im = n1.im + n2.im;
	return ans;
}

complex_t mult(complex_t n1, complex_t n2){
	complex_t ans;
	double a = n1.re, b = n1.im, c = n2.re, d = n2.im;
	ans.re = a*c - b*d;
	ans.im = a*d + b*c;
	return ans;
}
double norm(complex_t n) {
	return sqrt(n.re*n.re + n.im*n.im);
}
void show_complex(complex_t num) {
	printf("%f + %fi \n", num.re, num.im);
}
