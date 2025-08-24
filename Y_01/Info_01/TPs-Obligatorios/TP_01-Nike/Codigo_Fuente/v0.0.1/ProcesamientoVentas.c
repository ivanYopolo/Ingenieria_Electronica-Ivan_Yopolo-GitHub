#include <stdio.h>
// #include "MostrarDatos.h"
// #include "ProcesamientoVentas.h"

// ### Funciones de procesamiento ###

// Identifica el vendedor utilizando el programa.
int IdentificacionVendedor(){
	int vendedor = 0;
	
	// Seleccion de vendedor.
	printf(
	"\n[ Por favor, identifíquese: ]\n"
	"\n 1) Juan."
	"\n 2) Belén."
	"\n 3) Sofía.");
	scanf("%d", &vendedor);
	
	// Seleccion invalida.
	if((vendedor <= 0) || (vendedor > 3)){
		return 0;
	}
	
	return vendedor;
}


// Selecciona la categoria de producto.
int SeleccionCategoria(){
	int categoria = 0;
	
	// Seleccion de categoria del producto.
	printf(
	"\n[ Por favor, seleccione el tipo de producto: ]\n"
	"\n 1) Botines Mujer."
	"\n 2) Botines Hombre."
	"\n 3) Zapatillas Unisex."
	"\n 4) Medias.");
	scanf("%d", &categoria);
	/*
	1) BM
	2) BH
	3) ZU
	4) M
	*/
	
	// Seleccion invalida.
	if((categoria <= 0) || (categoria > 4)){
		return 0;
	}
	
	return categoria;
}


// Ingresa el numero de ventas.
int NumeroVentas(){
	int ventas = 0;
	
	// Seleccion de cantidad de ventas.
	printf(
	"\n[ Por favor, indique sus ventas en la categoría seleccionada: ]\n");
	scanf("%d", &ventas);
	
	// Seleccion invalida.
	if(ventas < 0){
		return 0;
	}
	
	return ventas;
}


// Registro de ventas nuevas tanto en el momento inicial como en la seleccion de venta nueva en el menu.
int NuevaVenta(int *selecVendedor, int *ventCat1, int *ventCat2, int *ventCat3, int *ventCat4){
	//int tempVendedor = 0;	// Variable temporal para no guardar datos invalidos en "*selecVendedor".
	int selecCat = 0, selecVentas = 0;		// Inputs del usuario + "*selecVendedor".
	int menuMode = 0;		// Mostrar menu? 1: si; 0: no.
	int selecOpcion = 1;	// Para seleccionar cambio o no de opcion. Empieza en 1 para empezar el ingreso de datos desde vendedor.
	int active = 1;			// Control de programa andando o no.
	
	switch(selecOpcion){			
		// Cambio de vendedor.
		case 1:
			*selecVendedor = IdentificacionVendedor();
		
		// Cambiar categoria + registro de ventas.
		case 2:
			selecCat = SeleccionCategoria();
			selecVentas = NumeroVentas();
			break;
			
		// Ir al menu.
		default:
			menuMode = 1;
			break;
	}
	
	// Si datoInvalido => Menu.
	if((!(*selecVendedor)) || (!selecCat)){
		menuMode = 1;
		return menuMode;
	}
	
	// Si datoValido => grabado de datos.
	// Grabado de ventas por categoria en vendedor X.
	switch(selecCat){
		case 1:
			*ventCat1 = selecVentas;
			break;
			
		case 2:
			*ventCat2 = selecVentas;
			break;
			
		case 3:
			*ventCat3 = selecVentas;
			break;
			
		case 4:
			*ventCat4 = selecVentas;
			break;
	}
	
	// Conjunto de ifs/switches que vayan sumando datos en base a categoria y vendedor.
	
	if(!menuMode){
		// Seleccion:
		printf(
		"\n[ Seleccione una opción: ]\n"
		"\n1) Cambiar de empleado."
		"\n2) Cambiar de categoría."
		"\n0) Finalizar e ir al menú.");
		scanf("%d", &selecOpcion);
	}
		
	return menuMode;
}
