/*
Escribir una función que permita evaluar una función polinómica en un punto, a
partir de un vector de coeficientes y su grado recibidos como parámetros. 

*/


#include <stdio.h>
#define GRAD_POL 4

double PolinomioX( double Coef[], int Grado, double Variable );


int main(){
	// Pos. 0: grado 0.
	// Pos. n: grado n.
	double Coef[ GRAD_POL + 1 ] = { 4, 6, 2, -3, ( double )5/7 };
	double Variable = 0;
	
	printf( "\n# Polinomio completo #\n" );
	
	for( int i = 0; i < GRAD_POL + 1; i++ ){
		printf( "%.6lf * x^%d  +  ", Coef[ i ], i );
	}
	
	printf( "\nElija un valor para evaluar la función polinómica:\t" );
	scanf( "%lf", &Variable );
	
	// printf( "\nVariable:\t\t%.6lf", Variable );
	
	double imagenPol = PolinomioX( Coef, GRAD_POL, Variable );
	
	printf( "\n\nLa imagen de la función en %.6lf es:\t\t%.6lf\n\n", Variable, imagenPol );
	
	return 0;
}


/*
# Mejoramiento 0 #
	Asumir coeficientes de menor grado primero.
	
	Multiplicar cada coeficiente por la variable elegida.
	
	Repetir hasta completar el grado (tamaño del array).
*/
	
/*
# Mejoramiento 1 #
	Si variable o el grado es 0: devuelve el coeficiente independiente (grado 0).
	
	Mientras el número de multiplicaciones "i" sea menor al grado:
		
		Multiplicar la variable de input por el coeficiente "i-ésimo". 
		Guardar sumatoria en una variable de salida tipo double.
		
		Sumar el contador "i" en 1.
*/	
		
/*		
# Mejoramiento 2 #
	Si "variable" o el "grado" es 0: devuelve el coeficiente independiente (grado 0).
	
	SUMATORIA TÉRMINOS
	Mientras el "término" sea menor o igual al "grado":
		
		POTENCIA:
		PARA un contador "multiplicacion" y "variablePotenciada" igual a 1;
		mientras "multiplicacion" sea menor o igual que el "término" (grado del término); 
		sumar "multiplicacion" en 1:
			
			Multiplicar "Variable" con "variablePotenciada" y guardarlo en "variablePotenciada",
			sumado a su valor antiguo (*=).
				
		Multiplicar "Coef" en posición "término" por "variablePotenciada" y 
		guardarlo en "imagenPolinomioX", sumado a su valor antiguo (+=).
		
		Poner "variablePotenciada" en 1.		
		
		Sumar el "termino" en 1.
*/

double PolinomioX( double Coef[], int Grado, double Variable ){
	double 	imagenPolinomioX = 0;		// Resultado imagen del polinomio evaluado en "Variable".
	double 	variablePotenciada = 1;		// Variable para algoritmo potenciación.
	int 	termino = 0;				// Exponente de cada término del polinomio (empieza en 0).
	int 	multiplicacion = 1;			// Para contar las multiplicaciones (potencia) en cada exponente.
	// Se toma el "Grado" como el tamaño - 1; la última posición del array.
	
	
	// Caso grado 0 o X = 0.
	if( Grado == 0 || Variable == 0 ){
		
		imagenPolinomioX = Coef[ 0 ];	// Guarda el término independiente solamente.
	}else{
	
		// Sumatoria de términos.
		for( termino = 0; termino <= Grado; termino++ ){
			
			printf( "\n\n### Término %d ###", termino );
			
			// Potenciación.
			for( multiplicacion = 1, variablePotenciada = 1; multiplicacion <= termino; multiplicacion++ ){
				
				variablePotenciada *= Variable;
			}	// Terminó la potencia, procede a multiplicar por coeficiente.
			
			// y = a * x^n
			printf( "\n[ IMAGEN = %.6lf + %.6lf * %.6lf", imagenPolinomioX, Coef[ termino ], variablePotenciada );
			
			imagenPolinomioX = imagenPolinomioX + Coef[ termino ] * variablePotenciada;
			
			printf( " = %lf ]", imagenPolinomioX );
		}	
	}
	
	return imagenPolinomioX;	// Retorna el resultado imagen.
}

