/* ### Ej. Integrador + REDES ###
 * # Opciones MENÚ #
 * Cargar base de datos.
 * Realizar ABM (altas-bajas-modificaciones) del equipamiento.
   * ABM: Agregar (altas), eliminar (bajas) o modificar REGISTROS/DATOS.
 * Guardar base de datos con nombre.
 * Ordenar los elementos por especialidad, precio o disponibilidades.
 * Mostrar todos los elementos de una determinada especialidad.
 * Mostrar la fecha de la base de datos.
 *
 * Cada NODO de la lista va a ser un SKU de equipamiento.
 * Los IDs se repiten si los SKUs también se repiten.
 * 
 * # Especialidades #
 * Cardiología.
 * Clínica.
 * Gastroenterología.
 * Cirugía. 
 * Dermatología. 
 * Oftalmología.
 * Traumatología.
 *
 * # IMPORTANTE #
 * Los primeros 11 Bytes del archivo deberán indicar 
 * la fecha de la base de datos en el siguiente formato: DD/MM/YYYY.
 *
 * # CONSIGNA ADICIONAL #
 * Se agregan 2 opciones:
   - Cargar datos remotamente.
   - Guardar datos remotamente.
 * En cada opción, se comunica el programa cliente con el servidor
 * en 1 de 2 puertos distintos; cada puerto se asocia o a CARGAR
 * (leer) o a GUARDAR datos remotamente. Los procesos del mismo archivo
 * se manejan con "fork()".
 */

#include "./includes/Equipamiento_medico/funciones_servidor.h"

/* # Comando SERVIDOR #
clear; gcc -Wall --pedantic-errors main_server.c \
./includes/debugging.c \
./includes/Equipamiento_medico/funciones_servidor.c \
./includes/GetString_console/getstring-lib.c \
./includes/Manejo_Listas/Doble/lista_doble-lib.c \
./includes/Sockets/sock-lib.c \
-o server.bin
*/

/* # Probando conexión con "net-cat" #
 * IP (loopback): 127.0.0.1
 * Puerto: [ VER PUERTO POR FUNCIÓN ].
   nc 127.0.0.1 [ VER PUERTO POR FUNCIÓN ]
 */

// Hacer "fork()" para que 2 procesos manejen puertos distintos.
int main( int argc, char *argv[] ) {
   
}

