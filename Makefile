all: project

project: head.o
	gcc head.o -o project

head.o: head.c functions.h
	gcc -c head.c

clean:
	rm -rf *o project
