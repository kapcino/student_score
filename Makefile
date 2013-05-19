.PHONY: all clean

all:
	gcc -o studentscore -Wall -ansi -g -std=c99 list.c main.c

clean:
	-rm -rf *.o studentscore studentscore.*
