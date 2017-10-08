#include "anim_atributes.h"

anim_atributes::anim_atributes()
{
}

void anim_atributes::set_anim_pre(string s)
{
	anim_pre = s;
}

void anim_atributes::set_anim_im_qnt(unsigned int q)
{
	anim_im_qnt = q;
}

void anim_atributes::set_period(float  p)
{
	period = p;
}

void anim_atributes::set_spd(float  s)
{
	spd = s;
}

string & anim_atributes::get_anim_pre(void)
{
	return anim_pre;
	// TODO: insertar una instrucción return aquí
}

unsigned int & anim_atributes::get_anim_im_qnt(void)
{
	return anim_im_qnt;
	// TODO: insertar una instrucción return aquí
}

float & anim_atributes::get_period(void)
{
	return period;
	// TODO: insertar una instrucción return aquí
}

float & anim_atributes::get_spd(void)
{
	return spd;
	// TODO: insertar una instrucción return aquí
}

void anim_atributes::atr_resolver(anim_atributes& atr,char anim_type) {
	switch (anim_type) {

	case 'A':
		atr.set_anim_pre("Pictures/Cat Running/Cat Running-F");
		atr.set_anim_im_qnt(12);
		atr.set_period(100.0);
		atr.set_spd(2.0);
		break;
	case 'B':
		atr.set_anim_pre("Pictures/Explosion 1/Explosion 1-F");
		atr.set_anim_im_qnt(8);
		atr.set_period(120.0);
		atr.set_spd(0.0);
		break;
	case 'C':
		atr.set_anim_pre("Pictures/Explosion 2/Explosion 2-F");
		atr.set_anim_im_qnt(48);
		atr.set_period(100.0);
		atr.set_spd(0.0);
		break;
	case 'D':
		atr.set_anim_pre("Pictures/Homer Dance/homerdance-F");
		atr.set_anim_im_qnt(10);
		atr.set_period(100.0);
		atr.set_spd(100.0);
		break;
	case 'E':
		atr.set_anim_pre("Pictures/Super Mario/Super Mario Running-F");
		atr.set_anim_im_qnt(12);
		atr.set_period(40.0);
		atr.set_spd(2.0);
		break;

	case 'F':
		atr.set_anim_pre("Pictures/Sonic/Sonic Running-F");
		atr.set_anim_im_qnt(10);
		atr.set_period(100.0);
		atr.set_spd(2.0);
		break;
	default:
		break;
	}
}

anim_atributes::~anim_atributes()
{
}
