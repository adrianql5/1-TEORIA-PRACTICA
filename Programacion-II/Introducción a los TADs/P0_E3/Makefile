#all: programa

#main: main.o gcd.o sqrt.o
#	gcc -o main main.o gcd.o sqrt.o

#main.o: main.c operaciones.h
#	gcc -c main.c

#gcd.o: gcd.c operaciones.h
#	gcc -c gcd.c

#sqrt.o: sqrt.c operaciones.h
#	gcc -c sqrt.c 

#clear:
#	rm -f main main.o gcd.o sqrt.o

CC= gcc -Wall

LIBS=

HEADER_FILES_DIR = .

INCLUDES = -I$(HEADER_FILES_DIR)

OUTPUT = main

LIB_HEADERS = $(HEADER_FILES_DIR)/operaciones.h

SRCS = main.c gcd.c sqrt.c

OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

%.o: %.c $(LIB_HEADERS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall: clean
	rm -f $(OUTPUT)

clean:
	rm -f *.o *~