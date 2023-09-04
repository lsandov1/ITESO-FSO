all: semsejemplo1 semsprodcons_threads semsprodcons_proc

semsejemplo1:
	gcc -o semsejemplo1 semsejemplo1.c semaphoresarr.c
	
semsprodcons_threads:
	gcc -o semsprodcons_threads semsprodcons_threads.c semaphoresarr.c

semsprodcons_proc:
	gcc -o semsprodcons_proc semsprodcons_proc.c semaphoresarr.c -lm
	
clean:
	rm semsejemplo1 semsprodcons_threads semsprodcons_proc