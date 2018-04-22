GCC = gcc
GCCFLAGS = -c -Wall -Werror
VPATH = src
PATH_SRC = ./src/
PATH_BUILD = ./build/

all: prog

prog: quizrunner_main.o
	$(GCC) quizrunner_main.o -o $(PATH_BUILD)prog.exe

quizrunner_main.o: quizrunner_main.c
	$(GCC) $(GCCFLAGS) $(PATH_SRC)quizrunner_main.c

clean: rm -rf *.o *.exe