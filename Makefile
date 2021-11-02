CC=gcc
AR=ar
FLAGS= -Wall -g

all: slast 

slast: slast.c
	$(CC) $(FLAGS) slast.c -o slast 

.PHONY: clean all

clean:
	rm -f *.o slast


