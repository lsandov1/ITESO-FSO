all: pi pi_pthread pi_fork

pi: pi.c
	gcc -o pi pi.c -lm

pi_pthread: pi_pthread.c
	gcc -o pi_pthread pi_pthread.c -lm -lpthread

pi_fork: pi_fork.c
	gcc -o pi_fork pi_fork.c -lm

