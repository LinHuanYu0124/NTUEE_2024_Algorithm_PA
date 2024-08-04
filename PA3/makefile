# Variables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

# Targets
all: bin/cd
	@echo -n ""

bin/mps			:  main_opt.o 
			$(CC) $(OPTFLAGS)  main_opt.o -o bin/cd

main_opt.o 	   	: src/main.cpp 
			$(CC) $(CFLAGS) $< -o $@

# Debug version
dbg : bin/cd_dbg
	@echo -n ""

bin/cd_dbg	: cd_dbg.o lib
			$(CC) $(DBGFLAGS)  main_dbg.o -o bin/cd_dbg
main_dbg.o 	   	: src/main.cpp 
			$(CC) $(CFLAGS) $< -o $@
# Clean command
clean:
	rm -rf  bin/*



