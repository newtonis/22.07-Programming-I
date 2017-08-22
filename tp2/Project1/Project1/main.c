#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "mandelbrot.h"
#include "complex.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FPS = 40;




int main2(int argc , char *argv[]) {
    
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
            return 0;
    }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    
    parameter_data data;
    data.x0 = -2;
    data.y0 = -2;
    data.xf = 2;
    data.yf = 2;
    data.xMax = SCREEN_WIDTH;
    data.yMax = SCREEN_HEIGHT;
    
    draw_mandelbrot((void*)&data);

    al_flip_display();


    int exit = 0;
    printf("starting ...\n");
    while (!exit) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)){
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                    exit = 1;
            }else if (ev.type == ALLEGRO_EVENT_TIMER) {

            }
        }
    }
    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

        
}