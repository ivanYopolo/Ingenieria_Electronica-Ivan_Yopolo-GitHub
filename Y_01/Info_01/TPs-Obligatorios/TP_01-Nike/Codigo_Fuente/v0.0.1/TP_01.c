#include <stdio.h>
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
	// Variables principales:
	unsigned int running = 1;	// Variable para checkear que la maquina corra.
	unsigned int menuMode = 0;	// 1: ir al menu; 0: seguir con ventas nuevas.
	
	// Variables a modificar en "NuevaVenta()":
	int selecVend = 0;			// Seleccion de vendedor.
	int ventasCategoria1 = 0;	// Ventas en "Botines Mujer".
	int ventasCategoria2 = 0;	// Ventas en "Botines Hombre".
	int ventasCategoria3 = 0;	// Ventas en "Zapatillas Unisex".
	int ventasCategoria4 = 0;	// Ventas en "Medias".
	
	// Variables de todos los casos vendedor-categoria.
	
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
	
	// Belen:
	unsigned int ventBelen_BM = 0;
	unsigned int ventBelen_BH = 0;
	unsigned int ventBelen_ZU = 0;
	unsigned int ventBelen_M  = 0;
	
	// Sofia:
	unsigned int ventSofia_BM = 0;
	unsigned int ventSofia_BH = 0;
	unsigned int ventSofia_ZU = 0;
	unsigned int ventSofia_M  = 0;
	
	printf(
	"\n##############################\n"
	"\n####Control_de_ventas-Nike####\n"
	"\n##############################\n"
	"\n"
	"\nVersión: v.0.0.1"
	"\nDesarrollado por: Iván Yopolo.\n"
	);
	
	// 1° do-while: maquina corriendo.
	do{
		// 2° do-while: maquina registrando ventas.
		do{
			// switch(selecVend) para guardar las ventas reales:
			switch(selecVend){
				case 1:		// Juan.
					ventJuan_BM += ventasCategoria1;
					ventJuan_BH += ventasCategoria2;
					ventJuan_ZU += ventasCategoria3;
					ventJuan_M  += ventasCategoria4;
					break;
				
				case 2:		// Belen.
					ventBelen_BM += ventasCategoria1;
					ventBelen_BH += ventasCategoria2;
					ventBelen_ZU += ventasCategoria3;
					ventBelen_M  += ventasCategoria4;
					break;
				
				case 3:		// Sofia.
					ventSofia_BM += ventasCategoria1;
					ventSofia_BH += ventasCategoria2;
					ventSofia_ZU += ventasCategoria3;
					ventSofia_M  += ventasCategoria4;
					break;
			}
			
			// Pasar por referencia variables a "NuevaVenta".
			menuMode = NuevaVenta(&selecVend, &ventasCategoria1, &ventasCategoria2, &ventasCategoria3, &ventasCategoria4);
		}while(!menuMode);
		
		// Se pasa al menu para mostrar datos:
		
		
		
		
		
		
		// MenuDatos(selecVend, selecCat, ventCat1, ventCat2, ventCat3, ventCat4);
		
		
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