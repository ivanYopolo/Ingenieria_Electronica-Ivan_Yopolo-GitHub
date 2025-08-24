#include "hh_mm_ss.h"


struct Hora hh_mm_ss(long int seconds){
	struct Hora tiempo;
	
	
	// Revisar decimal -> sexagesimal.
	tiempo.min = (int)seconds / 60;		// Parte entera = minutos.
	tiempo.seg = (int)seconds % 60;		// Resto = segundos.
	tiempo.hs = (int)tiempo.min / 60;	// Parte entera = horas.
	tiempo.min = (int)tiempo.min % 60;	// Resto = minutos.
	
	return tiempo;
}
