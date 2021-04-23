main: main.o background.o redirect.o execute.o pipeline.o sequence.o
	gcc -o main main.o background.o redirect.o execute.o pipeline.o sequence.o
main.o: main.c main.h
	gcc -c main.c
background.o: background.c background.h
	gcc -c background.c
redirect.o: redirect.c redirect.h
	gcc -c redirect.c
execute.o: execute.c execute.h
	gcc -c execute.c
pipeline.o: pipeline.c pipeline.h
	gcc -c pipeline.c
sequence.o: sequence.c sequence.h
	gcc -c sequence.c


