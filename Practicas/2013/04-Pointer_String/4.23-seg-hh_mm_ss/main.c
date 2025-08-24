
#include "hh_mm_ss.h"

int main(){
	long int seconds = 0;
	
	struct Hora time;
	
	time.seg = 0;
	time.min = 0;
	time.hs = 0;
	
	system("clear");
	
	printf("Ingrese los segundos a convertir (ss -> hh/mm/ss):\t\t");
	scanf("%ld", &seconds);
	
	time = hh_mm_ss(seconds);
	
	printf(
	"\nTiempo: \t%2d:%2d:%2d\n", time.hs, time.min, time.seg);
	
	return 1;
}