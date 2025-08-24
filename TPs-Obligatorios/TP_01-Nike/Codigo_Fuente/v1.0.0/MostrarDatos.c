#include <stdio.h>
#include <stdlib.h>
// #include "MostrarDatos.h"

// ### Funciones para mostrar datos ###

// Ventas Totales + Ventas/Categoria:
void ShowVentasCategoria(unsigned int ventTot, unsigned int ventBM, unsigned int ventBH, unsigned int ventZU, unsigned int ventM){
	printf(
	"\n# Ventas por categoria #");
	
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
void ShowComisionVendedor(float comJ, float comB, float comS){
	printf(
	"\n# Comisión por vendedor #");
	
	printf(	// Juan.
	"\nJuan:  $%.2f.", comJ);

	printf(	// Belen.
	"\nBelen: $%.2f.", comB);

	printf(	// Sofia.
	"\nSofia: $%.2f.\n", comS);
}


// Facturacion Total del Local:
void ShowFacturacion(int facturacion){
	printf("\n# Facturacion total del día #\n");
	printf("Se registró una ganancia neta de: $%d.\n", facturacion);
}


// Datos a mostrar al salir:
void ExitDatos(int facturacion, float comJ, float comB, float comS){
	printf(
	"\n[ Gracias por utilizar nuestros servicios. ]\n"
	"\n### Resumen del día ###\n");
	
	ShowFacturacion(facturacion);
	
	ShowComisionVendedor(comJ, comB, comS);	
	
	printf("\n##############################################\n");
}