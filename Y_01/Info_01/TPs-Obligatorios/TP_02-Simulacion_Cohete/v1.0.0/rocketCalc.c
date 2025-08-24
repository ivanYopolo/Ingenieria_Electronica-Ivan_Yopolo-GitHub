
/*
*****************ENCABEZADO DE FUNCION***********************
*
*  Informática I
*  Año: 2025
*  Nombre: Iván Yopolo

*  Descripcion: 
*  	En base a una masa dada [kg] del cohete, genera de manera
*	aleatoria fuerza y ángulos de lanzamiento, calcula velocidad
*	y altura, para verificar finalmente si se considera como
*	lanzamiento exitoso o fallido (luego de 3 intentos).

*  Formato de llamada:
*	rocketCalc(minVel, minH, currentRocket, &rocketSucc, &rocketTemp);

*  Argumentos:
*		* minVel: 		velocidad inicial mínima (límite); input del usuario.
*		* minH:			altura inicial mínima (límite); input del usuario.
*		* rocketSucc:	variable booleana (char) para determinar si el cohete fue exitoso
						o no en su lanzamiento; cambia dentro de la función (se pasa
						por referencia).
*		* rocketTemp:	struct TEMPORAL con datos cruciales por cada cohete, como:
						intentos, número del cohete actual, masa, fuerza y ángulo
						generados en cada intento, energías potencial y cinética
						calculadas por intento, etc.

*  Retorno: VOID.

*  Observaciones: ...
*/

#include "rocketCalc.h"

void rocketCalc(int minVel, int minH, int numRocket, int *rocketSucc, struct Rocket *rockTemp){
	float rendTemp = 0;	// Temporal del rendimiento.
	int flaw = 0;		// Penalización.
	int i = 0;
	
	
	
	srand(rockTemp -> Current);	// Semilla para el "número pseudo-random".
	
	printf(
		"\n\n\nMasa [kg] del cohete [ %d ]:    ", numRocket);
	scanf("%d", &(rockTemp -> Mass));
	
	// Máximo 3 intentos:
	for(i = 0; i < 3; i++){
		// rand() % (ValorMáximo-ValorMínimo+1) + (ValorMínimo);
		// rand() devuelve valores entre 0 y una constante grande. Con % se puede sacar el "resto"
		// del resultado, obteniendo efectivamente el rango deseado.
		rockTemp -> RandForce[i] = rand() % 1001 + 500;	// 500 <= F <= 1500.
		rockTemp -> RandAngle[i] = rand() % 61 + 30;	// 30 <= ángulo <= 90.
		
		// PASAR ÁNGULO A RADIANES.
		rockTemp -> RandAngleRAD[i] = rockTemp -> RandAngle[i] * M_PI / (float) 180;
		
		// math.h calcula en radianes:
		rockTemp -> CosAngle = cos(rockTemp -> RandAngleRAD[i]);
		rockTemp -> SinAngle = sin(rockTemp -> RandAngleRAD[i]);
		
		// Cálculo de velocidad y altura (masa en [T] = [kg/1000]):
		// ### REVISAR FÓRMULAS ###
		rockTemp -> Velocity[i] = (rockTemp -> CosAngle) * 1000 * (float) (rockTemp -> RandForce[i]) / (float) (rockTemp -> Mass);
		rockTemp -> Height[i] = (rockTemp -> SinAngle) * 1000 * (float) (rockTemp -> RandForce[i]) / (float) (rockTemp -> Mass);
		
		// Cálculo de Ep y Ec:
		rockTemp -> eC[i] = 0.5 * (float) (rockTemp -> Mass) * (float) (rockTemp -> Velocity[i]) * (float) (rockTemp -> Velocity[i]);
		rockTemp -> eP[i] = (float) (rockTemp -> Mass) * grav * (float) (rockTemp -> Height[i]);
		
		// Cálculo Rendimiento (eC/eM) [%]:
		rendTemp = -flaw + 100 * rockTemp -> eC[i] / (rockTemp -> eC[i] + rockTemp -> eP[i]);
		
		// Clasificación Rendimiento:
		if(80 < rendTemp){						// 80% eM < eC <= 100% eM
			strcpy(rockTemp -> PerfMes[i], "Excelente");
		}
		if(50 < rendTemp && rendTemp <= 80){	// 50% eM < eC <= 80% eM
			strcpy(rockTemp -> PerfMes[i], "Bueno");
		}
		if(20 < rendTemp && rendTemp <= 50){	// 20% eM < eC <= 50% eM
			strcpy(rockTemp -> PerfMes[i], "Regular");
		}
		if(rendTemp <= 20){						// 0 < eC <= 20% eM
			strcpy(rockTemp -> PerfMes[i], "Deficiente");
		}
		
		rockTemp -> Attempt = i + 1;
		
		// Si alcanzó los valores mínimos, para de hacer intentos:
		if(rockTemp -> Velocity[i] >= minVel && rockTemp -> Height[i] >= minH){
			rockTemp -> Success = 1;	// Intento exitoso (mínimo 1 exitoso).
			// Incrementar número de cohetes exitosos:
			(*rocketSucc)++;
			break;
		}
		
		// Si no llegó a la altura mínima, aplicar penalización del 5% al rendimiento:
		if(rockTemp -> Height[i] < minH){
			flaw += 5;
		}
		
		// Si no llegó a los 3 intentos, es FALLIDO:
		rockTemp -> Success = 0;	// Intento fallido (3 lanzamientos fallidos).
	}
	
	// Mostrar datos por cohete, al finalizar los 3 intentos:
	// Como se tiene un POINTER al STRUCT original, se "desreferencia" ese pointer.
	showData(*rockTemp);
}



