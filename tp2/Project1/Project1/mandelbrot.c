#include <math.h>
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"
#include "complex.h"
#include "mandelbrot.h"

#include <stdio.h>


/**** Manderbrot configuration ****/

/// Complex limits
const double MIN_X = -100.0; 
const double MIN_Y = -100.0;
const double MAX_X =  100.0;
const double MAX_Y =  100.0;

enum {VARIABLE_X , VARIABLE_Y };

const int MAND_CONSTANT = 255;

/// color interval configuration
const color_interval_t interval_color[] = {
	{ 0    , 32*1-1 ,255,255,255 },
	{ 32*1 , 32*2-1 ,200,255,255 },
	{ 32*2 , 32*3-1 ,200,200,255 },
	{ 32*3 , 32*4-1 ,200,200,200 },
	{ 32*4 , 32*5-1 ,150,200,200 },
	{ 32*5 , 32*6-1 ,150,150,200 },
	{ 32*6 , 32*7-1 ,150,150,150 },
	{ 32*7 , 32*8-1 ,100,150,150 },
};



int verify_range(double position,int type){
    int ans = 0;
    if (type == VARIABLE_X){
        ans = position > MIN_X && position < MAX_X;
    }else if (type == VARIABLE_Y){
        ans = position > MIN_Y && position < MAX_Y;
    }
    return ans;
}

int verify_mandelbrot(parameter_data *data){
   
    int success = 1;
    success = success && verify_range(data->x0,VARIABLE_X);
    success = success && verify_range(data->y0,VARIABLE_Y);
    success = success && verify_range(data->xf,VARIABLE_X);
    success = success && verify_range(data->yf,VARIABLE_Y);
    
    success = success && data->xf > data->x0;
    success = success && data->yf > data->y0;
    
    return success;    
}

int compute_f(complex_t point , parameter_data *data) { 
	parameter_data vars = *data;

	complex_t aux = init_complex(0.0,0.0);
	int max_distance = norm(init_complex( 
		max(abs(vars.x0), abs(vars.xf)), 
		max(abs(vars.y0), abs(vars.yf))  
	));
	complex_t test = init_complex(
		max(abs(vars.x0), abs(vars.xf)),
		max(abs(vars.y0), abs(vars.yf))
	);

	int max_i = 0;
	for (int i = 1; i <= MAND_CONSTANT && norm(aux) < max_distance; i++) { /// compute the formula
		aux = sum(mult(aux, aux), point);
		max_i = max(i, max_i); // max i that holds 'norm(aux) < max_distance'
	}
        
	return MAND_CONSTANT - max_i; 
}

void draw_point(int x,int y,ALLEGRO_COLOR color) { // draw point on screen
	al_draw_line((double)x + 0.5,(double)y, (double)x + 0.5, (double)y + 1.0,color,1); // pixel precise output
}

ALLEGRO_COLOR get_color(int value) { // if no color was found returns 0
	int cnt_intervals = sizeof(interval_color) / sizeof(color_interval_t);
	for (int i = 0; i < cnt_intervals; i++) {
		if (interval_color[i].a >= value && value <= interval_color[i].b) {
			int r = interval_color[i].rc;
			int g = interval_color[i].gc;
			int b = interval_color[i].bc;
			return al_map_rgb(r, g, b);
		}
	}
	return al_map_rgb(0, 0, 0); // no color!
}

complex_t get_complex_coordinate(int x, int y,parameter_data *data) {
	double x0 = (double)data->x0, y0 = (double)data->y0;
	double xf = (double)data->xf, yf = (double)data->yf;
	double xMax = (double)data->xMax, yMax = (double)data->yMax;

	return init_complex(x * (xf - x0) / xMax + x0, y * (yf - y0) / yMax + y0);
}

void draw_mandelbrot(parameter_data *pdata){
    parameter_data data = *pdata;
    printf("%d %d \n", data.xMax, data.yMax);
    printf("computing ...");


    int cnt[256];
    for (int i = 0; i < 256; i++) cnt[i] = 0;

    for (int y = 0; y < data.yMax; y++) {
            //printf("#");
            for (int x = 0; x < data.xMax; x++) {
                    complex_t cor = get_complex_coordinate(x, y, &data);
                    //printf("%f %f \n", cor.re, cor.im);
                    int val = compute_f(get_complex_coordinate(x, y, &data), &data);
                    cnt[val]++;
                    ALLEGRO_COLOR color = get_color(val);
                    draw_point(x, y, color);
            }
    }
    for (int i = 0; i < 256; i++) {
            printf("%d ", cnt[i]);
    }
    printf("\n");


}