GCC = gcc
GCCFLAGS = -c -Wall -Werror
VPATH = src:build
PATH_IN = ./src/
PATH_BUILD = ./build/
PATH_OUT = ./bin/
QZ_F_CHDIR = quizrunner_changedir
QZ_F_CFILE = quizrunner_closefile
QZ_F_CRBUF = quizrunner_createbuffer
QZ_F_MAIN = quizrunner_main
QZ_F_OFILE = quizrunner_openfile
QZ_F_WTBUF = quizrunner_writetobuffer
QZ_F_OFILEW = quizrunner_openfile_write

all: prog

prog: $(QZ_F_MAIN).o $(QZ_F_CHDIR).o $(QZ_F_CHDIR).o $(QZ_F_CFILE).o $(QZ_F_CRBUF).o $(QZ_F_OFILE).o $(QZ_F_WTBUF).o $(QZ_F_OFILEW).o
	$(GCC) $(PATH_BUILD)$(QZ_F_MAIN).o $(PATH_BUILD)$(QZ_F_CHDIR).o $(PATH_BUILD)$(QZ_F_CFILE).o $(PATH_BUILD)$(QZ_F_CRBUF).o $(PATH_BUILD)$(QZ_F_OFILE).o $(PATH_BUILD)$(QZ_F_WTBUF).o $(PATH_BUILD)$(QZ_F_OFILEW).o -o $(PATH_OUT)prog.exe

$(QZ_F_MAIN).o: $(QZ_F_MAIN).c
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_MAIN).o $(PATH_IN)$(QZ_F_MAIN).c

$(QZ_F_CHDIR).o: $(QZ_F_CHDIR).c $(QZ_F_CHDIR).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_CHDIR).o $(PATH_IN)$(QZ_F_CHDIR).c

$(QZ_F_CFILE).o: $(QZ_F_CFILE).c $(QZ_F_CFILE).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_CFILE).o $(PATH_IN)$(QZ_F_CFILE).c

$(QZ_F_CRBUF).o: $(QZ_F_CRBUF).c $(QZ_F_CRBUF).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_CRBUF).o $(PATH_IN)$(QZ_F_CRBUF).c

$(QZ_F_OFILE).o: $(QZ_F_OFILE).c $(QZ_F_OFILE).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_OFILE).o $(PATH_IN)$(QZ_F_OFILE).c

$(QZ_F_WTBUF).o: $(QZ_F_WTBUF).c $(QZ_F_WTBUF).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_WTBUF).o $(PATH_IN)$(QZ_F_WTBUF).c

$(QZ_F_OFILEW).o: $(QZ_F_OFILEW).c $(QZ_F_OFILEW).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_OFILEW).o $(PATH_IN)$(QZ_F_OFILEW).c
clean: rm -rf *.o *.exe