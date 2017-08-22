#ifndef CONFIG_H
#define CONFIG_H

#include "mandelbrot.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FPS = 40;


/**** Manderbrot configuration ****/

/// Complex limits
const double MIN_X = -100.0; 
const double MIN_Y =  100.0;
const double MAX_X = -100.0;
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


#endif /* CONFIG_H */

