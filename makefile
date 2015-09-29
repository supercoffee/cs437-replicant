all: prog_gen bootstrap replicant_source replicant_bin

prog_gen: prog_gen.py
	python3 prog_gen.py bootstrap.c > prog.h

bootstrap: bootstrap.c prog.h
	gcc bootstrap.c -o bootstrap

replicant_source:
	./bootstrap > replicant.c

replicant_bin:
	gcc replicant.c -o replicant
