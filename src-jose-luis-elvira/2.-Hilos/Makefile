all: matrprimos matrprimos_p

matrprimos: matrprimos.c
	gcc -o matrprimos matrprimos.c -lm

matrprimos_p: matrprimos_p.c
	gcc -o matrprimos_p matrprimos_p.c -lpthread -lm


clean:
	rm matrprimos matrprimos_p