.PHONY: diff

GCCSTD=-std=c99

ifeq ($(OS),Windows_NT)
   DIFF = fc
else
   DIFF = diff
endif


diff: debug_out_to_file.gotten  debug_out_to_memory.gotten
	@$(DIFF) debug_out_to_file.gotten   debug_out_to_file.expected
	@$(DIFF) debug_out_to_memory.gotten debug_out_to_memory.expected

debug_out_to_file.gotten: tq84_test_debug_to_file
	@./tq84_test_debug_to_file
	
debug_out_to_memory.gotten: tq84_test_debug_to_memory
	@./tq84_test_debug_to_memory

#
#  Creating the executables
#

tq84_test_debug_to_file:    tq84_debug_to_file.o main_debug_to_file.o
	@gcc $(GCCSTD)            tq84_debug_to_file.o main_debug_to_file.o    -o tq84_test_debug_to_file

tq84_test_debug_to_memory: tq84_debug_to_memory.o main_debug_to_memory.o
	@gcc $(GCCSTD)           tq84_debug_to_memory.o main_debug_to_memory.o -o tq84_test_debug_to_memory

#
#  Creating *.o files
#
#     The the TO_FILE files

tq84_debug_to_file.o: ../tq84_debug.c ../tq84_debug.h
	@gcc $(GCCSTD) -DTQ84_DEBUG_ENABLED -DTQ84_DEBUG_TO_FILE -W -Wall -Wextra -c ../tq84_debug.c -o tq84_debug_to_file.o

main_debug_to_file.o: ../tq84_debug.h main_debug_to_file.i
	@gcc $(GCCSTD) -I.. -W -Wall -Wextra -c main_debug_to_file.i -o main_debug_to_file.o

#
#     The the TO_MEMORY files
#     

tq84_debug_to_memory.o: tq84_debug_to_memory.i
	@gcc $(GCCSTD) -DTQ84_DEBUG_ENABLED -DTQ84_DEBUG_TO_MEMORY -W -Wall -Wextra -c tq84_debug_to_memory.i -o tq84_debug_to_memory.o

main_debug_to_memory.o: ../tq84_debug.h main_debug_to_memory.i
	@gcc $(GCCSTD) -I.. -W -Wall -Wextra -c main_debug_to_memory.i -o main_debug_to_memory.o

#
#  Creating *.i files
#

main_debug_to_file.i:  ../tq84_debug.h main.c
	@gcc $(GCCSTD) -DTQ84_DEBUG_ENABLED -DTQ84_DEBUG_TO_FILE -I.. -W -Wall -Wextra -E main.c -o main_debug_to_file.i

main_debug_to_memory.i:  ../tq84_debug.h main.c
	@gcc $(GCCSTD) -DTQ84_DEBUG_ENABLED -DTQ84_DEBUG_TO_MEMORY -I.. -W -Wall -Wextra -E main.c -o main_debug_to_memory.i

tq84_debug_to_memory.i:  ../tq84_debug.c ../tq84_debug.h
	@gcc $(GCCSTD) -DTQ84_DEBUG_ENABLED -DTQ84_DEBUG_TO_MEMORY -W -Wall -Wextra -E ../tq84_debug.c -o tq84_debug_to_memory.i

clean:
	@rm -f *.o *.i tq84_test*
