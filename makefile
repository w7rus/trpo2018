GCC = gcc
GCCFLAGS = -c -Wall -Werror -Wno-unused-variable -std=c99 -std=gnu99
VPATH = src:build
PATH_IN = ./src/
PATH_BUILD = ./build/
PATH_OUT = ./bin/
QM_F_MAIN = quizmaker_main

all: app2

app2: $(QM_F_MAIN).o
	$(GCC) $(PATH_BUILD)$(QM_F_MAIN).o -o $(PATH_OUT)quiz_maker.exe

$(QM_F_MAIN).o: $(QM_F_MAIN).c
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QM_F_MAIN).o $(PATH_IN)$(QM_F_MAIN).c