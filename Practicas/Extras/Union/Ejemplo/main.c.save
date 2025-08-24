#include <stdio.h>


union equivalencia {
    int i;      // 4 B.
    char b[4];  // 4 B.
};  // Total: 4 B.


int main(){
	union equivalencia x;
	
	x.i = 1024;
	printf("Valor de i:    %x\n", x.i);
	printf("Valor de b[o]: %x\n", x.b[0]); // %x: hexadecimal.
	printf("Valor de b[1]: %x\n", x.b[1]);
	printf("Valor de b[2]: %x\n", x.b[2]);
	printf("Valor de b[3]: %x\n", x.b[3]);

	return 1;
}
