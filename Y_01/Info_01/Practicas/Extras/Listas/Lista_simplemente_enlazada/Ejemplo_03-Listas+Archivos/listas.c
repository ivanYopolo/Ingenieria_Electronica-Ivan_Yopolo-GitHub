/*
 * Consigna (con listas - LIFO):
 *
 * 1) Ingresar una cantidad indeterminada de alumnos.
 * 2) Guardar toda la lista en un archivo.
 * 3) Imprimir los datos de todos los alumnos ingresados.
 * 4) Liberar los recursos correctamente.
 */

#include "includes.h"


// -----------------------------------------------------------------------------------
//      getInputData
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
        printf( "2) Ingrese el/los nombre/s:\t\t" );
        alumX->nombres = getString();
        if( alumX->nombres == NULL ){
            
            legajoTemp = -1;
        }
        // printf( "[ Nombre/s recibido/s correctamente ]\n" );
        
        // Apellido/s.
        printf( "3) Ingrese el/los apellido/s:\t\t" );
        alumX->apellidos = getString();
        if( alumX->apellidos == NULL ){
            
            legajoTemp = -1;
        }
        // printf( "[ Apellido/s recibido/s correctamente ]\n" );
        
        do{ // Nota.
            printf( "4) Ingrese la nota de el/la alumno/a:\t\t" );
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
//      getString
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
//      copiarStruct (desuso)
//--------------------------------------------------------------------------
// Copia datos de un struct a otro.
void copiarStruct( Alumno_s *destino, const Alumno_s origen ){
   // printf( "[ Copiando structs... ]\n" );

   /* ### Datos del struct inicial ###
   printf( "\n[ Datos de origen ]\n" );

   printf( "Legajo origen:  \t\t%.3f\n", origen.legajo );
   printf( "Nota origen:    \t\t%d\n", origen.nota );
   printf( "Nombre origen:  \t\t%s\n", origen.nombre );
   printf( "Apellido origen:\t\t%s\n", origen.apellido );
   */

   destino->legajo = origen.legajo;
   destino->nota   = origen.nota;
   strncpy( destino->nombres,    origen.nombres,     strlen( origen.nombres ) ); 
   strncpy( destino->apellidos,  origen.apellidos,   strlen( origen.apellidos ) );

   /* ### Datos copiados en el struct dinámico ###
   printf( "\n[ Datos de destino ]\n" );

   printf( "Legajo:         \t\t%.3f\n", destino->legajo );
   printf( "Nota:           \t\t%d\n", destino->nota );
   printf( "Nombre:         \t\t%s\n",  destino->nombre );
   printf( "Apellido:       \t\t%s\n", destino->apellido );
   */
   // printf( "[ Copiado exitosamente ]\n" );
}


// -----------------------------------------------------------------------------------
//      createNode
// -----------------------------------------------------------------------------------
// Con los datos de los alumnos, crea un nuevo nodo y lo devuelve dinámicamente.
// # Recordar de liberar memoria después #
Nodo_s * createNode( Alumno_s *dataX ){

   Nodo_s *newNode = (Nodo_s *) calloc( 1, sizeof(Nodo_s) );
   newNode->next = NULL;   // El siguiente es el NULO.

   // Copia structs.
   // copiarStruct( &(newNode->data), *dataX );
   newNode->data = *dataX;

   return newNode; // Retorna la dirección del nuevo nodo creado.
}


// -----------------------------------------------------------------------------------
//      pushNode
// -----------------------------------------------------------------------------------
// Agrega un nuevo nodo a la lista (FIFO).
void pushNode( Nodo_s **startNode, Nodo_s *newNode ){

   newNode->next = *startNode;
   *startNode = newNode;
}


// -----------------------------------------------------------------------------------
//      popNode
// -----------------------------------------------------------------------------------
// Saca un nodo de la lista (FIFO).
void popNode( Nodo_s **startNode ){
   // Se toma doble pointer porque se necesita cambiar los datos
   // del puntero en sí, que apunte a otro lado este mismo.

   Nodo_s *nodeAux = *startNode;   // Auxiliar para apuntar al nodo "n".

   *startNode = nodeAux->next;    // Apunta al nodo "n+1". 

   // Libera memoria de nombres y apellidos (strings dinámicos).
   free( nodeAux->data.nombres );
   free( nodeAux->data.apellidos );

   free( nodeAux );    // Libera el nodo "n".
}


// -----------------------------------------------------------------------------------
//      printData
// -----------------------------------------------------------------------------------
// Imprime datos de cada alumno en pantalla.
// Datos del alumno X.
void printData( Alumno_s alumX ){
    printf( "\n### Datos de las/os alumnas/os ###" );
    
    printf( "\nAlumno/a:\t\t%s %s", alumX.nombres, alumX.apellidos );
    printf( "\nLegajo:  \t\t%03.3f", alumX.legajo );
    printf( "\nNota:    \t\t%d", alumX.nota );
    
    printf( "\n" );
}


// -----------------------------------------------------------------------------------
//      writeListInFile 
// -----------------------------------------------------------------------------------
// Guarda la lista entera en un archivo como STRING (.txt).
// Carga solamente "data"; se pierden los punteros.
/* # Pseudocódigo #
 * 
 * Obtener la dirección del primer nodo.
 * Acceder al campo "data".
 * Convertir los datos a strings.
 * Copiar todos los datos, separados por líneas.
 * Cuando se termine un nodo, se dejan 2 líneas.
 */
void writeListInFile( Nodo_s *startNode ){
    Nodo_s *pointerNodeX = startNode;   // Obtiene el primer nodo.
    char tempDataStr[ TAM_STR ];
    char tempDataStr2[ TAM_STR ];
    char newLine = '\n';
    
    int fd = creat( "datosLista.txt", 0666 );   // Archivo a guardar datos de la lista entera.
    
    while( pointerNodeX != NULL ){   // Recorre la lista entera.
        printf( "Legajo...\n" );
        sprintf( tempDataStr, "%03.3f", pointerNodeX->data.legajo );
        write( fd, tempDataStr, sizeof(char) * strlen( tempDataStr ) );
        write( fd, &newLine, sizeof(char) );
        
        printf( "Nota...\n" );
        sprintf( tempDataStr2, "%d", pointerNodeX->data.nota );
        write( fd, tempDataStr2, sizeof(char) * strlen( tempDataStr2 ) );
        write( fd, &newLine, sizeof(char) );
        
        printf( "Nombres...\n" );
        write( fd, pointerNodeX->data.nombres, strlen( pointerNodeX->data.nombres ) );
        write( fd, &newLine, sizeof(char) );
        
        printf( "Apellidos...\n" );
        write( fd, pointerNodeX->data.apellidos, strlen( pointerNodeX->data.apellidos ) );
        write( fd, &newLine, sizeof(char) );
        
        // Termina de cargar los datos del nodo X.
        write( fd, &newLine, sizeof(char) );
        
        pointerNodeX = pointerNodeX->next;  // Apunta al siguiente.
    }
    
    close( fd );    // Cierra archivo.
}
 
 