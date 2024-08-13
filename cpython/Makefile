test: test.c solution.o
	cc test.c solution.o -o test

solution: solution.c
	cc -c solution.c

timer: solution.c timer.c
	cc solution.o timer.c -o timer

clean:
	rm -f a.out test *.o
