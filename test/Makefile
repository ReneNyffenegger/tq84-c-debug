
tq84_test: tq84_debug.o main.o
	gcc tq84_debug.o main.o -o tq84_test

tq84_debug.o: ../tq84_debug.c ../tq84_debug.h
	gcc -Wall -Wextra -c ../tq84_debug.c -o tq84_debug.o

main.o: ../tq84_debug.h main.c
	gcc -I.. -Wall -Wextra -c main.c -o main.o

