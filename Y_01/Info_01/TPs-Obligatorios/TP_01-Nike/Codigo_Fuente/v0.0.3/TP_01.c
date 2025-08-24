#include <stdio.h>
#include <stdlib.h>					// Importado para el system("clear").
#include "ProcesamientoVentas.h"
#include "MostrarDatos.h"

/*
##############################
Programa: 
	Control de Ventas Nike.

Hecho por:
	Iván Yopolo.

Comisión:
	R1021.
##############################
*/


// Funcion MAIN:
int main(){
	// # Variables principales #
	unsigned int running = 1;	// Variable para checkear que la maquina corra.
	int menuShow = 0;			// 1: muestra menu; 0: procesa ventas.
	int selecOpcion = 1;		// Seleccion de modo en ingreso de datos nuevos (de fabrica, empieza desde vendedor).
	int seleccionMenu = 0;		// Seleccionar opciones basicas del menu.
	
	// # Variables a modificar en "NuevaVenta()" #
	float tempComisionVendedor = 0;
	int tempFacturacion = 0;
	int facturacionTotal = 0;
	int selecVend = 0;			// Seleccion de vendedor.
	// int precioTransaccion = 0;
	
	int ventasCategoria1 = 0;	// Ventas en "Botines Mujer".
	int ventasCategoria2 = 0;	// Ventas en "Botines Hombre".
	int ventasCategoria3 = 0;	// Ventas en "Zapatillas Unisex".
	int ventasCategoria4 = 0;	// Ventas en "Medias".
	
	
	// # Variables de cada vendedor #
	/*
	Categorias:
	1) BM (Botines Mujer)
	2) BH (Botines Hombre)
	3) ZU (Zapatillas Unisex)
	4) M (Medias)
	*/
	
	// Juan:
	unsigned int ventJuan_BM = 0;
	unsigned int ventJuan_BH = 0;
	unsigned int ventJuan_ZU = 0;
	unsigned int ventJuan_M  = 0;
	unsigned int ventJuan  = 0;		// Ventas totales de Juan.
	float comisionJuan = 0;
	
	// Belen:
	unsigned int ventBelen_BM = 0;
	unsigned int ventBelen_BH = 0;
	unsigned int ventBelen_ZU = 0;
	unsigned int ventBelen_M  = 0;
	unsigned int ventBelen = 0;		// Ventas totales de Belen.
	float comisionBelen = 0;
	
	// Sofia:
	unsigned int ventSofia_BM = 0;
	unsigned int ventSofia_BH = 0;
	unsigned int ventSofia_ZU = 0;
	unsigned int ventSofia_M  = 0;
	unsigned int ventSofia = 0;		// Ventas totales de Sofia.
	float comisionSofia = 0;
	
	// Ventas:
	unsigned int ventasTotales = 0;	// Ventas TOTALES.
	unsigned int ventCat_BM = 0;	// Ventas totales de "Botines Hombre".
	unsigned int ventCat_BH = 0;	// Ventas totales de "Botines Mujer".
	unsigned int ventCat_ZU = 0;	// Ventas totales de "Zapatillas Unisex".
	unsigned int ventCat_M  = 0;	// Ventas totales de "Medias".
		
	
	// ####################################
	// Inicio del codigo:
	
	system("clear");
	printf(
	"\n##############################\n"
	"\n####Control_de_ventas-Nike####\n"
	"\n##############################\n"
	"\n"
	"\nVersión: v0.0.3"
	"\nDesarrollado por: Iván Yopolo.\n"
	);
	
	// 1° do-while: maquina corriendo.
	do{
		// ############# REGISTRO VENTAS ###############
		do{	
			// Pasar por referencia variables a "NuevaVenta".
			menuShow = NuevaVenta(&selecOpcion, &selecVend, &tempComisionVendedor, &tempFacturacion, &ventCat_BM, &ventCat_BH, &ventCat_ZU, &ventCat_M);
			
			// Ventas totales:
			ventasTotales = ventCat_BM + ventCat_BH + ventCat_ZU + ventCat_M;
			// Facturacion total del local:
			facturacionTotal += tempFacturacion;
			
			// switch(selecVend) para guardar las ventas y comisiones:
			switch(selecVend){
				case 1:		// Juan.
					// Ventas:
					ventJuan_BM += ventCat_BM;
					ventJuan_BH += ventCat_BH;
					ventJuan_ZU += ventCat_ZU;
					ventJuan_M  += ventCat_M;
					
					// Comision:
					comisionJuan += tempComisionVendedor;
					
					break;
				
				case 2:		// Belen.
					// Ventas:
					ventBelen_BM += ventCat_BM;
					ventBelen_BH += ventCat_BH;
					ventBelen_ZU += ventCat_ZU;
					ventBelen_M  += ventCat_M;
					
					// Comision:
					comisionBelen += tempComisionVendedor;
					
					break;
				
				case 3:		// Sofia.
					// Ventas:
					ventSofia_BM += ventCat_BM;
					ventSofia_BH += ventCat_BH;
					ventSofia_ZU += ventCat_ZU;
					ventSofia_M  += ventCat_M;
					
					// Comision:
					comisionSofia += tempComisionVendedor;
			}

		}while(menuShow > 0);	// Si menuShow <= 0  =>  Ir al menu.
		
		
		// ############# MENU ###############
		do{
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
			
			scanf("%d", &seleccionMenu);
			
			system("clear");
			
			
			switch(seleccionMenu){
				case 1:		// Nueva venta (sale del menu).
					menuShow = 1;
					break;
					
				case 2:		// VentTot + Vent/Cat.
					ShowVentasCategoria(ventasTotales, ventCat_BM, ventCat_BH, ventCat_ZU, ventCat_M);
					break;
				
				case 3:		// Com/vend.
					ShowComisionVendedor(&comisionJuan, &comisionBelen, &comisionSofia);
					break;
					
				case 0:		// Salir del programa.
					running = 0;
					seleccionMenu = 1;
					menuShow = 1;
			}
			
		}while(menuShow <= 0);
	}while(running);
	
	
	
	// Datos a mostrar al salir del programa:
	
	
	return 0;
}