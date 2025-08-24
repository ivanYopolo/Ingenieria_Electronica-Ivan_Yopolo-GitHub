#include "my_strcpy.h"


// Copiar "s" en "t" + '\0' al final.
void my_strcpy(char *t, const char *s){
	printf("\nTamaño mensaje:\t\t%d", (int)strlen(s));
	
	for(int i = 0; i < strlen(s); i++){
		t[i] = s[i];
	}
	t[strlen(s)] = '\0';
}
