all: prog_gen prog

prog_gen: prog_gen.py
	python3 prog_gen.py assn2.c > prog.h

prog: assn2.c prog.h
	gcc assn2.c -o prog

bootstrap: prog
	./prog > bootstrap.c
