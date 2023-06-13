all: dsv empty/empty

dsv: dsv.c print/libprint.a
	tcc -Wall -c -o dsv.o dsv.c
	ld -static -s -z norelro -z noseparate-code -o dsv dsv.o print/libprint.a /opt/diet/lib-x86_64/libc.a

empty/empty:
	as empty/empty.s -o empty/empty.o
	ld -static -s -z norelro -z noseparate-code -o empty/empty empty/empty.o

print/libprint.a: print
	cd print; make

print:
	git submodule update --init --remote

clean:
	rm -f dsv *.o */*.o empty/empty
