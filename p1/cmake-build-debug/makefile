CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps

all: process.o p1.o
	$(CC) -o $(EXE) process.o p1.o

process.o: process.c
	$(CC) $(WARNING_FLAGS) -c process.c

p1.o: p1.c
	$(CC) $(WARNING_FLAGS) -c p1.c

clean:
	rm $(EXE) *.o
