all: dsv empty/empty

dsv: dsv.c
	tcc -Wall -c -o dsv.o dsv.c
	ld -static -s -z norelro -z noseparate-code -o dsv dsv.o /opt/diet/lib-x86_64/libc.a

empty/empty:
	as empty/empty.s -o empty/empty.o
	ld -static -s -z norelro -z noseparate-code -o empty/empty empty/empty.o

clean:
	rm -f dsv *.o */*.o empty/empty
