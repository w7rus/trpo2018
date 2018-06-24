GCCFLAGS = -c -Wall -Werror
VPATH = src:build
PATH_SRC = ./src/
PATH_BUILD = ./build/

all: bin build prog

bin:
	mkdir -p bin

build:
	mkdir -p build

prog: testGenerator_main.o
	g++ build/testGenerator_main.o -o bin/prog

testGenerator_main.o: testGenerator_main.c
	g++ $(GCCFLAGS) $(PATH_SRC)testGenerator_main.c -o $(PATH_BUILD)testGenerator_main.o

.PHONY: clean
clean:
	rm -rf build bin