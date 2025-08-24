#include "my_strcat.h"


// Concatena "s" en "t" + '\0' al final.
void my_strcat(char *t, const char *s){
	int i = 0;
	int tamT = (int)strlen(t);	
	// Se pone esto porque siempre cambia el tamaño de "t", sobre todo porque se sobreescribe el '\0'.
	
	// Va escaneando por el string "s".
	for(i = 0; i <= strlen(s); i++){
		t[i + tamT] = s[i];	// Copia después del final de "t" (justo empezando por '\0').
		
		// Si se pasó del tamaño de "t", salir:
		// if(sizeof(i + tamT) > sizeof(t)){
			// break;
		// }
	}
	// Pone el '\0' al final:
	t[i + tamT] = '\0';
	
}
