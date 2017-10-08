#include <iostream>
#include "animation.h"
#include "anim_atributes.h"

const float MAX_WIDTH = 1280.0;
const float MAX_HEIGHT = 720.0;

using namespace std;

int allegro_init(ALLEGRO_DISPLAY *&);
int create_and_register_allegro_vars(ALLEGRO_TIMER *&timer, ALLEGRO_EVENT_QUEUE*& event_queue, ALLEGRO_DISPLAY *&display, float timer_period);

int main(void)
{
	ALLEGRO_DISPLAY * display = nullptr;
	ALLEGRO_EVENT_QUEUE *	event_queue = nullptr;
	ALLEGRO_TIMER * timer = nullptr;

	//iniciliazacion de allegro
	if (allegro_init(display) == -1) {
		return -1;
	}

	/*Acá se selecciona la animacion*/
	//con las letras A B C D E F 

	char anim_type = 'F';


	anim_atributes atr;
	atr.atr_resolver(atr, anim_type);
	animation a1(anim_type, atr.get_anim_pre(), atr.get_anim_im_qnt(),atr.get_period(),atr.get_spd());
	a1.p2anim_lib = a1.load_imgs(a1.get_anim_cant_img(), a1.get_anim_prefix());

	if (create_and_register_allegro_vars(timer,event_queue,display,a1.get_anim_per()) == -1) {
		return -1;
	}
	//variables para la animacion
	
	ALLEGRO_EVENT evs;

	int i = 0;
	float k = a1.get_speed();
	bool exit = 0;

	while (!exit) {
		al_get_next_event(event_queue, &evs);
		if (evs.type == ALLEGRO_EVENT_TIMER) {
			a1.play_anim(i, k,MAX_WIDTH,MAX_HEIGHT); // vamos a modificar k e i por eso las necesitamos
			if (k == 0) {
				exit = 1;
			}
		}
		else if(evs.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			exit = 1;
		}
		
	}

	al_destroy_display(display);
	return 0;
}




int allegro_init(ALLEGRO_DISPLAY *&disp) {
	if (!al_init()) {
		return -1;
	}
	if (!al_install_keyboard())
	{
		return -1;
	}

	if (!al_init_image_addon()) {
		return -1;
	}
	disp = al_create_display(MAX_WIDTH, MAX_HEIGHT);

	if (disp == nullptr) {
		return -1;
	}

	return 0;
}

int create_and_register_allegro_vars(ALLEGRO_TIMER *&timer,ALLEGRO_EVENT_QUEUE*& event_queue, ALLEGRO_DISPLAY *&display, float timer_period) {
	timer = al_create_timer(timer_period / 1000.0); // queremos en milisegundos
	if (!timer) {
		return -1;
	}
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_start_timer(timer);
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	return 0;
}

