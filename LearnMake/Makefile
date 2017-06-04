#Declare the variables

CC = gcc

CFLAGS = -c -Wall

bit: all

all: main.o fun1.o
	$(CC) main.o fun1.o -o hello

main.o: main.c
	$(CC) $(CFLAGS) main.c

fun1.o: fun1.c
	$(CC) $(CFLAGS) fun1.c

clean:
	rm -rf *o hello

