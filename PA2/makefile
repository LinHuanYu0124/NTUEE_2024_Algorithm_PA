# Variables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

# Targets
all: bin/mps
	@echo -n ""

bin/mps			:  main_opt.o 
			$(CC) $(OPTFLAGS)  main_opt.o -o bin/mps

main_opt.o 	   	: src/main.cpp 
			$(CC) $(CFLAGS) $< -o $@

# Debug version
dbg : bin/mps_dbg
	@echo -n ""

bin/mps_dbg	: mps_dbg.o lib
			$(CC) $(DBGFLAGS)  main_dbg.o -o bin/mps_dbg
main_dbg.o 	   	: src/main.cpp 
			$(CC) $(CFLAGS) $< -o $@
# Clean command
clean:
	rm -rf  bin/*



