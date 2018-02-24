
.PHONY: diff

diff: tq84_test_debug_to_file
	@./tq84_test_debug_to_file
	@diff /tmp/tq84_debug_out_to_file debug_out.expected

tq84_test_debug_to_file: tq84_debug_to_file.o main_debug_to_file.o
	@gcc tq84_debug_to_file.o main_debug_to_file.o -o tq84_test_debug_to_file


tq84_debug_to_file.o: ../tq84_debug.c ../tq84_debug.h
	@gcc -DTQ84_DEBUG_TO_FILE -W -Wall -Wextra -c ../tq84_debug.c -o tq84_debug_to_file.o

# main.o: ../tq84_debug.h main.c
# 	@gcc -I.. -Wall -Wextra -c main.c -save-temps -o main.o

main_debug_to_file.o: ../tq84_debug.h main_debug_to_file.i
	@gcc -I.. -W -Wall -Wextra -c main_debug_to_file.i -o main_debug_to_file.o

main_debug_to_file.i:  ../tq84_debug.h main.c
	@gcc -DTQ84_DEBUG_TO_FILE -I.. -W -Wall -Wextra -E main.c -o main_debug_to_file.i

clean:
	@rm -f *.o *.i tq84_test*
