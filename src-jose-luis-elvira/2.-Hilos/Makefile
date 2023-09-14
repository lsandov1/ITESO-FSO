all: matrprimos matrprimos_p ejemplo3 ejemplo4 taylor

matrprimos: matrprimos.c
	gcc -o matrprimos matrprimos.c -lm

taylor: taylor-1.c
	gcc -o taylor taylor-1.c -lm

ejemplo3: ejemplo3.c
	gcc -o ejemplo3 ejemplo3.c -lpthread -lm

ejemplo4: ejemplo4.c
	gcc -o ejemplo4 ejemplo4.c -lpthread -lm

matrprimos_p: matrprimos_p.c
	gcc -o matrprimos_p matrprimos_p.c -lpthread -lm


clean:
	rm matrprimos matrprimos_p
