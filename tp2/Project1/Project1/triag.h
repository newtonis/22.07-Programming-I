
#include <allegro5\allegro5.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include "common_structs.h"

typedef struct {
	double x;
	double y;
}pos_t;

typedef	struct {
	pos_t arriba;
	pos_t izq;
	pos_t derecha;
}bordes_t;

void dibujar(pos_t p1, pos_t p2, pos_t p3, double lend, int loop, double *small);

void precomputar_orden(pos_t p1, pos_t p2, pos_t p3, double lend, int loop, double *);

int verify_triang(parameter_data *p2trivar);
double distance(pos_t p1, pos_t p2);
double lado(pos_t p1, pos_t p2, pos_t p3);
pos_t calculate_new_cm(pos_t p1, pos_t p2, pos_t p3);

void get_three_coords(parameter_data * p2tri, bordes_t*);
void plot_triangle(parameter_data * p2tri);
