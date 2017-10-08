#pragma once
#include "img_anim.h"

class animation : public img_anim
{
private:
	char anim_id;
	string anim_prefix;
	unsigned int anim_cant_img;
	float anim_period;
	float speed;
public:
	animation(char name,string pref, unsigned int im_cant,double per, double vel);
	
	ALLEGRO_BITMAP ** p2anim_lib;
	char& get_anim_id(void);
	float& get_anim_per(void);
	float& get_speed(void);
	string& get_anim_prefix(void);
	unsigned int& get_anim_cant_img(void);
	void play_anim(int& i, float& k, float MAX_SCREEN_WIDTH, float MAX_SCREEN_HEIGHT);
	~animation();
};

