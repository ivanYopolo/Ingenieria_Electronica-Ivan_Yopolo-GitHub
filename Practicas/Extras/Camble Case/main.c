#include "cambleCase.h"
#define strTam 50

int main(){
	char str[strTam] = "¿hoLA muNDo?";
	printf("\nEl string original:  %s\n", str);
	cambleCase(str);
	printf("\nEl string resultó:   %s\n", str);
	return 1;
}