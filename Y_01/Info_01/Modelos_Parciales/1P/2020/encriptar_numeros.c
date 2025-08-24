/*
Para encriptar los números del string el procedimiento será el siguiente: se debe
convertir el número en octal, para luego reemplazar cada uno de sus dígitos por los
siguientes caracteres:
0 $
1 %
2 &
3 *
4 @
5 !
6 +
7 =
Adicionalmente, se debe agregar el carácter # tanto al comienzo como al final del numero
encriptado.
*/

#include "desplazar_letras.h"

void encriptar_numeros(char *strI, char *strO){
	strcpy(strO, strI);
	
	
	for(int i = 0; i < strlen(strI); i++){
		decOct(strO, i);
		/*
		switch(strI[i]){
			case '0':
				strO[i] = '$';
				break;
				
			case '1':
				strO[i] = '%';
				break;
				
			case '2':
				strO[i] = '&';
				break;
				
			case '3':
				strO[i] = '*';
				break;
				
			case '4':
				strO[i] = '@';
				break;
				
			case '5':
				strO[i] = '!';
				break;
				
			case '6':
				strO[i] = '+';
				break;
				
			case '7':
				strO[i] = '=';
				break;
		}
		*/
	}
}



/* 
#####################
HACER DIVISIÓN SUCESIVA.
#####################
	1) Dividir por 8.
	2) Guardar el resto.
	3) IF resultado es 0:
		3.a) STOP.
		3.b) Guardar secuencia de "restos" en orden inverso. Dicha secuencia es N° en octal.
	4) ELSE:
		4.a) Seguir dividiendo.
*/

void decOct(char *strO, int pos){	
	// char strTemp[strlen(strO)];
	char octTemp[strlen(strO) * 2];	// Donde se va a guardar la secuencia de restos, el número en octal.
	char div = 1;	// Variable para verificar si dividir o no.
	
	// Es número?
	if(strO[pos] >= '0' && strO[pos] <= '9'){
		
		while(div){
			if(strO[pos] / 8){
				
			}
		}
		
		
		
		
		
		
		
		// Octal calculado:
		printf("\nOctal [%d]:\t%s", pos, octTemp);
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*
		// Posición menor a la última:
		if(pos < strlen(strO)){
			// Se copia desde la posición siguiente al número tomado.
			strcpy(strTemp, strO + pos + 1);
		}else{	// Posición final:
			strcpy(strTemp + pos, " ");
		}
	
		// Se toma el octal.
		sprintf(octTemp, "%d", ('0' + (int)strO[pos] / 8));
		
		printf("\nOctal [%d]:\t%s", pos, octTemp);
		
		// Se concatenan (o sobreescriben) los strings en orden:
			// 1) strO
			// 2) octTemp
			// 3) strTemp
		// strncat(strO, octTemp);
		// strcpy(strO + strlen(octTemp), strTemp);
		
		// strncat(octTemp, strTemp, strlen(strTemp));
		// strcpy(strO + strlen(octTemp), octTemp);
		*/
	}
}


