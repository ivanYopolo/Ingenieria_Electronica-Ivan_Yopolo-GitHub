#include "../inc/debugging.h"

//--------------------------------------------------------------------------
// show_data_log - [ DONE ]
//--------------------------------------------------------------------------
/* Muestra datos de un nodo en un archivo ".log".
 */
void show_data_log( Dato_t datoX, int fdLog ) {
   dprintf( fdLog, "\n#########################################################\n" );
   dprintf( fdLog, "* SKU:               \t%d\n", datoX.sku );
   dprintf( fdLog, "* Descripción:       \t%s\n", datoX.descripcion );
   dprintf( fdLog, "* Detalles:          \t%s\n", datoX.detalles );
   dprintf( fdLog, "* Cantidad en stock: \t%d\n", datoX.cantidad );
   dprintf( fdLog, "* Precio:            \t%.02f\n", datoX.precio );
   
   switch ( datoX.especialidad ){   // Imprimir según especialidad.
      case CARDIOLOGIA:
         dprintf( fdLog, "* Especialidad:      \tCARDIOLOGÍA.\n" );
      break;
      
      case CLINICA:
         dprintf( fdLog, "* Especialidad:      \tCLÍNICA.\n" );
      break;
      
      case GASTROENTEROLOGIA:
         dprintf( fdLog, "* Especialidad:      \tGASTROENTEROLOGÍA.\n" );
      break;
      
      case CIRUGIA:
         dprintf( fdLog, "* Especialidad:      \tCIRUGÍA.\n" );
      break;
      
      case DERMATOLOGIA:
         dprintf( fdLog, "* Especialidad:      \tDERMATOLOGÍA.\n" );
      break;
      
      case OFTALMOLOGIA:
         dprintf( fdLog, "* Especialidad:      \tOFTALMOLOGÍA.\n" );
      break;
      
      case TRAUMATOLOGIA:
         dprintf( fdLog, "* Especialidad:      \tTRAUMATOLOGÍA.\n" );
      break;
   }
}