/*
*****************ENCABEZADO DE FUNCION***********************
*
*  Informática I
*  Año: 2025
*  Nombre: Iván Yopolo
*
*  Descripcion: 
*	Muestra datos en pantalla del struct "rockData" y la
*	gran mayoría de sus objetos/variables (excepto las temporales
*	y exclusivas de cálculo).
*
*  Formato de llamada: 
*	showData(rockTemp);
*
*  Argumentos: 
*	rockTemp:			struct pasado por valor para copiarlo
*						e imprimir en pantalla  todos sus datos.
*
*  Retorno: VOID.
*
*  Observaciones: ...
*/

void showData(struct Rocket rockData){
/*
	Mostrar:
		* N° intentos.
		* Ángulo de lanzamiento.
		* Fuerza.
		* Velocidad calculada.
		* Altura calculada.
		* Ec.
		* Ep.
		* Rendimiento del cohete.
*/
	printf(
	"\n\n### DATOS DEL COHETE N°            [ %d ] ###\n", rockData.Current);
	
	printf(
	"\nN° de Intentos:                    [ %d ]\n", rockData.Attempt);
	
	// Datos/intento:
	for(int i = 0; i < (rockData.Attempt); i++){
		printf(
	"\nIntento:                           [ %d ]\n", i+1);
		printf(
	"\nÁngulo de lanzamiento %d [DEG]:     [ %.2f ]", i+1, rockData.RandAngle[i]);
		printf(                                     
	"\nFuerza de empuje %d [N]:            [ %.2f ]", i+1, rockData.RandForce[i]);
		printf(                                       
	"\nVelocidad inicial %d [m/s]:         [ %.2f ]", i+1, rockData.Velocity[i]);
		printf(                                        
	"\nAltura inicial %d [m]:              [ %.2f ]", i+1, rockData.Height[i]);
		printf(
	"\nEnergía Cinética %d [J]:            [ %.2f ]", i+1, rockData.eC[i]);
		printf(                                          
	"\nEnergía Potencial %d [J]:           [ %.2f ]\n", i+1, rockData.eP[i]);
		printf(                                          
	"\nRendimiento %d:                     [ %s ]\n", i+1, rockData.PerfMes[i]);	
		// printf(
	// "############################################\n");
	}
	
	printf(
	"\n¿Lanzamiento de cohete exitoso?    ");
	switch(rockData.Success){
		case 1:
			printf("[ SÍ ]");
			break;
		case 0:
			printf("[ NO ]");
			break;
	}
	printf(
	"\n############################################\n");
}



/*
*****************ENCABEZADO DE FUNCION***********************
*
*  Informática I
*  Año: 2025
*  Nombre: Iván Yopolo
*
*  Descripcion: 
*	Muestra datos FINALES en pantalla: el porcentaje de éxito
*	de cohetes que alcanzaron la "órbita segura".
*
*  Formato de llamada: 
*	showData(rockTemp);
*
*  Argumentos: 
*	rockTemp:			struct pasado por valor para copiarlo
*					e imprimir en pantalla  todos sus datos.
*
*  Retorno: VOID.
*
*  Observaciones: ...
*/

void showResults(int numRockets, int rocketSucc){
/*
	Mostrar:
		* Porcentaje de éxito de cuantos cohetes llegaron a órbita segura.
*/
	// 100 * rocketSucc / numRockets
	printf(
	"\n\nEl porcentaje de éxito de cohetes lanzados \n"
	"que alcanzaron órbita segura fue de:           ");
	printf("[ %.2d %% ]\n\n", 100 * rocketSucc / numRockets);
}


