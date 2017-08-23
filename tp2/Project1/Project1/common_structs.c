#include "common_structs.h"


void init_data(parameter_data *data) {
	data->error = 0;
	data->recv_cnt = 0;
}

int find_in_data(char *key,parameter_data *data) {

	for (int i = 0; i < data->recv_cnt; i++) {
		if (strcmp(data->recv[i],key) == 0){
			return 1;
		}
	}
	return 0;
}


check_params(parameter_data *data, char *params[], int size) {
	
	if (data->recv_cnt > size) {
		return 0; //excess of parameters
	}
	for (int i = 0; i < size; i++) {
		if (!find_in_data(params[i],data)) {
			return 0; // parameter was not found
		}
	}
	

	return 1;
}