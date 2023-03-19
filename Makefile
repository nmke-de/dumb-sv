sv: sv.c
	tcc -Wall -c -o sv.o sv.c
	ld -static -s -z norelro -z noseparate-code -o sv sv.o /opt/diet/lib-x86_64/libc.a

clean:
	rm -f sv *.o
