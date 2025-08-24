#include <stdio.h>

/*
// Datos del triángulo:
float ladoA = 0;
float ladoB = 0;
float ladoC = 0;
unsigned int perimetro = 0;
int b = 0; // Base.
int h = 0; // Altura.
// Dato de selección de modo:
unsigned char mode;
*/

// funcion perimetro
void funPerimetro(int ladoA, int ladoB, int ladoC){
	// Ingreso de datos:
	printf("\nIngrese longitud de los 3 lados en secuencia: \n");

	// LADO_A:
	printf("\nLado A: ");
	scanf("%d", &ladoA);

	// Checkeo de datos correctos:
	if(ladoA <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}
	
	// LADO_B:
	printf("\nLado B: ");
	scanf("%d", &ladoB);

	// Checkeo de datos correctos:
	if(ladoB <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}
	
	// LADO_C:
	printf("\nLado C: ");
	scanf("%d", &ladoC);

	// Checkeo de datos correctos:
	if(ladoC <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa. ###\n");
		return;
	}
	

	// Cálculo perímetro:
	int perimetro = ladoA + ladoB + ladoC;
	printf("\nEl perímetro es de: %d\n", perimetro);
	return;
}

// funcion identificador triangulo
void funIdenTriang(int ladoA, int ladoB, int ladoC){
	// Ingresado de lados:
	printf("\nIntroduzca los 3 lados en secuencia: \n");

	// Lado A:
	printf("\nLado A: ");
	scanf("%d", &ladoA);

	if(ladoA <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}

	// Lado B:
	printf("\nLado B: ");
	scanf("%d", &ladoB);

	if(ladoB <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}
	
	// Lado C:
	printf("\nLado C: ");
	scanf("%d", &ladoC);

	if(ladoC <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}

	
	// Identificación del triángulo:

	// Escaleno:
	if((ladoA != ladoB) && (ladoB != ladoC)){
		printf("\nTriángulo Escaleno.\n");
	}

	// Isóceles:
	if(((ladoA == ladoB) && (ladoA != ladoC)) || ((ladoC == ladoB) && (ladoA != ladoB)) || ((ladoA == ladoC) && (ladoA != ladoB))){
		printf("\nTriángulo Isóceles.\n");
	}

	// Equilátero:
	if((ladoA == ladoB) && (ladoB == ladoC)){
		printf("\nTriángulo Equilátero\n");
	}

	// Rectángulo:
	int a2 = ladoA * ladoA;	
	int b2 = ladoB * ladoB;
	int c2 = ladoC * ladoC;
	if((a2 == (b2 + c2)) || (b2 == (a2 + c2)) || (c2 == (b2 + a2))){
		printf("\nTriángulo Rectángulo. \n");
	}
	return;
}

// funcion area
void funArea(int b, int h){
	// Ingreso de datos:
	printf("\nIngrese base y altura: \n");
	printf("\nBase: ");
	scanf("%d", &b);
	if(b <= 0){
		printf("\n### MATH_ERROR: Base no puede ser negativa o 0. ###\n");
		return;
	}

	printf("\nAltura: ");
	scanf("%d", &h);
	if(h <= 0){
		printf("\n### MATH_ERROR: Altura no puede ser negativa o 0. ###\n");
		return;
	}

	// Cálculo del área:
	float a = 0.5*(float)(b*h);
	printf("\nEl área es de: %f\n", a);
	return;
}

// funcion ver triangulo
void funVerTriang(int ladoA, int ladoB, int ladoC){
	// Ingreso de datos:

	// A:
	printf("\nIngresar lado A: ");
	scanf("%d", &ladoA);

	if(ladoA <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}

	// B:
	printf("\nIngresar lado B: ");
	scanf("%d", &ladoB);

	if(ladoB <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}

	// C:
	printf("\nIngresar lado C: ");
	scanf("%d", &ladoC);

	if(ladoC <= 0){
		printf("\n### MATH_ERROR: Longitud no puede ser negativa o 0. ###\n");
		return;
	}

	// Verificación del triángulo:
	int ver1 = ladoA+ladoB;
	int ver2 = ladoA+ladoC;
	int ver3 = ladoC+ladoB;
	
	if((ver1 > ladoC) || (ver2 > ladoB) || (ver3 > ladoA)){
		printf("\nEs un triángulo.\n");
		return;
	}
	
	printf("\nNo es un triángulo.\n");
	return;
}

int main(){
    printf("\n### TRIANGLE_PROGRAM ###\n");
	
	// Datos del triángulo:
	int ladoA = 0;
	int ladoB = 0;
	int ladoC = 0;
	unsigned int perimetro = 0;
	int b = 0; // Base.
	int h = 0; // Altura.
	// Dato de selección de modo:
	unsigned char mode;

    // Selección de modo:
    printf("\nBienvenida/o al programa de matemática de triángulos. \n"
    "Por favor, seleccione el tipo de modo a utilizar: \n"
    "\n1) Cálculo de perímetro. \n"
    "\n2) Identificador de triángulo. \n"
    "\n3) Cálculo de área. \n"
    "\n4) Verificación de triángulo. \n");
    scanf("%c", &mode);

    // Cálculo de perímetro:
    if(mode == '1'){
		funPerimetro(ladoA, ladoB, ladoC);
    }
    
    // Identificador de triángulo:
    if(mode == '2'){
        funIdenTriang(ladoA, ladoB, ladoC);
    }

    // Cálculo de área:
    if(mode == '3'){
        funArea(b, h);
    }

    // Verificación de triángulo:
    if(mode == '4'){
        funVerTriang(ladoA, ladoB, ladoC);
    }

    return 1;
}