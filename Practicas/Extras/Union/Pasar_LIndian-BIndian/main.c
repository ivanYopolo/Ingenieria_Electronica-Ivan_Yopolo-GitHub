// Reordenar los Bytes de un INT 
// para pasar de LittleEndian (mayor-menor) a BigEndian (menor-mayor).

#include "Lendian_Bendian.h"

int main(){
	int num;
	
	system("clear");
	
	printf("Ingrese el número:\t\n");
	scanf("%d", &num);
	
	LB_endian(&num);
	
	return 1;
}