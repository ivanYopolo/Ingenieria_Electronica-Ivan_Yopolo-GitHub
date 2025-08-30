/* # Ejemplo 03 #
 * Consigna (con listas + archivos - LIFO):
 *
 * 1) Ingresar una cantidad indeterminada de alumnos.
 * 2) Guardar toda la lista en un archivo.
 * 3) Imprimir los datos de todos los alumnos ingresados.
 * 4) Liberar los recursos correctamente.
 */
 
// Ejecución:   gcc -Wall --pedantic-errors main.c listas.c
 
#include "includes.h"

// -----------------------------------------------------------------------------------
//     main
// -----------------------------------------------------------------------------------
int main(){
    int running = 1;
    Nodo_s *nodo1;   // Comienzo de la lista.
    Alumno_s alumnoX;    // Datos auxiliares a recibir por cada iteración.
    
    
    printf( "# Ingrese los datos de las/os alumnas/os a registrar #\n\n" );
    
    // ### Input de datos ###
    
    // # 1° iteración #
    running = getInputData( &alumnoX );
    
    if( running > 0 ){
        // Pasó e ingresó mínimo 1 dato.
        nodo1 = createNode( &alumnoX ); // Asigna el comienzo de la lista.
        
        // # Resto #
        while( running > 0 ){ 
            
            Nodo_s *nodoAux = nodo1;    // Nodo auxiliar para recibir datos en cada iteración.
        
            running = getInputData( &alumnoX );
            
            if( running > 0 ){
                
                nodoAux = createNode( &alumnoX );   // Crea un nodo en la lista y lo apunta correctamente.
                pushNode( &nodo1, nodoAux );    // Mete dicho nodo dentro de la lista.
                
                // printf( "\n[ Nodo creado:   \t%p ]", (void *) nodoAux );
                // printf( "\n[ Nodo siguiente:\t%p ]", (void *) nodoAux->next );
            }
        }
    }

    // Guarda datos en un archivo:
    writeListInFile( nodo1 );
    
    // Libera recursos.
    while( nodo1 != NULL ){
        // Imprime datos en pantalla.
        printData( nodo1->data );

        // Saca el nodo de la lista, libera los recursos.
        popNode( &nodo1 );
    }
    
    return 0;
}


 