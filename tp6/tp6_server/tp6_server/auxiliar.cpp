#include <fstream>
#include <iostream>
using namespace std;

#include "auxiliar.h"


ostream& operator<<(ostream& o,package_data& data) {
	cout << "actual: " << data.actual << '\n';
	cout << "animacion: " << data.animation << '\n';
	cout << "cantidad: " << data.cnt_maq << '\n';
	cout << "secuencia: ";
	for (int i = 0; i < data.cnt_maq; i++) {
		cout << data.seq[i] << ' ' << '\n';
	}
	return o;
}


string compose_msg(package_data &data) {
	string ans = "";
	ans.push_back(data.animation);
	ans.push_back(data.actual);
	for (int i = 0; i < data.cnt_maq; i++) {
		ans.push_back(data.seq[i]);
	}
	return ans;
}
void decompose_msg(string msg, package_data &data) {
	data.animation = msg[0];
	data.actual = msg[1];
	int j = 2;
	for (int i = 0; i < data.cnt_maq; i++) {
		data.seq[i] = msg[j++];
	}
}

int leer_direcciones(vector <string> &direcciones) {
	ifstream myfile;
	myfile.open(DIRECCIONES_FILE);

	if (!myfile.is_open()) {
		return 0;
	}
	string line;

	while (getline(myfile, line)) {
		cout << line << '\n';
		direcciones.push_back(line);
	}

	myfile.close();


	return 1;
}

void preguntar_secuencia(char *letra, int seq[MAX_MAQUINAS], vector <string> &direcciones) {

	bool invalid_letter;

	do {
		cout << "indique animacion: ";
		cin >> *letra;
		invalid_letter = (*letra) < 'A' || (*letra) > 'F';
		if (invalid_letter) {
			cout << "letra invalida insertada \n";
		}
	} while (invalid_letter);
	int used[MAX_MAQUINAS];
	fill(used, used + direcciones.size(), 0);

	for (int i = 0; i < direcciones.size(); i++) {
		int val;
		bool invalid;
		do {
			cout << "indique pc " << i << " de la secuencia:";
			cin >> val;

			invalid = val < 0 || val >= direcciones.size() || used[val];
			if (invalid) cout << "indico una opcion invalida\n";
		} while (invalid);
		seq[i] = val;
		used[val] = 1;
	}
	cout << "{";
	for (int i = 0; i < direcciones.size(); i++) {
		cout << seq[i] << ',';
	}
	cout << "}";
}