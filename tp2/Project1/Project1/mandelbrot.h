#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "complex.h"

typedef struct{ // interval [a,b]
	int a, b;
	int rc, gc, bc; // red color, green color, blue color
}color_interval_t;


typedef struct {
	int x0, y0, xf, yf;
	int xMax, yMax;
}mandelbrot_data_t; // to organize manderbrot input data

void draw_mandelbrot(int x0,int y0,int xf,int yf,int xMax,int yMax); // draw in screen

static complex_t get_complex_coordinate(int i, int j, mandelbrot_data_t *data);
static int compute_f(complex_t point, mandelbrot_data_t *vars);
static void draw_point(int x, int y, ALLEGRO_COLOR color);

#endif