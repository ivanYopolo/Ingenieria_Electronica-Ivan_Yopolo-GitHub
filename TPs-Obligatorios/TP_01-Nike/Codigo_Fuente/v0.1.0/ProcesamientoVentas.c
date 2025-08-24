#include <stdio.h>
#include <stdlib.h>
// #include "MostrarDatos.h"
// #include "ProcesamientoVentas.h"

// ### Funciones de procesamiento ###

// Identifica el vendedor utilizando el programa.
int IdentificacionVendedor(){
	int vendedor = 0;
	
	// Seleccion de vendedor.
	printf(
	"\n##############################################\n"
	"\n[ Por favor, identifíquese: ]\n"
	"\n 1) Juan."
	"\n 2) Belén."
	"\n 3) Sofía.\n");
	scanf("\n%d", &vendedor);
	
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
	"\n##############################################\n"
	"\n[ Por favor, seleccione el tipo de producto: ]\n"
	"\n 1) Botines Mujer."
	"\n 2) Botines Hombre."
	"\n 3) Zapatillas Unisex."
	"\n 4) Medias.\n");
	scanf("\n%d", &categoria);
	
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


// Precio por categoria.
int PrecioTransaccion(){
	int precioTemp = 0;
	
	printf(
	"\n##############################################\n"
	"\n[ Por favor, indique el precio de la transaccion: ]\n");
	scanf("\n%d", &precioTemp);
	
	// Seleccion invalida.
	if(precioTemp <= 0){
		return 0;
	}
	
	return precioTemp;
}


// Ingresa el numero de ventas + calculo de facturacion y comision.
int NumeroVentas(int precio, float *comVend, int *fact){
	int ventas = 0;
	
	// Seleccion de cantidad de ventas.
	printf(
	"\n##############################################\n"
	"\n[ Por favor, indique sus ventas en la categoría seleccionada: ]\n");
	scanf("\n%d", &ventas);
	
	system("clear");
	
	// Seleccion invalida.
	if(ventas < 0){
		return 0;
	}
	
	// Datos validos:
	// Calculo Comision.
	*fact = (precio*ventas);			// Facturacion/categoria/vendedor.
	*comVend = 0.01*((float)(*fact));	// Comision/vendedor
	
	// *fact = precio*ventas;				// Facturacion/categoria/vendedor.
	// *comVend = 0.01*((float)(*fact));	// Comision/vendedor
	printf("\n\n"
	"\nFacturacion total: %.2f\n", (float)(*fact));
	
	printf(
	"\nComision Vendedor: %.2f\n", (float)(*comVend));
	return ventas;
}


// Registro de ventas nuevas tanto en el momento inicial como en la seleccion de venta nueva en el menu.
int NuevaVenta(int *selecOpcion, int *selecVendedor, float *comVendedor, int *fact, int *ventCat1, int *ventCat2, int *ventCat3, int *ventCat4){
	int selecCat = 0, selecVentas = 0, selecPrecio = 0;		// Inputs del usuario + "*selecVendedor".
	
	
	
	// Opciones/procesos de ventas:
	switch(*selecOpcion){
		case 0:
			*selecOpcion = 1;			// Proxima vez empieza de "case 1".
			// printf("\n# 9 #\n");
		
		// Cambio de vendedor.
		case 1:
			*selecVendedor = IdentificacionVendedor();
		
		// Cambiar categoria + precio + registro de ventas.
		case 2:
			selecCat = SeleccionCategoria();
			selecPrecio = PrecioTransaccion();
			
			// Si datoInvalido => Menu.
			if((!(*selecVendedor)) || (!selecCat) || (!selecPrecio)){
				*selecOpcion = 1;		// Proxima vez empieza de "case 1".
				*selecVendedor = 0;
				// printf("\n# 7 #\n");
				return 0;
			}
			
			// Registro de ventas + comisiones + facturacion total.
			selecVentas = NumeroVentas(selecPrecio, comVendedor, fact);
			
			// Si datoInvalido => Menu.
			if(selecVentas < 0){
				selecVentas = 0;
				return 0;
			}
			
			break;
			
		// Ir al menu.
		default:
			*selecOpcion = 1;			// Proxima vez empieza de "case 1".
			// printf("\n# 8 #\n");
			return 0;
	}
	
	
	// Si datoValido => grabado de datos.
	// Grabado de ventas por categoria en vendedor X.
	switch(selecCat){
		case 1:
			*ventCat1 += selecVentas;
			break;
			
		case 2:
			*ventCat2 += selecVentas;
			break;
			
		case 3:
			*ventCat3 += selecVentas;
			break;
			
		case 4:
			*ventCat4 += selecVentas;
			break;
	}
	
	
	printf(
	"\n[ Seleccione una opción: ]\n"
	"\n1) Cambiar de empleado (nueva transacción)."
	"\n2) Cambiar de categoría (nueva transacción).\n"
	"\n0) Finalizar e ir al menú.\n");
	scanf("%d", selecOpcion);

	system("clear");
	
	return *selecOpcion;
}
