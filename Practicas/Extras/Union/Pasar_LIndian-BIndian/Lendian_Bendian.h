#ifndef Lendian_Bendian
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	// struct bytes{
		// char
	// };
	
	union campBit{
		unsigned char Bytes[4];
		int Num;
	};
	
	void LB_endian(int *numero);
#endif