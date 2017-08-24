#include "triag.h"

const double PI = 3.141592;

const double LSTARTMIN = 0;
const double LSTARTMAX = 400;
const double RIGHTANGLEMIN = -90.0;
const double RIGHTANGLEMAX = 0.0;
const double LEFTANGLEMIN = 0.0;
const double LEFTANGLEMAX = 90.0;

int verify_triang(parameter_data *p2trivar) {
	const double RADIUS = 200.0;
	const double X0MIN = p2trivar->xMax / 2.0 - RADIUS;
	const double X0MAX = p2trivar->xMax / 2.0 + RADIUS;
	const double Y0MIN = p2trivar->yMax / 2.0 - RADIUS;
	const double Y0MAX = p2trivar->yMax / 2.0 + RADIUS;


	int success = 1;
	if (! (p2trivar->x0 < X0MAX && p2trivar->x0 > X0MIN) ){
		success = 0;
	}else if (! (p2trivar->y0 > Y0MIN && p2trivar->y0 < Y0MAX) ) {
		success = 0;

	}else if (! (p2trivar->lStart > LSTARTMIN && p2trivar->lStart <= LSTARTMAX) ) {
		success = 0;

		
	}else if (! (p2trivar->lEnd >0  && p2trivar->lEnd < p2trivar->lStart)) {
	//	(p2trivar->lStart / 0.0)
		success = 0;
	}else if (! (p2trivar->rightAngle < RIGHTANGLEMAX && p2trivar->rightAngle  > RIGHTANGLEMIN)){
		success = 0;
	}else if (! (p2trivar->leftAngle > LEFTANGLEMIN && p2trivar->leftAngle < LEFTANGLEMAX)) {
		success = 0;
	}

	return success;
}

void get_three_coords(parameter_data * p2triag, bordes_t *p2aux) {
	/* se tiene que definir las primeras tres coordenadas para poder ejecutar la funcion recursiva
	y se realizo mediante relaciones trigonometricas*/

	double l1, l2;

	l2 = p2triag->lStart / (1 + (tan((p2triag->rightAngle + 90.0)* PI / 180.0) / tan((p2triag->leftAngle) * PI / 180.0)));

	l1 = p2triag->lStart - l2;

	int y1 = l1* tan(p2triag->leftAngle * PI / 180.0);

	p2aux->arriba.x = p2triag->x0;

	p2aux->arriba.y = p2triag->yMax - (p2triag->y0 + (y1* 2.0 / 3.0));

	p2aux->derecha.x = p2triag->x0 + l2;

	p2aux->derecha.y = p2triag->yMax - (p2triag->y0 - (y1 / 3.0));

	p2aux->izq.x = p2triag->x0 - l1;


	p2aux->izq.y = p2triag->yMax - (p2triag->y0 - (y1 / 3.0));

}

void dibujar(pos_t p1, pos_t p2, pos_t p3, double lend, int loop, double *small, unsigned int arr_color[][3]) {
	// podemos pensar el triangulo como un grafo 3-ario
	// donde cada triangulo "padre" tiene 3 "hijos" por cada nivel cada hijo se vuelve padre
	// y cada uno de esos nuevos padres vuelve a tener 3 hijos cada uno

	if (small[loop - 1]> lend) {


		// primero dibujamos al padre
		small[loop] = min(small[loop], lado(p1, p2, p3));
		pos_t p4 = calculate_new_cm(p1, p2, p3);

		// y despues sus hijos
		dibujar(p1, p2, p4, lend, loop + 1, small,arr_color);
		dibujar(p2, p3, p4, lend, loop + 1, small,arr_color);
		dibujar(p1, p3, p4, lend, loop + 1, small,arr_color);

		al_draw_triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, al_map_rgb(arr_color[loop][0], arr_color[loop][1], arr_color[loop][2]), 1.0);

	}
}
void precomputar_orden(pos_t p1, pos_t p2, pos_t p3, double lend, int loop, double *small) {
	if (small[loop - 1]> lend) {

		small[loop] = min(small[loop], lado(p1, p2, p3));
		// tenemos dos condiciones de corte 
		// o bien por profundidad del grafo o por que alguno de los lados supero a lend

		pos_t p4 = calculate_new_cm(p1, p2, p3);

		precomputar_orden(p1, p2, p4, lend, loop + 1, small);
		precomputar_orden(p2, p3, p4, lend, loop + 1, small);
		precomputar_orden(p1, p3, p4, lend, loop + 1, small);
	}
}

double distance(pos_t p1, pos_t p2) {

	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));

}

double lado(pos_t p1, pos_t p2, pos_t p3) {

	return min(distance(p1, p3), min(distance(p1, p2), distance(p2, p3)));

}

pos_t calculate_new_cm(pos_t p1, pos_t p2, pos_t p3) {
	pos_t p4;
	p4.x = (p1.x + p2.x + p3.x) / 3.0;
	p4.y = (p1.y + p2.y + p3.y) / 3.0;
	return p4;
}


void plot_triangle(parameter_data * p2tri) {

	double profundidad[20];
	for (int i = 0; i < 19; i++) {
		profundidad[i] = 1e6;
	}
	unsigned int color_arr[20][3];
	unsigned int aux=1;

	srand(time(NULL));

	for (int l = 0; l < 20; l++) {
		for (int k = 0; k < 3; k++) {
			color_arr[l][k] = rand() % 256;

			printf("%u ",color_arr[l][k]);
		}
		printf("\n");
	}
	

	bordes_t main_borde;
	bordes_t *p2borde = &main_borde;

	get_three_coords(p2tri, p2borde);

	precomputar_orden(p2borde->arriba, p2borde->derecha, p2borde->izq, p2tri->lEnd, 1, profundidad);

	dibujar(p2borde->arriba, p2borde->derecha, p2borde->izq, p2tri->lEnd, 1, profundidad,color_arr);

}
