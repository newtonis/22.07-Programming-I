#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "common_structs.h"
#include "complex.h"


typedef struct{ // interval [a,b]
	int a, b;
	int rc, gc, bc; // red color, green color, blue color
}color_interval_t;

int verify_mandelbrot(parameter_data *data); /// return 1 if data is correct, 0 otherwise

void draw_mandelbrot(parameter_data *data); // draw in screen

static complex_t get_complex_coordinate(int i, int j, parameter_data *data);
static int compute_f(complex_t point, parameter_data *vars);
static void draw_point(int x, int y, ALLEGRO_COLOR color);

#endif