GCCFLAGS = -c -Wall -Werror
VPATH = src:build
PATH_SRC = ./src/
PATH_BUILD = ./build/

all: bin build prog

bin:
	mkdir -p bin

build:
	mkdir -p build

prog: nameFile.o
	g++ build/nameFile.o -o bin/prog

nameFile.o: nameFile.c
	g++ $(GCCFLAGS) $(PATH_SRC)nameFile.c -o $(PATH_BUILD)nameFile.o

.PHONY: clean
clean:
	rm -rf build bin