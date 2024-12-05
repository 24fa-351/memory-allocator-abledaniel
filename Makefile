all: system_malloc my_malloc

system_malloc:
	gcc -o testsys test.c

my_malloc:
	gcc -o testmy test.c memory.c

clean:
	rm -f testsys testmy
