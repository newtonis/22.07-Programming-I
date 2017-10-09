
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

#include "boost/asio.hpp"
#include "boost/function.hpp"
#include "boost/bind.hpp"
#include <fstream>


using namespace std;



void mostrar_secuencia(char letra) {
	cout << "mostrando la secuencia " << letra << '\n';
	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			for (int z = 0; z < 100; z++) {

			}
		}
	 }
}

bool iniciar(vector <string> &direcciones,string mi_ip) {
	cout << "inciando \n";
	package_data data;
	data.actual = 0;
	preguntar_secuencia(&data.animation,data.seq,direcciones);
	data.cnt_maq = direcciones.size();

	
	if (mi_ip == direcciones[data.seq[0]]) { // empiezo yo!
		cout << "soy la maquina inicial, y empiezo yo la animacion \n";
		mostrar_secuencia(data.animation);
		data.actual++;
	}

	// pasamos a la siguiente
	{
		cout << "pasamos el mensaje al proximo en la lista \n";
		cout << "le toca a " << data.seq[data.actual] << "[" << direcciones[data.seq[data.actual]] << "]" << '\n';
		client my_client;
		my_client.startConnection(direcciones[data.seq[data.actual]].c_str());
		if (!my_client.success()) {
			cout << "could not connect, fatal error \n";
			return 0;
		}
		string msg = compose_msg(data);
		cout << "enviando ";
		cout << data << '\n';
		my_client.send_message(msg.c_str(), msg.size());
	
	}
	// esperamos que nos respondan
	{
		char ans[512]; int sz;
		cout << "Empezamos a escuchar, nos quedamos esperando a recibir un mensaje \n";
		server my_server;
		my_server.start_to_listen();
		my_server.wait_for_message(ans, &sz);

		string str_ans;
		complete_string(str_ans, ans, sz);

		decompose_msg(str_ans, data);
		cout << "se recibio \n";
		cout << data;
		if (data.actual == 0) {
			/// termino la animacion!
		} else {
			/// debemos mostrar la animacion, y despues responder el mensaje
			mostrar_secuencia(data.animation);
			client my_client;
			data.actual++;
			if (data.actual == data.cnt_maq) data.actual = 0;
			my_client.startConnection(direcciones[data.seq[data.actual]].c_str());
			string msg = compose_msg(data);
			cout << "se esta enviando \n";
			cout << data;
			my_client.send_message(msg.c_str(), msg.size());
		}
	}
	cout << "ya no hay nada mas que hacer \n";
	return 1;
}
bool escuchar(vector <string> &direcciones) {
	cout << "escuchando \n";
	/// escuchamos y respondemos
	server my_server;
	my_server.start_to_listen();
	char ans[512]; int sz;
	cout << "esperamos el mensaje . . . \n";
	my_server.wait_for_message(ans, &sz);
	string str_ans;
	complete_string(str_ans,ans, sz);

	package_data data;
	data.cnt_maq = direcciones.size();
	decompose_msg(str_ans, data);
	cout << "se recibio: \n";
	cout << data;
	/// mostramos la animacion correspondiente

	mostrar_secuencia(data.animation);

	/// respondemos

	data.actual++;
	if (data.actual == data.cnt_maq) data.actual = 0;

	client my_client;
	my_client.startConnection(direcciones[data.seq[data.actual]].c_str());
	if (!my_client.success()) {
		cout << "could not connect, fatal error \n";
		return 0;
	}
	cout << "enviando \n";
	cout << data;

	string msg = compose_msg(data);
	my_client.send_message(msg.c_str(),msg.size());

	cout << "nothing more to do \n";

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
	vector <string> direcciones;

	if (!leer_direcciones(direcciones)) {
		cout << "no se puede abrir el archivo de direcciones \n";
		return -1;
	}
	for (int i = 0; i < direcciones.size(); i++) {
		cout << i << ' ' << direcciones[i] << '\n';
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