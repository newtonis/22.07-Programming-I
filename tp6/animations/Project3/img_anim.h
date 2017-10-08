#pragma once
#include <iostream>
#include <string>
#include <allegro5\allegro5.h>
#include <allegro5\allegro_image.h>

using namespace std;
class img_anim
{

private:
	ALLEGRO_BITMAP * p2imglib;
public:
	img_anim();
	ALLEGRO_BITMAP**& img_anim::load_imgs(unsigned int qnt, string prefix);
	~img_anim();
};

