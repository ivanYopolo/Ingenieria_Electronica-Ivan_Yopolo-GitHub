#ifndef includes
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    
    #define TAM_STR 1024
    
    char * writeStrD();
    
    // Devuelve NULL.
    char * contarPalabras( int fdi, int *cantidadPalabras );
    
    // Recordar hacer FREE del pointer.
    char * contarPalabraClave( int fdi, int *cantidadPalabras );
    
    // Si es nulo palabraClave, hace otra cosa.
    void mostrarResultados( int cantidadPalabras, char *palabraClave );
#endif