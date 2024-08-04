# Variables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O2

# Targets
all: bin/cb

bin/cb: main_opt.o
	$(CC) $(OPTFLAGS) main_opt.o -o bin/cb

main_opt.o: src/main.cpp
	$(CC) $(CFLAGS) $< -o $@

# Debug version
dbg: bin/cb_dbg

bin/cb_dbg: main_dbg.o
	$(CC) $(DBGFLAGS) main_dbg.o -o bin/cb_dbg

main_dbg.o: src/main.cpp
	$(CC) $(CFLAGS) $(DBGFLAGS) $< -o $@

# Clean command
clean:
	rm -rf bin/*

