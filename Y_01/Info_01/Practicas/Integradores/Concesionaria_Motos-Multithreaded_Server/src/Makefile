# Con el "gcc -c" se genera un archivo objeto *.o.
# Así, no se tienen que recompilar TODOS los 
# *.c para volver a hacer el ejecutable, por cada cambio hecho.


################################################################
# VARIABLES #
################################################################
CC             = gcc
DEP_FLAGS      = -MD -MP
OBJ_DIR        = ../obj
BIN_DIR        = ../bin
INC_DIR        = ../inc
SRC_DIR        = .
# OBJS 				= $(SRCS:.c=.o)
# CLIENT #
TARGET_CL      = prog_cl
TARGET_CL_DIR  = $(BIN_DIR)/$(TARGET_CL).bin
OBJ_CL_DIR 		= ../obj/cl
OBJS_CL        = $(OBJ_DIR)/getstring-lib.o \
                 $(OBJ_DIR)/main_client.o \
                 $(OBJ_DIR)/funciones_client.o \
                 $(OBJ_DIR)/lista_doble-lib.o \
                 $(OBJ_DIR)/sock-lib.o
# SERVER #
TARGET_SRV     = prog_srv
TARGET_SRV_DIR = $(BIN_DIR)/$(TARGET_SRV).bin
OBJ_SRV_DIR 	= ../obj/srv
OBJS_SRV       = $(OBJ_DIR)/getstring-lib.o \
                 $(OBJ_DIR)/main_server.o \
                 $(OBJ_DIR)/funciones_server.o \
                 $(OBJ_DIR)/lista_doble-lib.o \
                 $(OBJ_DIR)/sock-lib.o
# Compiler Flags #
CFLAGS         = -Wall --pedantic-errors -I/$(INC_DIR)
# Linker Flags #
LDFLAGS        = -Wall --pedantic-errors -lpthread


################################################################
# Target PRINCIPAL #
################################################################
#
all : $(TARGET_SRV) $(TARGET_CL) Makefile


################################################################
# Linkeo #
################################################################
#
# Pattern Rules & Variables automáticas (Linker) #
# Automáticamente hace el archivo objeto de TODO .c en el proyecto. 
#
# $<   					sustituye por el nombre del primer pre-requisito (todos, uno a la vez).
# $^   					sustituye por el nombre de TODOS los pre-requisitos.
# $@   					sustituye por el nombre del INPUT (target de la regla).
# mkdir -p	 			crea la carpeta si no existe; sinó, ignora el comando.
# gcc -c 				compila pero no linkea, crea objetos *.o.
# gcc -o [archivo] 	linkea y genera [archivo].
#
# CLIENT #
$(TARGET_CL) : $(OBJS_CL)
	@echo ''
	@echo '#################################################################'
	@echo '###   Linkeando (CLIENT) ...   ###'
	@echo ''
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $(TARGET_CL_DIR)
	@echo ''
	@echo '###   Terminó de linkear.   ###'
	@echo '#################################################################'
	@echo ''
#
# SERVER #
$(TARGET_SRV) : $(OBJS_SRV)
	@echo ''
	@echo '#################################################################'
	@echo '###   Linkeando (SERVER) ...   ###'
	@echo ''
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $(TARGET_SRV_DIR)
	@echo ''
	@echo '###   Terminó de linkear.   ###'
	@echo '#################################################################'
	@echo ''
	

################################################################
# Compilado #
################################################################
#
# Pattern Rules & Variables automáticas (Linker) #
# Automáticamente hace el archivo objeto de TODO .c en el proyecto. 
#
# $<   					sustituye por el nombre del primer pre-requisito (todos, uno a la vez).
# $^   					sustituye por el nombre de TODOS los pre-requisitos.
# $@   					sustituye por el nombre del INPUT (target de la regla).
# mkdir -p	 			crea la carpeta si no existe; sinó, ignora el comando.
# gcc -c 				compila pero no linkea, crea objetos *.o.
# gcc -o [archivo] 	linkea y genera [archivo].
$(OBJ_DIR)/%o : $(SRC_DIR)/%c
	@echo ''
	@echo '#################################################################'
	@echo '###   Compilando $^...   ###'
	@echo ''
	@mkdir -p $(OBJ_DIR)
	$(CC) $(DEP_FLAGS) $(CFLAGS) -c $< -o $@ 
	@echo ''
	@echo '###   Terminó de compilar.   ###'
	@echo '#################################################################'
	@echo ''


################################################################
# Dependencias #
################################################################
#
# Para incluir dependencias *.h y sus cambios automáticamente #
# Ligado al -MD.
-include $(OBJ_DIR)/*.d


################################################################
# Clean #
################################################################
#
# El ".PHONY" evita conflictos con archivos de mismo nombre que
# los TARGETS.
# Cuando se ejecuta por terminal "make clean", 
# borra las carpetas no útiles (objetos y binarios).
.PHONY : clean $(TARGET_SRV) $(TARGET_CL) all
clean : 
	@echo ''
	@echo '#################################################################'
	@echo '###   Removiendo $(OBJ_DIR) $(BIN_DIR)...   ###'
	@rm -r $(OBJ_DIR) $(BIN_DIR)
	@echo '#################################################################'
	@echo ''
