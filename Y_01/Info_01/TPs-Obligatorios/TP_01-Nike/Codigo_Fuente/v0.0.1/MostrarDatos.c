#include <stdio.h>
// #include "MostrarDatos.h"

// ### Funciones para mostrar datos ###
void ShowVentasCategoria(unsigned int showCategoria, int showVentas){
	// A
}

void ShowVentasTotales(){
	int ventasTot = 0;
	// A
}

void ShowGananciasBrutas(){
	// A
}

void ShowComisionVendedor(){
	// A
}

/*
Menu donde se muestran:
* Opcion para nueva venta.
* Ventas por categoria y totales.
* Comisiones por vendedor.
* Salir del programa.
*/

int MenuDatos(unsigned int vendedor, unsigned int categoria, int ventasCat1, int ventasCat2, int ventasCat3, int ventasCat4){
	// Ventas por cada categoria, en un solo vendedor en particular.
	//int datosVendedor[4] = {ventasCat1, ventasCat2, ventasCat3, ventasCat4};
	unsigned int activo = 1;		// Variable para indicar si sale o no el programa.
	int seleccion = 0;
	
	// Mostrar botones para seleccion:
	printf(
	"\n################################################################\n"
	"\n##### Bienvenida/o al Sistema de Control de Ventas de Nike #####\n"
	"\n###### [ Seleccione alguna de las siguientes opciones: ] #######\n"
	"\n1) Ingresar una nueva venta."
	"\n2) Mostrar las ventas totales y por categoría de producto."
	"\n3) Mostrar las comisiones acumuladas por vendedor.\n"
	"\n0) SALIR DEL PROGRAMA.\n"
	"\n################################################################\n");
	
	scanf("%d", &seleccion);
	
	// Seleccion invalida.
	if(seleccion < 0){
		// return ;
	}
	
	// return activo = 0;			// Retorna 0 si sale el programa (exit).
}