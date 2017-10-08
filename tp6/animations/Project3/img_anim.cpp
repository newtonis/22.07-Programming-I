#include "img_anim.h"




img_anim::img_anim()
{
	p2imglib = nullptr;
}

ALLEGRO_BITMAP**& img_anim::load_imgs(unsigned int qnt,string prefix) {
	string extension = ".png";
	ALLEGRO_BITMAP ** auxlib= new ALLEGRO_BITMAP*[qnt];
	for (unsigned int i = 0; i < qnt; i++) { // el 1 es por F1, F2.. etc
		string aux = prefix + to_string(i + 1) + extension;
		auxlib[i] = al_load_bitmap(&aux[0]);

	}
	return auxlib;
}




img_anim::~img_anim()
{
	if (p2imglib != nullptr) {
		delete[] p2imglib;
	}
}
