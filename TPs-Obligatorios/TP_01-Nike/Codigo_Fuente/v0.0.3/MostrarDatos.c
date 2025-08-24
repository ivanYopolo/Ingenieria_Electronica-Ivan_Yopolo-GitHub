#include <stdio.h>
#include <stdlib.h>
// #include "MostrarDatos.h"

// ### Funciones para mostrar datos ###

// Ventas Totales + Ventas/Categoria:
void ShowVentasCategoria(unsigned int ventTot, unsigned int ventBM, unsigned int ventBH, unsigned int ventZU, unsigned int ventM){
	printf(
	"\n### Ventas por categoria ###\n");
	
	printf(
	"\nBotines de Mujer:  %d", ventBM);
	
	printf(
	"\nBotines de Hombre: %d", ventBH);
	
	printf(
	"\nZapatillas Unisex: %d", ventZU);
	
	printf(
	"\nMedias:            %d\n", ventM);
	
	printf(
	"\nVentas Totales:    %d\n", ventTot);
	
	return;
}


// Facturacion de cada vendedor o comision:
void ShowComisionVendedor(float *comJ, float *comB, float *comS){
	printf(
	"\n### Comisión por vendedor ###\n");
	
	printf(	// Juan.
	"\nJuan:  %.2f", *comJ);

	printf(	// Belen.
	"\nBelen: %.2f", *comB);

	printf(	// Sofia.
	"\nSofia: %.2f\n", *comS);
}


// Facturacion Total del Local:
void ShowFacturacion(){
	// A
}


// Datos a mostrar al salir:
int ExitDatos(){
	// A
}