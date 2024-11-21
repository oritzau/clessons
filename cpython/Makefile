all: test

test: test.c solution.c
	cc test.c solution.c -o test

timer: solution.c timer.c
	cc solution.c timer.c -o timer

clean:
	rm -f a.out test timer *.o
