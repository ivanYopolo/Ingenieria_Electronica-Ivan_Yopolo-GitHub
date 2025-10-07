#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <ctype.h>

// clear; gcc -Wall --pedantic-errors main.c -o prog.bin

typedef struct Dato_s {
   int   dni;
   float dinero;
   char  nombre[20];
} Dato_t;

int main() {
   Dato_t   ciudadanoIn;   // A cargar del archivo.
   Dato_t   ciudadanoOut = {
               47126740, 31415.9, "Iván" 
            }; // A guardar en archivo.
   int      fdData;
   
   fdData = open( "datos.dat", O_WRONLY | O_CREAT | O_TRUNC, 0666 );
   
   printf( "\n\n### Dato a guardar ###\n" );
   printf( "* DNI:   \t%d\n", ciudadanoOut.dni );
   printf( "* Dinero:\t%f\n", ciudadanoOut.dinero );
   printf( "* Nombre:\t%s\n\n", ciudadanoOut.nombre );
   
   write( fdData, &ciudadanoOut, sizeof(ciudadanoOut) );
   printf( "[ DATOS GUARDADOS EN ARCHIVO. ]\n\n" );
   close( fdData );
   
   printf( "\n[ Leyendo... ]\n" );
   fdData = open( "datos.dat", O_RDONLY );
   read( fdData, &ciudadanoIn, sizeof(ciudadanoIn) );
   
   printf( "\n\n### Dato leído ###\n" );
   printf( "* DNI:   \t%d\n", ciudadanoIn.dni );
   printf( "* Dinero:\t%f\n", ciudadanoIn.dinero );
   printf( "* Nombre:\t%s\n\n", ciudadanoIn.nombre );
   
   close( fdData );
}
