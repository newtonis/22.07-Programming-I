
#ifndef COMMON_STRUCTS_H
#define COMMON_STRUCTS_H

#define CNT_PARAMETERS 15

typedef struct {
	double x0, y0, xf, yf;
	int xMax, yMax;
    int lStart , lEnd;
    double leftAngle , rightAngle;
	double lConstant;

	char *type;
	int error;

	char *recv[CNT_PARAMETERS]; // received parameters list
	int recv_cnt;

}parameter_data; // to organize manderbrot input data

void init_data(parameter_data *data);
int find_in_data(char *key, parameter_data *data);
int check_params(parameter_data *data, char *params[] , int size);

#endif /* COMMON_STRUCTS_H */

