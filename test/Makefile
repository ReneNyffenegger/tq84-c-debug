
diff: tq84_test
	@./tq84_test
	@diff /tmp/tq84_debug debug.expected

tq84_test: tq84_debug.o main.o
	@gcc tq84_debug.o main.o -o tq84_test


tq84_debug.o: ../tq84_debug.c ../tq84_debug.h
	@gcc -W -Wall -Wextra -c ../tq84_debug.c -o tq84_debug.o

# main.o: ../tq84_debug.h main.c
# 	@gcc -I.. -Wall -Wextra -c main.c -save-temps -o main.o

main.o: ../tq84_debug.h main.i
	@gcc -I.. -W -Wall -Wextra -c main.i -o main.o

main.i:  ../tq84_debug.h main.c
	@gcc -I.. -W -Wall -Wextra -E main.c -o main.i

clean:
	@rm -f *.o *.i tq84_test
