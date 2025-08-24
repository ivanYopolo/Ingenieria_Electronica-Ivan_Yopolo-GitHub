// Reordenar los Bytes de un INT 
// para pasar de LittleEndian (mayor-menor) a BigEndian (menor-mayor).

#include "Lendian_Bendian.h"

void LB_endian(int *numero){
	union campBit NumeroEntero;
	
	NumeroEntero.Num = *numero;
	
	unsigned char temp;
	printf("Número antes de LB_endian:\t\t\t0x%x\n", NumeroEntero.Num);
	for(int i = 0; i < 4; i++){		
		printf("Bytes antes de LB_endian:\t\t\t0x%x\n", NumeroEntero.Bytes[i]);
		switch(i){
			case 0:
				//																	  0x00001234
				printf("Bytes antes de LB_endian (CON MÁSCARA):\t\t0x%x\n", *numero & 0xFF000000);
				break;
			case 1:
				printf("Bytes antes de LB_endian (CON MÁSCARA):\t\t0x%x\n", *numero & 0x00FF0000);
				break;
			case 2:
				printf("Bytes antes de LB_endian (CON MÁSCARA):\t\t0x%x\n", *numero & 0x0000FF00);
				break;
			case 3:
				printf("Bytes antes de LB_endian (CON MÁSCARA):\t\t0x%x\n", *numero & 0x000000FF);
				break;
		}
	}
	
	for(int i = 0; i < 2; i++){
		temp = NumeroEntero.Bytes[i];
		NumeroEntero.Bytes[i] = NumeroEntero.Bytes[3 - i];
		NumeroEntero.Bytes[3 - i] = temp;
	}
	
	printf("\n###############################################\n");
	
	printf("\nNúmero después de LB_endian:\t\t\t0x%x\n", NumeroEntero.Num);
	
	for(int i = 0; i < 4; i++){		
		printf("Bytes después de LB_endian:\t\t\t0x%x\n", NumeroEntero.Bytes[i]);
	}
	
	
}