proj1: main.o loglib.o
	gcc -o proj1 main.o loglib.o
	rm -rf *.o
main.o: main.c log.h
	gcc -c main.c
loglib.o: loglib.c log.h
