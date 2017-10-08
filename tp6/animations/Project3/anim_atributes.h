#pragma once
#include <iostream>
using namespace std;
class anim_atributes
{
private:
	string anim_pre;
	unsigned int anim_im_qnt;
	float period;
	float spd;
	bool sense;
public:
	anim_atributes();
	void atr_resolver(anim_atributes& atr, char anim_type);


	void set_anim_pre(string s);
	void set_anim_im_qnt(unsigned int q);
	void set_period(float p);
	void set_spd(float s);
	void set_sense(bool);

	string& get_anim_pre(void);
	unsigned int& get_anim_im_qnt(void);
	float& get_period(void);
	float& get_spd(void);
	bool& get_sense(void);

	~anim_atributes();
};

