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
	"\nVersión: v0.0.2"
	"\nDesarrollado por: Iván Yopolo.\n"
	);
	
	// 1° do-while: maquina corriendo.
	do{
		// 2° do-while: maquina registrando ventas.
		do{
			// switch(selecVend) para guardar las ventas reales:
			switch(selecVend){
				case 1:		// Juan.
					// Ventas:
					ventJuan_BM += ventasCategoria1;
					ventJuan_BH += ventasCategoria2;
					ventJuan_ZU += ventasCategoria3;
					ventJuan_M  += ventasCategoria4;
					
					// Comision:
					comisionJuan += tempComisionVendedor;
					
					break;
				
				case 2:		// Belen.
					// Ventas:
					ventBelen_BM += ventasCategoria1;
					ventBelen_BH += ventasCategoria2;
					ventBelen_ZU += ventasCategoria3;
					ventBelen_M  += ventasCategoria4;
					
					// Comision:
					comisionBelen += tempComisionVendedor;
					
					break;
				
				case 3:		// Sofia.
					// Ventas:
					ventSofia_BM += ventasCategoria1;
					ventSofia_BH += ventasCategoria2;
					ventSofia_ZU += ventasCategoria3;
					ventSofia_M  += ventasCategoria4;
					
					// Comision:
					comisionSofia += tempComisionVendedor;
					
					break;
			}
			
			// Ventas totales:
			ventasTotales += ventCat_BM + ventCat_BH + ventCat_ZU + ventCat_M;
			
			// Pasar por referencia variables a "NuevaVenta".
			// PASAR PRECIO Y COMISION.
			menuShow = NuevaVenta(&selecOpcion, &selecVend, &tempComisionVendedor, &facturacionTotal, &ventasCategoria1, &ventasCategoria2, &ventasCategoria3, &ventasCategoria4);
		}while(menuShow > 0);	// Si menuShow <= 0  =>  Ir al menu.
		
		
		// Se pasa al menu para mostrar datos:
		// 2) Poner lo principal de MenuDatos() en main() con la interfaz gráfica en otras funciones/librerías.
		
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
		
		break;
		
		// Seleccion invalida.
		if(seleccionMenu < 0){
			// return ;
		}
		
		
		// running = MenuDatos(selecVend, ventCat1, ventCat2, ventCat3, ventCat4);
		
		
	}while(running);
	
	
	
	// Datos a mostrar al salir del programa:
	
	//Cambiar para pasar variables de VENTAS.
	/*
	ShowVentasTotales();
	ShowGananciasBrutas();
	ShowComisionVendedor();
	*/
	return 0;
}