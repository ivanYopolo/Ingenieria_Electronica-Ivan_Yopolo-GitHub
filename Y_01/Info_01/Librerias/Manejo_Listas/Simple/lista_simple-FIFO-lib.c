
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
