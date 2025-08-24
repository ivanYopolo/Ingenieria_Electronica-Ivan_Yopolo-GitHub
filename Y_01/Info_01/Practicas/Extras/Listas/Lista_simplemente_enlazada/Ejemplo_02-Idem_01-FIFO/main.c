/*
 * Consigna (con listas - FIFO):
 *
 * 1) Ingresar una cantidad indeterminada de alumnos.
 * 2) Imprimir los datos de todos los alumnos ingresados.
 * 3) Liberar los recursos correctamente.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100

typedef struct Alumno{  // Data a guardar.
    float   legajo;
    int     nota;
    char    *nombres;      // Dinámico.
    char    *apellidos;    // Dinámico.
} Alumno_s;


typedef struct Nodo{    // Nodo de la lista.
    struct Alumno   data;  // Struct Alumno dentro.
    struct Nodo     *next; // Puntero al siguiente nodo.
} Nodo_s;

// ###################################################################################

int getInputData( Alumno_s *alumX );

char * getString();

void copiarStruct( Alumno_s *destino, Alumno_s origen );

Nodo_s * createNode( Alumno_s *dataX );

void pushNode( Nodo_s **startNode, Nodo_s *newNode );

// Nodo_s * popNode( Nodo_s *nodePop, Nodo_s *startNode );
Nodo_s * popNode( Nodo_s *startNode );

Nodo_s * getLastNode( Nodo_s *nodo1 );

void printData( const Alumno_s alumX );

// -----------------------------------------------------------------------------------
//     main
// -----------------------------------------------------------------------------------
int main(){
    int running = 1;
    Nodo_s *nodo1;      // Comienzo de la lista.
    Alumno_s alumnoX;   // Datos auxiliares a recibir por cada iteración.
    Nodo_s *nodoAux = NULL;   // Nodo auxiliar para recibir datos en cada iteración.
    
    
    printf( "# Ingrese los datos de los alumnos a registrar (legajo 0 o negativo para finalizar) #\n\n" );
    
    // ### Input de datos ###
    
    // # 1° iteración #
    running = getInputData( &alumnoX );
    
    if( running > 0 ){
        
        nodo1 = createNode( &alumnoX );
        
        // # Resto #  
        while( running > 0 ){
        
            running = getInputData( &alumnoX );
            if( running > 0 ){
                
                // Crea un nodo en la lista y lo apunta correctamente.
                nodoAux = createNode( &alumnoX );
                
                // Mete dicho nodo dentro de la lista.
                pushNode( &nodo1, nodoAux );
            }
        } // nodoAux agarra el PRIMER nodo.
    }
    
    // Para hacer tipo FIFO, vamos al último nodo.
    nodoAux = getLastNode( nodo1 );
    
    printf( "\n### Datos de los alumnos ###" );
    
    while( nodoAux != NULL ){
        
        // Imprime datos en pantalla.
        printData( nodoAux->data );
        
        // Saca el nodo de la lista, libera los recursos.
        nodoAux = (Nodo_s *) popNode( nodo1 );
    }
    
    return 0;
}


// -----------------------------------------------------------------------------------
//     getInputData
// -----------------------------------------------------------------------------------
// Guarda datos de input en un struct de datos (Alumno).
int getInputData( Alumno_s *alumX ){
    float legajoTemp = 0;
    int notaTemp = 0;
    char c;
    
    do{ // Legajo.
        printf( "\n1) Ingrese el legajo (legajo 0 o negativo para finalizar):\t\t" );
        scanf( "%f", &legajoTemp );
        while( (c = getchar()) != '\n' && c != EOF );
        // printf( "[ Legajo recibido correctamente ]\n" );
        
        if( legajoTemp >= 1000 ){
            printf( "\n[ ERROR: DATO INVÁLIDO. VUELVA A INGRESARLO. ]\n" );
        }
    }while( legajoTemp >= 1000 );

    if( legajoTemp > 0 ){
        alumX->legajo = legajoTemp;
        
        // Nombre/s.
        printf( "2) Ingrese el/los nombre/s:                                 \t\t" );
        alumX->nombres = getString();
        if( alumX->nombres == NULL ){
            
            legajoTemp = -1;
        }
        // printf( "[ Nombre/s recibido/s correctamente ]\n" );
        
        // Apellido/s.
        printf( "3) Ingrese el/los apellido/s:                               \t\t" );
        alumX->apellidos = getString();
        if( alumX->apellidos == NULL ){
            
            legajoTemp = -1;
        }
        // printf( "[ Apellido/s recibido/s correctamente ]\n" );
        
        do{ // Nota.
            printf( "4) Ingrese la nota de el/la alumno/a:                       \t\t" );
            scanf( "%d", &notaTemp );
            while( (c = getchar()) != '\n' && c != EOF );
            
            if( notaTemp < 1 || notaTemp > 10 ){
                printf( "\n[ ERROR: DATO INVÁLIDO. VUELVA A INGRESARLO. ]\n" );
            }
        }while( notaTemp < 1 || notaTemp > 10 );
        
        alumX->nota = notaTemp;
        // printf( "[ Nota recibida correctamente ]\n" );
    }else{
        legajoTemp = -1;
    }
    
    printf( "\n" );
    
    return (int)legajoTemp;
}


// -----------------------------------------------------------------------------------
//     getString
// -----------------------------------------------------------------------------------
// Devuelve un string dinámico.
char * getString(){
    char strI[ TAM ];
    
    // No poner strlen() porque toma el salto de línea.
	while( fgets( strI, TAM, stdin ) == NULL ){
        printf( "[ ERROR: POR FAVOR, ESCRIBA DE VUELTA. ]\n" );
    }	// ERROR
	
	// Flushea el buffer:
	if( strI[ strlen( strI ) - 1 ] != '\n' ){
        
		char ch = 0;
		while( ( ch = getchar() ) != '\n' && ch != EOF );
	}
    
	// Si se detecta un salto de línea:
	if( strI[ strlen( strI ) - 1 ] == '\n' ){
        strI[ strlen( strI ) - 1 ] = '\0';
    }
    
    // Aloja memoria en el HEAP para el string.
    char *strO = (char *) calloc( strlen( strI ), sizeof(char) );
    
    strcpy( strO, strI );
    
    return strO;
}


//--------------------------------------------------------------------------
//    copiarStruct (desuso)
//--------------------------------------------------------------------------
// Copia datos de un struct a otro.
void copiarStruct( Alumno_s *destino, Alumno_s origen ){
    
    destino->legajo = origen.legajo;
    destino->nota   = origen.nota;
    strncpy( destino->nombres,    origen.nombres,     strlen( origen.nombres ) ); 
    strncpy( destino->apellidos,  origen.apellidos,   strlen( origen.apellidos ) );
}


// -----------------------------------------------------------------------------------
//     createNode
// -----------------------------------------------------------------------------------
// Con los datos de los alumnos, crea un nuevo nodo y lo devuelve dinámicamente.
// # Recordar de liberar memoria después #
Nodo_s * createNode( Alumno_s *dataX ){
    
    Nodo_s *newNode = (Nodo_s *)calloc( 1, sizeof(Nodo_s) );
    // Copia structs.
    // copiarStruct( &(newNode->data), *dataX );
    newNode->data = *dataX;
    
    return newNode; // Retorna la dirección del nuevo nodo creado.
}


// -----------------------------------------------------------------------------------
//     pushNode - FIFO
// -----------------------------------------------------------------------------------
// Agrega un nuevo nodo a la lista.
void pushNode( Nodo_s **startNode, Nodo_s *newNode ){
    
    newNode->next = *startNode;
    *startNode = newNode;
}


// -----------------------------------------------------------------------------------
//     popNode - FIFO
// -----------------------------------------------------------------------------------
// Saca un nodo de la lista (el último).
Nodo_s * popNode( Nodo_s *startNode ){
    // Se toma doble pointer porque se necesita cambiar los datos
    // del puntero en sí, que apunte a otro lado este mismo.
    Nodo_s *nodePrev = NULL;
    Nodo_s *nodeNext = NULL;

    if( startNode != NULL && startNode->next != NULL ){
        
        nodePrev = startNode;         // Apunta al nodo "n".
        // printf( "\n[ Nodo primero:            \t%p ]", (void *) nodePrev );
        nodeNext = startNode->next;    // Apunta al nodo "n+1".
        // printf( "\n[ Nodo segundo:            \t%p ]", (void *) nodeNext );
        
        while( nodeNext->next != NULL ){ 
        
            nodePrev = nodeNext;         // Previous: Apunta al nodo "n".
            nodeNext = nodeNext->next;   // Current: Apunta al nodo "n+1". 
            
            // printf( "\n[ Nodo actual:             \t%p ]", (void *) nodePrev );
            // printf( "\n[ Nodo siguiente:          \t%p ]", (void *) nodeNext );
        }  // nodeNext = nodePop.
        
        // Libera memoria de nombres y apellidos (strings dinámicos).
        free( nodeNext->data.nombres );
        free( nodeNext->data.apellidos );
        
        free( nodeNext );    // Libera el nodo "n".
        
        nodePrev->next = NULL;  // El siguiente es el NULL; se convierte en el nuevo final.
    }
    
    return nodePrev;
}


// -----------------------------------------------------------------------------------
//     printData
// -----------------------------------------------------------------------------------
// Imprime datos de cada alumno en pantalla.
// Datos del alumno X.
void printData( Alumno_s alumX ){
    
    printf( "\nAlumno/a:\t\t%s %s", alumX.nombres, alumX.apellidos );
    printf( "\nLegajo:  \t\t%3.3f", alumX.legajo );
    printf( "\nNota:    \t\t%d", alumX.nota );
    
    printf( "\n" );
}



// -----------------------------------------------------------------------------------
//     getLastNode
// -----------------------------------------------------------------------------------
// Devuelve la dirección del último nodo de la lista.
Nodo_s * getLastNode( Nodo_s *nodo1 ){
    Nodo_s *nodeCursor = nodo1;
    
    while( nodeCursor->next != NULL && nodeCursor != NULL ){
        // printf( "\n# nodeCursor       = %p #", (void *) nodeCursor );
        // printf( "\n# nodeCursor->next = %p #\n", (void *) nodeCursor->next );
        nodeCursor = nodeCursor->next;
    }   // Cuando el siguiente es el NULL, encontró el último.
    
    return nodeCursor;
}


 