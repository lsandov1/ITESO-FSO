all: matrprimos matrprimos_p ejemplo3

matrprimos: matrprimos.c
	gcc -o matrprimos matrprimos.c -lm

ejemplo3: ejemplo3.c
	gcc -o ejemplo3 ejemplo3.c -lpthread -lm


matrprimos_p: matrprimos_p.c
	gcc -o matrprimos_p matrprimos_p.c -lpthread -lm


clean:
	rm matrprimos matrprimos_p
