#include "animation.h"

animation::animation(char name,string pref,unsigned int im_cant,double per, double vel)
{
	anim_id = name;
	anim_prefix = pref;
	anim_cant_img = im_cant;
	anim_period=per;
	speed=vel;
}

char& animation::get_anim_id(void)
{
	return anim_id;
}

float & animation::get_anim_per(void)
{
	return anim_period;
	// TODO: insertar una instrucción return aquí
}

float & animation::get_speed(void)
{
	return speed;
	// TODO: insertar una instrucción return aquí
}

string& animation::get_anim_prefix(void)
{
	return anim_prefix;
}

unsigned int& animation::get_anim_cant_img(void)
{
	return anim_cant_img;
}

void animation::play_anim(int& i, float& k, float MAX_SCREEN_WIDTH, float MAX_SCREEN_HEIGHT)
{

	al_clear_to_color(al_map_rgb(255, 255, 255));
	al_draw_bitmap(p2anim_lib[i], k, MAX_SCREEN_HEIGHT / 10.0, 1); // sobre 10.0 para que la imagen se centre
	al_flip_display();

	if (i < get_anim_cant_img() - 1) { // como son n imagenes entonces 
		i++;							// tengo que cortar en n-1 imagenes
	}
	else {
		i = 0;
	}
	if (k < (MAX_SCREEN_WIDTH - k)) {
		k += get_speed();
	}
	else {
		k = 0;
	}
}


animation::~animation()
{
}
