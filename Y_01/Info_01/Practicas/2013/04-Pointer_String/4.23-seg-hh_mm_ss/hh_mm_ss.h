#ifndef hh_mm_ss
	#include <stdio.h>
	#include <stdlib.h>
	// #include <string.h>
	
	struct Hora{
		int seg;
		int min;
		int hs;
	};
	
	struct Hora hh_mm_ss(long int seconds);
#endif