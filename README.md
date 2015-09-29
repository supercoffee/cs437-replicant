#Replicant -- a self replicating program

###Design overview
The self replicating program is actually the output of the bootstrap program.
Run `make` to compile `replicant`, the self replicating program.
The make operation will also output the source of the replicant program.

`prog_gen.py` is a python script that reads the contents of the bootstrap source
and outputs a header file which is included in the bootstrap program.

Running the bootstrap program will output the replicant source.
Compiling the replicant and running it will of course output it's own source.

### Diffing the output of replicant
Compare the output of replicant with it's source

`diff replicant.c <(./replicant)`
