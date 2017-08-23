#include "allegro5\allegro.h"
#include "allegro5\allegro_primitives.h"
#include "common_structs.h"
#include "octogon.h"

#include <stdio.h>
#include <math.h>

#define PI	3.14159265358979323846
#define ERROR	0
#define NO_ERROR 1 // para compatibilidad con el proyecto principal, error y warning son considerados como lo mismo (una falla)
#define WARNING	1
#define REPETICIONES ceil(log(info->lEnd/info->lStart)/log(info->lConstant)) //numero de veces que se debe multiplicar a lStart por lConstant para que alcanze a lEnd
#define REP_MAX	8 //maximo de repeticiones permitidas para un tiempo razonable de espera

const int octogon_color[3] = { 255,0,0 };

void draw_octogonal_fractal(parameter_data *info) {
	double lStart = info->lStart, lEnd = info->lEnd;
	double lConstant = info->lConstant;
	double x0 = info->x0, y0 = info->y0;
	ALLEGRO_COLOR color = al_map_rgb(octogon_color[0], octogon_color[1], octogon_color[2]);

	draw_octogonal_fractal_recursive(lStart, lEnd, lConstant, x0, y0, color);
}

void draw_octogonal_fractal_recursive(double lStart, double lEnd, double lConstant, double Xo, double Yo, ALLEGRO_COLOR color){
	double radius = (lStart) / (2 * sin(PI / 8));
	double offset = radius*(1 / sqrt(2));
	if (lStart<lEnd){
		return;
	}else{
		draw_octogon(Xo, Yo, radius, color); //dibujo un octagono de centro (Xo,Yo)
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo + radius, Yo, color); //llamo a la funcion  recursiva en los 8 vertices del octagono
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo + offset, Yo + offset, color);
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo, Yo + radius, color);
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo - offset, Yo + offset, color);
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo - radius, Yo, color);
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo - offset, Yo - offset, color);
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo, Yo - radius, color);
		draw_octogonal_fractal_recursive(lStart*lConstant, lEnd, lConstant, Xo + offset, Yo - offset, color);
	}
}

void draw_octogon(double Xo, double Yo, double radius, ALLEGRO_COLOR color){
	double offset = radius*(1 / sqrt(2));
	al_draw_line(Xo + radius, Yo, Xo + offset, Yo + offset, color, 2);
	al_draw_line(Xo + offset, Yo + offset, Xo, Yo + radius, color, 2);
	al_draw_line(Xo, Yo + radius, Xo - offset, Yo + offset, color, 2);
	al_draw_line(Xo - radius, Yo, Xo - offset, Yo + offset, color, 2);
	al_draw_line(Xo - radius, Yo, Xo - offset, Yo - offset, color, 2);
	al_draw_line(Xo, Yo - radius, Xo - offset, Yo - offset, color, 2);
	al_draw_line(Xo, Yo - radius, Xo + offset, Yo - offset, color, 2);
	al_draw_line(Xo + radius, Yo, Xo + offset, Yo - offset, color, 2);
}

int validacion_fractal_octogonal(parameter_data *info){
	int status = NO_ERROR;
	if ((info->lConstant < 0) || (info->lEnd < 0) || (info->lStart < 0) || (info->x0 < 0) || (info->y0 < 0)){
		status = ERROR; //no se aceptan valores negativos de ningun tipo
	}else if ((info->x0 > info->xMax) || (info->y0 > info->yMax)){
		status = ERROR; //centro se encuentra fuera del display
	}else if (info->lConstant > 1){
		status = ERROR; //lConstant esta entre cero y uno
	}else if (info->lStart < info->lEnd){
		status = ERROR; //lStart debe ser mayor a lEnd
	}else if (REPETICIONES > REP_MAX){
		status = WARNING;
		/*
		No hay error, pero con estos parametros el programa puede colgar en la recursion.
		Numero de repeticiones mayores a 8 hacen que el arbol de recursion sea muy grande
		y tarde mucho en procesarse el fractal
		*/
	}
	return status;
}