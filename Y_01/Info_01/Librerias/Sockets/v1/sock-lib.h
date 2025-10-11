#ifndef SOCK_LIB
   #define SOCK_LIB
   
   // ########################################################
   // Includes
   // ########################################################
   #include <stdio.h>
   #include <unistd.h>
   #include <stdlib.h>
   #include <errno.h>
   #include <string.h>
   #include <sys/types.h>
   #include <netinet/in.h>
   #include <sys/socket.h>
   #include <sys/wait.h>
   #include <arpa/inet.h>
   #include <netdb.h>
   
   
   // ########################################################
   // Defines
   // ########################################################
   #define PORT         3490	   // El puerto donde se conecta, servidor. 
   #define BACKLOG      10       // Tamaño de la cola de conexiones recibidas.
   
   
   // ########################################################
   // Funciones
   // ########################################################

   // ### SERVIDOR ###
   int	open_conection( struct sockaddr_in *addr );  /* Función que crea la conexión. */
   int	aceptar_pedidos( int sockfd );	            /* Función que acepta una conexión entrante. */
   
   // ### CLIENTE ###
   int	conectar( int argc, char *argv[] );          // Recibe el PUERTO como texto.
#endif