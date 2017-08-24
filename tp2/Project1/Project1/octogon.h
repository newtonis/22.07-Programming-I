#ifndef OCTAGON_H
#define OCTAGON_H

#include "common_structs.h"
#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"

void draw_octogonal_fractal(parameter_data *info);
int validacion_fractal_octogonal(parameter_data *info);

static void draw_octogonal_fractal_recursive(double lStart, double lEnd, double lConstant, double Xo, double Yo,int depth);
static void draw_octogon(double Xo, double Yo, double radius, ALLEGRO_COLOR color);

#endif