/*
Escribir una función que reciba una matriz cuadrada de doubles y su dimensión,
y retorne el valor de su determinante.

Comprobar su correcto funcionamiento contrastando el resultado del
algoritmo con matlab.
*/

#include <stdio.h>

#define D1 3

// Matriz 3x3.
double detCalc(double mC[][D1]);

// Hacer producto vectorial.
int main(){
	// Matriz 3x3 (cuadrada).
	double matrizX[D1][D1];
	
	// Ingreso de datos para la matriz 3x3:
	printf("\nComplete la matriz con números: \n");
	
	// Filas.
	for(int i = 0; i < D1; i++){
		// Columnas.
		for(int j = 0; j < D1; j++){
			printf("\n\nFila: %d", i);
			printf("\nColumna: %d\n", j);
			
			printf("\n\nValor:  ");
			scanf("%lf", &matrizX[i][j]);
		}
	}
	
	double determinante = detCalc(matrizX);
	printf("\nLa matriz tiene determinante de:  %lf\n", determinante);
	
	return 1;
}

// Hay que pasarle COMO NÚMERO DEFINIDO el tamaño de TODAS LAS DIMENSIONES menos la primera (columnas).
// Así, C sabe el "salto" entre dimensiones.
// Si se pasa como "**mc", no funciona más la sintaxis de matrices/pointers.
double detCalc(double mC[][D1]){
	double determinante = 0;
	int colDet1 = 0;
	int colDet2 = 0;
	
	// Producto vectorial; se toman los primeros valores de la fila 1:
	for(int i = 0; i < D1; i++){
		// Fila 0; Columna "i":
		// 00 * (11*22 - 21*12)
		// 0i * (1(i+1)*2(i+2) - 2(i+1)*1(i+2))
		switch(i){
			case 0:
				colDet1 = 1;
				colDet2 = 2;
				determinante += mC[0][i] * ((mC[1][colDet1]*mC[2][colDet2]) - (mC[2][colDet1]*mC[1][colDet2]));
				break;
			
			case 1:
				colDet1 = 0;
				colDet2 = 2;
				determinante -= mC[0][i] * ((mC[1][colDet1]*mC[2][colDet2]) - (mC[2][colDet1]*mC[1][colDet2]));
				break;
			
			case 2:
				colDet1 = 0;
				colDet2 = 1;
				determinante += mC[0][i] * ((mC[1][colDet1]*mC[2][colDet2]) - (mC[2][colDet1]*mC[1][colDet2]));
				break;
		}
		
	}
	
	return determinante;
}
