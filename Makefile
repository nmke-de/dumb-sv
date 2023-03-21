dsv: dsv.c
	tcc -Wall -c -o dsv.o dsv.c
	ld -static -s -z norelro -z noseparate-code -o dsv dsv.o /opt/diet/lib-x86_64/libc.a

clean:
	rm -f dsv *.o
