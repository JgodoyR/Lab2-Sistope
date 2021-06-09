CC=gcc

FLAGS = -g -Wall 

all: lab2
	echo "./lab2 -I imagen1.raw -O imagen1F.raw -M 512 -N 512 -r 2 -g 270 -b"

lab2: lab2.o io.o funciones.o
	${CC} lab2.o io.o funciones.o -o lab2 ${FLAGS}

lab2.o: lab2.c struct.h io.h funciones.h
	${CC} lab2.c -c ${FLAGS}

io.o: io.c struct.h io.h funciones.h
	${CC} io.c -c ${FLAGS}

funciones.o: funciones.c struct.h io.h funciones.h
	${CC} funciones.c -c ${FLAGS}

clean:
	rm lab2 *.o -f