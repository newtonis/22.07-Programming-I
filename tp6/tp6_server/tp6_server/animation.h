#pragma once
#include <allegro5\allegro_image.h>
#include <vector>
#include <iostream>
#include <allegro5\allegro5.h>
#include <string>
using namespace std;

class animation
{
private:
	char anim_id;
	string anim_prefix;
	unsigned int anim_cant_img;
	double anim_period;
	double speed;
public:
	animation(char name,string pref, unsigned int im_cant,double per, double vel);
	
	void load_imgs(unsigned int qnt, string prefix, vector<ALLEGRO_BITMAP*>&, vector<ALLEGRO_BITMAP*>&);
	vector<ALLEGRO_BITMAP*> p2anim_lib;
	vector<ALLEGRO_BITMAP*> background;
	char& get_anim_id(void);
	double& get_anim_per(void);
	double& get_speed(void);
	string& get_anim_prefix(void);
	unsigned int& get_anim_cant_img(void);
	void play_anim(char anim_type,int& i, float& k, float MAX_SCREEN_WIDTH, float MAX_SCREEN_HEIGHT, bool& sense, unsigned int img_qnt);
	~animation();
};

