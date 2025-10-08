#ifndef STRUCT_DATOS
   #define STRUCT_DATOS
   
   // ########################################################
   // Defines
   // ########################################################
   #define TAM_DATE           11
   #define TAM_DESC           20
   #define TAM_DET            200
   
   #define CARDIOLOGIA        0
   #define CLINICA            1
   #define GASTROENTEROLOGIA  2
   #define CIRUGIA            3
   #define DERMATOLOGIA       4
   #define OFTALMOLOGIA       5
   #define TRAUMATOLOGIA      6

   // ########################################################
   // Dato_t
   // ########################################################
   typedef struct equipamiento {
      int   sku;                       // Identificador de modelo (puede repetirse).
      char  descripcion[ TAM_DESC ];
      char  detalles[ TAM_DET ];
      int   cantidad;                  // Disponibilidad / Stock.
      int   especialidad;
      float precio;
   } Dato_t;
   /* Cada NODO de la lista va a ser un SKU de equipamiento.
    * Los IDs se repiten si los SKUs también se repiten.
    */

   // ########################################################
   // Nodo_t
   // ########################################################
   typedef struct Nodo_s {
      struct Nodo_s *prevNode;
      struct Nodo_s *nextNode;
      Dato_t         dato;
   } Nodo_t;
#endif