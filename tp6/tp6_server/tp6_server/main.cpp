
#define _WIN32_WINNT 0x0501

#include <iostream>
#include <cstring>
#include <vector>
#include <time.h>
#include "server.h"
#include "client.h"
#include "parser.h"
#include "config.h"
#include "auxiliar.h"
#include "animation.h"
#include "anim_atributes.h"
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_audio.h>


#include "boost/asio.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include <fstream>
#include <time.h>


using namespace std;

const float MAX_WIDTH = 1280.0;
const float MAX_HEIGHT = 720.0;

int allegro_init();
bool blocking_anim(char letra, double width, double height);


void mostrar_secuencia(char& letra) {
	cout << "mostrando la secuencia " << letra << '\n';
	if (blocking_anim(letra, MAX_WIDTH, MAX_HEIGHT)) {
		cout << "la animacion " << letra << " se pudo realizar satisfactoriamente!" << endl;
	}
	else {
		cout << "hubo un error al tratar de reproducir animacion " << letra << " " << endl;
	}		
}

bool iniciar(vector <string> &direcciones,string mi_ip) {
	//cout << "inciando \n";
	package_data data;
	data.actual = 0;
	preguntar_secuencia(&data.animation,data.seq,direcciones);
	data.cnt_maq = direcciones.size();

	
	if (mi_ip == direcciones[data.seq[0]]) { // empiezo yo!
		//cout << "soy la maquina inicial, y empiezo yo la animacion \n";
		mostrar_secuencia(data.animation);
		data.actual++;
	}

	// pasamos a la siguiente
	{
		//cout << "pasamos el mensaje al proximo en la lista \n";
		//cout << "le toca a " << data.seq[data.actual] << "[" << direcciones[data.seq[data.actual]] << "]" << '\n';
		client my_client;
		my_client.startConnection(direcciones[data.seq[data.actual]].c_str());
		if (!my_client.success()) {
			cout << "could not connect, fatal error \n";
			return 0;
		}
		string msg = compose_msg(data);
		//cout << "enviando ";
		//cout << data << '\n';
		my_client.send_message(msg.c_str(), msg.size());
	
	}
	if (mi_ip == direcciones[data.seq[0]]) {
		return 1; // exito!	
	}
	// esperamos que nos respondan
	{
		char ans[512]; int sz;
		//cout << "Empezamos a escuchar, nos quedamos esperando a recibir un mensaje \n";
		//cout << "escuchando" << '\n';
		server my_server;
		my_server.start_to_listen();
		my_server.wait_for_message(ans, &sz);

		string str_ans;
		complete_string(str_ans, ans, sz);

		decompose_msg(str_ans, data);
		//cout << "se recibio \n";
		//cout << data;
		
		/// debemos mostrar la animacion, y despues responder el mensaje
		mostrar_secuencia(data.animation);
		client my_client;
		data.actual++;
		if (data.actual == data.cnt_maq) data.actual = 0;
		if (data.actual != 0) {
			my_client.startConnection(direcciones[data.seq[data.actual]].c_str());
			string msg = compose_msg(data);
			//cout << "se esta enviando \n";
			//cout << data;
			my_client.send_message(msg.c_str(), msg.size());
		}
		
	}
	//cout << "ya no hay nada mas que hacer \n";
	return 1;
}
bool escuchar(vector <string> &direcciones) {
	cout << "escuchando \n";
	/// escuchamos y respondemos
	server my_server;
	my_server.start_to_listen();
	char ans[512]; int sz;
	//cout << "esperamos el mensaje . . . \n";
	my_server.wait_for_message(ans, &sz);
	string str_ans;
	complete_string(str_ans,ans, sz);

	package_data data;
	data.cnt_maq = direcciones.size();
	decompose_msg(str_ans, data);
	//cout << "se recibio: \n";
	//cout << data;
	/// mostramos la animacion correspondiente

	mostrar_secuencia(data.animation);

	/// respondemos

	data.actual++;
	if (data.actual == data.cnt_maq) return 1; // no need to respond message

	client my_client;
	my_client.startConnection(direcciones[data.seq[data.actual]].c_str());
	if (!my_client.success()) {
		cout << "could not connect, fatal error \n";
		return 0;
	}
	//cout << "enviando \n";
	//cout << data;

	string msg = compose_msg(data);
	my_client.send_message(msg.c_str(),msg.size());

	//cout << "nothing more to do \n";

	return 1;
}


int parseCallback(char *key, char *value, void *userData);

class data_t {
	public:
		string ip;
		int iniciar;
		int bad;
		data_t() : ip("0.0.0.0"), iniciar(0) , bad(0){}
};

int main(char argc , char *argv[]) {

	//iniciliazacion de allegro
	if (allegro_init() == -1) {
		return -1;
	}

	vector <string> direcciones;

	if (!leer_direcciones(direcciones)) {
		//cout << "no se puede abrir el archivo de direcciones \n";
		return -1;
	}
	for (int i = 0; i < direcciones.size(); i++) {
		//cout << i << ' ' << direcciones[i] << '\n';
	}

	data_t data;
	
	parseCmdLine(argc, argv , parseCallback, (void*)&data);

	if (data.bad) {
		cout << "saliendo ... \n";
		return -1;
	} else if (data.ip == "0.0.0.0") {
		cout << "No se especifico IP ... \n";
		return -1;
	}

	if (data.iniciar) {
		cout << "comenzando como maquina que inicia \n";
		while (1) {
			if (!iniciar(direcciones,data.ip)) {
				break;
			}
		}
	} else {
		cout << "iniciando como maquina que escucha \n";
		while (1) {
			if (!escuchar(direcciones)) {
				break;
			}
		}
	}


	cout << "ending program \n";
	return 0;
}


int parseCallback(char *key, char *value, void *userData) {
	data_t *ud = (data_t*)userData;
	if (strcmp(key, "ip") == 0) {
		ud->ip = string(value);
		cout << "setting ip to " << value << '\n';
	}else if (strcmp(key,"iniciar") == 0) {
		ud->iniciar = 1;
		cout << "setting iniciar to 1 \n";
	} else {
		cout << "invalid parameter inserted \n";
		ud->bad = 1;
	}

	return 1;
}


int allegro_init(void) {
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

	if (!al_install_audio()) {
		return -1;
	}

	if (!al_init_acodec_addon()) {
		return -1;
	}

	if (!al_reserve_samples(1)) {
		return -1;
	}
	return 0;
}

bool blocking_anim(char letra, double width, double height) {
	ALLEGRO_DISPLAY * display = nullptr;
	ALLEGRO_SAMPLE * music = nullptr;

	display = al_create_display(width, height);
	if (display == nullptr) {
		return -1;
	}

	music = al_load_sample("Music/shooting_stars.wav");
	if (!music) {
		al_destroy_display(display);
		return -1;
	}

	al_play_sample(music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

	anim_atributes atr;
	atr.atr_resolver(atr, letra);
	animation a1(letra, atr.get_anim_pre(), atr.get_anim_im_qnt(), atr.get_period(), atr.get_spd());
	a1.load_imgs(a1.get_anim_cant_img(), a1.get_anim_prefix(), a1.p2anim_lib, a1.background);


	int i = 0;	float k = a1.get_speed(); bool exit = 0;

	while (!exit) {
		a1.play_anim(letra, i, k, width, height, atr.get_sense(), atr.get_anim_im_qnt());
		al_rest(atr.get_period() / 1000.0); // queremos milisegundos
		if (k == 0) exit = 1;
	}

	al_destroy_display(display);
	al_destroy_sample(music);

}