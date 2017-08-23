
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


#include "common_structs.h"
#include "lib_parser.h"
#include "utils.h"
#include "mandelbrot.h"
#include "octogon.h"

const char * manderbrot_params[] = { "type","x0","y0","xf","yf" };
const char * triang_params[] = { "type","lstart","lend","x0","y0","leftangle","rightangle" };
const char * octogon_params[] = { "type","lstart","lend","x0","y0","lconstant"};

const int SCREEN_WIDTH  = 800;
const int SCREEN_HEIGHT = 600;
const int FPS = 40;

int parseCallback(char* key, char* data, void* userdata);

/*** Testing examples 
	-type Octogon -lStart 300 -lEnd 30 -lConstant 0.5 -x0 450 -y0 45
***/
int main(int argv , char *argc[]){
    parameter_data data;
	data.xMax = SCREEN_WIDTH;
	data.yMax = SCREEN_HEIGHT;

	init_data(&data);

    int parser_success = parseCmdLine(argv,argc,parseCallback,(void*)&data);
    
	if (parser_success == 0) {
		printf("Syntax error on parameters \n");
		getchar();

		return 0;
	}
    
	if (!find_in_data("type",&data)) {
		printf("type parameter missing \n");
		getchar();
		return 0;
	}
	if (strcmp(data.type, "manderbrot") == 0) {
		if (!check_params(&data, manderbrot_params, sizeof(manderbrot_params) / sizeof(char*))) {
			printf("Invalid manderbrot parameters \n");
			getchar();
			return 0;
		}
		if (!verify_mandelbrot(&data)) {
			printf("Invalid manderbrot intervals\n");
			getchar();
			return 0;
		}
	}else if (strcmp(data.type, "triangle") == 0) {
		if (!check_params(&data, triang_params, sizeof(triang_params) / sizeof(char*))) {
			printf("Invalid triangle parameters \n");
			getchar();
			return 0;
		}
		if (!verify_triang(&data)) {
			printf("Invalid triangle intervals \n");
			getchar();
			return 0;
		}
	}else if(strcmp(data.type,"octogon") == 0){
		if (!check_params(&data, &octogon_params, sizeof(octogon_params) / sizeof(char*))) {
			printf("Invalid octogon parameters \n");
			getchar();
			return 0;
		}
		if (!validacion_fractal_octogonal(&data)) {
			printf("Invalid octogon parameters \n");
			getchar();
			return 0;
		}
	}else {
		printf("No valid type selected \n");
		getchar();
		return 0;
	}


	/// Now start allegro!
	al_init();
	ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	al_init_primitives_addon();
	if (!display || !event_queue || !timer) {
		printf("Failed to start allegro \n");
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		al_destroy_timer(timer);
		getchar();
		return 0;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));



	if (strcmp(data.type, "manderbrot") == 0) {
		draw_mandelbrot((void*)&data);
	}else if (strcmp(data.type, "triangle") == 0) {
		plot_triangle(&data);
	}else if (strcmp(data.type, "octogon") == 0) {
		draw_octogonal_fractal(&data);
	}


	al_flip_display();

	int exit = 0;
	printf("starting ...\n");

	while (!exit) {
		ALLEGRO_EVENT ev;
		if (al_get_next_event(event_queue, &ev)) {
			if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				exit = 1;
			}
		}
	}
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
	al_destroy_display(display);


}

int parseCallback(char* key, char* data, void* userdata) {
	lowerize(key);
	lowerize(data);

	parameter_data *udata = ((parameter_data*)userdata);

	char *endptr = NULL;

	if (data == NULL) {
		return 0; // no pure parameter expected
	}
	if (find_in_data(key, &udata)) {
		return 0; // repeated parameter
	}
	if (strcmp(key, "type") == 0) {
		udata->type = data;
	}else if (strcmp(key, "x0") == 0) {
		udata->x0 = strtof(data, &endptr);
	}else if (strcmp(key, "y0") == 0) {
		udata->y0 = strtof(data, &endptr);
	}else if (strcmp(key, "xf") == 0) {
		udata->xf = strtof(data, &endptr);
	}else if (strcmp(key, "yf") == 0) {
		udata->yf = strtof(data, &endptr);
	}else if (strcmp(key, "lstart") == 0) {
		udata->lStart = (int)strtol(data, &endptr, 10);
	}else if (strcmp(key, "lend") == 0) {
		udata->lEnd = (int)strtol(data, &endptr, 10);
	}else if (strcmp(key, "leftangle") == 0) {
		udata->leftAngle = strtof(data, &endptr);
	}else if (strcmp(key, "rightangle") == 0) {
		udata->rightAngle = strtof(data, &endptr);
	}else if(strcmp(key,"lconstant") == 0){
		udata->lConstant = strtof(data, &endptr);
	}else {
		udata->error = 1;
		return 0; // error, invalid parameter
	}
	if (errno == ERANGE) {
		udata->error = 1; // invalid conversion
		return 0;
	}
	udata->recv[udata->recv_cnt++] = key;

	printf("[%s] = %s \n",key,data);
	printf("udata[%d] = %s\n", udata->recv_cnt-1, udata->recv[udata->recv_cnt-1]);
	return 1;
}
