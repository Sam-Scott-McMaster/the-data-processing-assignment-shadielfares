main: clean.c create.c manipulate.c manipulate.h create.h
	gcc -o clean clean.c manipulate.c create.c


test: clean.c create.c manipulate.c manipulate.h create.h
	gcc -o test --coverage clean.c manipulate.c create.c

clean:
	rm -f clean
