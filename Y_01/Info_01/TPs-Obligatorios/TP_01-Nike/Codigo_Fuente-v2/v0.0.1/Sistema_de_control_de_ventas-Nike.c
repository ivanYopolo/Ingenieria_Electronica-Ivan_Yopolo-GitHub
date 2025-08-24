#include <stdio.h>
#include <stdlib.h>

void main(){
	// # Declaración de variables principales #
	// Variables para verificar que el programa corra y para mostrar o no el menú.
	int running = 1;
	int mostrarMenu = 0;
	
	// Input de opciones en NuevaVenta y en MenuDatos.
	int opcionVent = 1;
	int opcionMenu = 0;
	
	// Input de selección de vendedor y categoría.
	int selecVend = 1;
	int selecCat = 1;
	
	// Input de precio y cantidad de ventas realizadas (en la categoría indicada).
	int precioTemp = 0;
	int ventasTemp = 0;
	
	// Comisiones acumuladas por vendedor.
	float comVend1 = 0;
	float comVend2 = 0;
	float comVend3 = 0;
	
	// Ventas acumuladas por categoría.
	int ventCat1 = 0;
	int ventCat2 = 0;
	int ventCat3 = 0;
	int ventCat4 = 0;
	
	// Facturación total.
	int factTotal = 0;
	
	// # Mensaje inicial #
	system("clear");
	printf("\n#############################################################\n");
	printf("\n### Bienvenida/o al programa de control de ventas de Nike ###\n");
	printf("\n#############################################################\n");
	printf("\nProgramador:                                     Iván Yopolo.");
	printf("\nComisión:                                              R1021.");
	printf("\nVersión:                                               v0.0.1");
	printf("\n#############################################################\n");
	
	/* 
	#####################################################
	############### INICIO DEL PROGRAMA #################
	#####################################################
	*/
	
	// # do-while(running) mientras el programa corra #
	do{		
		// # Nuevas Ventas #
		do{
			switch(opcionVent){
				// Cambio/Identificación de vendedor.
				case 1:
					printf(
					"\n\n[ Por favor, identifíquese: ]\n"
					"\n1) Belén."
					"\n2) Juan."
					"\n3) Sofía.\n");
					
					scanf("%d", &selecVend);
					
					printf("\n#############################################################\n");
					
					// Datos inválidos:
					if(selecVend < 1 || selecVend > 3){
						selecVend = 1;
						mostrarMenu = 1;
						break;
					}


				// Cambio de categoría.
				case 2:
					printf(
					"\n\n[ Seleccione una categoría: ]\n"
					"\n1) Botines Mujer."
					"\n2) Botines Hombre."
					"\n3) Zapatillas Unisex."
					"\n4) Medias.\n");
					
					scanf("%d", &selecCat);
					
					printf("\n#############################################################\n");

					// Datos inválidos:
					if(selecCat < 1 || selecCat > 4){
						selecCat = 1;
						mostrarMenu = 1;
						break;
					}


				// Ingreso de nueva/s venta/s.
				case 3:
					printf("\n\n[ Ingrese el precio unitario del producto: ]\n\n");
					
					scanf("%d", &precioTemp);
					
					printf("\n#############################################################\n");

					// Datos inválidos:
					if(precioTemp < 0){
						precioTemp = 0;
						mostrarMenu = 1;
						break;
					}

					printf("\n\n[ Indique la cantidad vendida: ]\n\n");
					
					scanf("%d", &ventasTemp);
					
					printf("\n#############################################################\n");
					
					// Datos inválidos:
					if(ventasTemp < 0){
						ventasTemp = 0;
						mostrarMenu = 1;
						break;
					}
					
					// Cargado de datos de ventas/categoría.
					switch(selecCat){
						case 1:
							ventCat1 += ventasTemp;
							break;
						
						case 2:
							ventCat2 += ventasTemp;
							break;
						
						case 3:
							ventCat3 += ventasTemp;
							break;
						
						case 4:
							ventCat4 += ventasTemp;
							break;
					}
					
					// Cálculo de la facturación total (hasta el momento).
					factTotal += ventasTemp*precioTemp;
					
					// Cálculo de comisión por vendedor.
					switch(selecVend){
						case 1:
							comVend1 += (ventasTemp*precioTemp)*0.01;
							break;
						
						case 2:
							comVend2 += (ventasTemp*precioTemp)*0.01;
							break;
						
						case 3:
							comVend3 += (ventasTemp*precioTemp)*0.01;
							break;
					}
					
					// Selección de nuevo dato en específico o salir al menú.
					system("clear");
					
					printf(
					"\n[ Seleccione una opción entre: ]\n"
					"\n1) Cambiar de vendedor."
					"\n2) Cambiar de categoría (mismo vendedor)."
					"\n3) Ingresar nueva/s venta/s (mismo vendedor y categoría).\n"
					"\n0) SALIR AL MENÚ.\n");
					
					scanf("%d", &opcionVent);
					
					system("clear");
					
				default:
					mostrarMenu = 1;
					break;
			}
			
		}while(!mostrarMenu);
		
		
		
		// # Menú + Datos #
		while(mostrarMenu){
			printf("\n#############################################################\n");
			printf("\n################### Menú de ventas de Nike ##################\n");
			printf("\n#############################################################\n");
			
			printf(
			"\n[ Seleccione una opción entre: ]\n"
			"\n1) Ingresar nueva/s venta/s."
			"\n2) Mostrar ventas acumuladas por categoría."
			"\n3) Mostrar comisiones acumuladas por vendedor.\n"
			"\n0) SALIR DEL PROGRAMA Y MOSTRAR RESUMEN.\n");
			
			scanf("%d", &opcionMenu);
			
			switch(opcionMenu){
				// Nueva Venta.
				case 1:
					system("clear");
					
					mostrarMenu = 0;
					
					break;
				
				// Ventas/Categoría.
				case 2:
					system("clear");
					
					printf("\n# Ventas acumuladas por categoría #\n");
					
					printf("\nBotines Mujer:        %d", ventCat1);
					printf("\nBotines Hombre:       %d", ventCat2);
					printf("\nZapatillas Unisex:    %d", ventCat3);
					printf("\nMedias:               %d", ventCat4);
					
					break;
				
				// Comisión/Vendedor.
				case 3:
					system("clear");
					
					printf("\n# Comisiones acumuladas por vendedor #\n");
					
					printf("\nBelén:    $ %.2f", comVend1);
					printf("\nJuan:     $ %.2f", comVend2);
					printf("\nnSofía:   $ %.2f", comVend3);
					
					break;
				
				// Datos inválidos.
				default:
					mostrarMenu = 0;
					running = 0;
					
					break;
			}
		}
	}while(running);
	
	
	// # Datos mostrados al salir del programa #
	system("clear");
	
	printf("\n### RESUMEN DEL DÍA ###\n");
	
	// Comisión/Vendedor.
	printf("\n# Comisiones acumuladas por vendedor #\n");
					
	printf("\nBelén:    $ %.2f", comVend1);
	printf("\nJuan:     $ %.2f", comVend2);
	printf("\nSofía:    $ %.2f\n", comVend3);
	
	// Facturación Total.
	printf("\n# Facturación total acumulada: $ %d #\n", factTotal);
	
	return;
}