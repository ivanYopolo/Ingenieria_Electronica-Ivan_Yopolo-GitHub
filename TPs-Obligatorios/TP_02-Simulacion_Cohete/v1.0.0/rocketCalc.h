#ifndef rocketCalc
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	
	#include "structRocket.h"
	
	#define M_PI 3.14159265358979323846	// Pi.
	#define grav 9.81	// Gravedad [m/s^2].
	
	
	void showResults(int numRockets, int rocketSucc);

	void showData(struct Rocket rockData);

	// Velocidad mínima inicial, altura mínima.
	void rocketCalc(int minVel, int minH, int numRocket, int *rocketSucc, struct Rocket *rockTemp);
#endif
