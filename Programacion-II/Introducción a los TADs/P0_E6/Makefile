#all: main

#main: main.o crearMatriz.o asignarElemento.o obtenerElemento.o suma.o producto.o destruirMatriz.o imprimirMatriz.o
#	gcc -o main main.o crearMatriz.o asignarElemento.o obtenerElemento.o suma.o producto.o destruirMatriz.o imprimirMatriz.o

#main.o: main.c matriz.h
#	gcc -c main.c 

#crearMatriz.o: crearMatriz.c matriz.h
#	gcc -c crearMatriz.c 

#asignarElemento.o: asignarElemento.c matriz.h
#	gcc -c asignarElemento.c 

#obtenerElemento.o: obtenerElemento.c matriz.h
#	gcc -c obtenerElemento.c 

#suma.o: suma.c matriz.h
#	gcc -c suma.c

#producto.o: producto.c matriz.h
#	gcc -c producto.c

#destruirMatriz.o: destruirMatriz.c matriz.h
#	gcc -c destruirMatriz.c 

#imprimirMatriz.o: imprimirMatriz.c matriz.h
#	gcc -c imprimirMatriz.c

#clean: 
#	rm -f main *.o

#VERSIÓN CON VARIABLES

CC= gcc -Wall

LIBS=

HEADER_FILES_DIR = ./include

INCLUDES = -I$(HEADER_FILES_DIR)

OUTPUT = main

LIB_HEADERS = $(HEADER_FILES_DIR)/matriz.h

SRCS = asignarElemento.c destruirMatriz.c main.c suma.c crearMatriz.c imprimirMatriz.c obtenerElemento.c producto.c

OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall:clean
	rm -f $(OUTPUT)

clean:
	rm -f *.o *~
	