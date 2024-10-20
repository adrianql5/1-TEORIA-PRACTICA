#all: main

#main: main.o
#	gcc -o main main.o

#main.o: main.c
#	gcc -c main.c

#clear:
#	rm -f main *.o

CC= gcc -Wall

LIBS=

HEADER_FILES_DIR = .

INCLUDES = -I $(HEADER_FILES_DIR)

OUTPUT = main

#LIB_HEADERS = $(HEADER_FILES_DIR)

SRCS = main.c

OBJS = $(SRCS:.c=.o)

$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) $(LIBS)

%.o: %.c #$(LIB_HEADERS)
	$(CC) -c –o $@ $< $(INCLUDES)

cleanall: clean
	rm -f $(OUTPUT)

clean:
	rm -f *.o *~