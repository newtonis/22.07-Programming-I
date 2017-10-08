#include <iostream>
#include "animation.h"
#include "anim_atributes.h"

const float MAX_WIDTH = 1280.0;
const float MAX_HEIGHT = 720.0;

using namespace std;

int allegro_init(ALLEGRO_DISPLAY *&);

int main(void)
{
	ALLEGRO_DISPLAY * display = nullptr;

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


	//variables para la animacion

	int i = 0;
	float k = a1.get_speed();
	bool exit = 0;

	while (!exit) {
		a1.play_anim(anim_type,i, k,MAX_WIDTH,MAX_HEIGHT,atr.get_sense(),atr.get_anim_im_qnt()); 
		al_rest(atr.get_period() / 1000.0);
		if (k == 0) {
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


