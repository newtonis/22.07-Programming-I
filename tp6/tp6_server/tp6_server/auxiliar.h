#ifndef AUXILIAR_H
#define AUXILIAR_H

#include <string>
#include <vector>
#include "config.h"

using namespace std;


/// data that has to be sent
struct package_data {
	int seq[MAX_MAQUINAS];
	int cnt_maq;
	int actual;
	char animation;
};

string compose_msg(package_data &data);
void decompose_msg(string msg, package_data &data);

void preguntar_secuencia(char *letra, int seq[MAX_MAQUINAS], vector <string> &direcciones);
int leer_direcciones(vector <string> &direcciones);


#endif