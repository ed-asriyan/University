CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c99
LD = gcc

all: main.o list.o student.o
	$(LD) main.o list.o student.o -o a.exe

main.o: main.c
	$(CC) -c main.c -o main.o $(CFLAGS)

list.o: list.c
	$(CC) -c list.c -o list.o $(CFLAGS)

student.o: student.c
	$(CC) -c student.c -o student.o $(CFLAGS)

clean:
	rm main.o list.o student.o a.exe

