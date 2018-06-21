GCC = gcc
GCCFLAGS = -c -Wall -Werror -Wno-unused-variable
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
QZ_F_PRTLST = quizrunner_printlist
QZ_F_ADDLSTE = quizrunner_addlistelement
QZ_F_DTEXTR = quizrunner_dataextract
QZ_F_DTEXCNG = quizrunner_dataexchange
QZ_F_DTCMP = quizrunner_datacompare
CTEST_MAIN = ctest_main
CTEST_TESTS = ctest_tests

all: app test

app: $(QZ_F_MAIN).o $(QZ_F_CHDIR).o $(QZ_F_CFILE).o $(QZ_F_CRBUF).o $(QZ_F_OFILE).o $(QZ_F_WTBUF).o $(QZ_F_PRTLST).o $(QZ_F_ADDLSTE).o $(QZ_F_DTEXTR).o $(QZ_F_DTEXCNG).o $(QZ_F_DTCMP).o
	$(GCC) $(PATH_BUILD)$(QZ_F_MAIN).o $(PATH_BUILD)$(QZ_F_CHDIR).o $(PATH_BUILD)$(QZ_F_CFILE).o $(PATH_BUILD)$(QZ_F_CRBUF).o $(PATH_BUILD)$(QZ_F_OFILE).o $(PATH_BUILD)$(QZ_F_WTBUF).o $(PATH_BUILD)$(QZ_F_PRTLST).o $(PATH_BUILD)$(QZ_F_ADDLSTE).o $(PATH_BUILD)$(QZ_F_DTEXTR).o $(PATH_BUILD)$(QZ_F_DTEXCNG).o $(PATH_BUILD)$(QZ_F_DTCMP).o -o $(PATH_OUT)prog.exe

test: $(CTEST_MAIN).o $(CTEST_TESTS).o $(QZ_F_CHDIR).o $(QZ_F_CFILE).o $(QZ_F_CRBUF).o $(QZ_F_OFILE).o $(QZ_F_WTBUF).o $(QZ_F_PRTLST).o $(QZ_F_ADDLSTE).o $(QZ_F_DTEXTR).o $(QZ_F_DTEXCNG).o $(QZ_F_DTCMP).o
	$(GCC) $(PATH_BUILD)$(CTEST_MAIN).o $(PATH_BUILD)$(CTEST_TESTS).o $(PATH_BUILD)$(QZ_F_CHDIR).o $(PATH_BUILD)$(QZ_F_CFILE).o $(PATH_BUILD)$(QZ_F_CRBUF).o $(PATH_BUILD)$(QZ_F_OFILE).o $(PATH_BUILD)$(QZ_F_WTBUF).o $(PATH_BUILD)$(QZ_F_PRTLST).o $(PATH_BUILD)$(QZ_F_ADDLSTE).o $(PATH_BUILD)$(QZ_F_DTEXTR).o $(PATH_BUILD)$(QZ_F_DTEXCNG).o $(PATH_BUILD)$(QZ_F_DTCMP).o -o $(PATH_OUT)test.exe

$(CTEST_TESTS).o: $(CTEST_TESTS).c
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(CTEST_TESTS).o $(PATH_IN)$(CTEST_TESTS).c

$(CTEST_MAIN).o: $(CTEST_MAIN).c
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(CTEST_MAIN).o $(PATH_IN)$(CTEST_MAIN).c

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

$(QZ_F_PRTLST).o: $(QZ_F_PRTLST).c $(QZ_F_PRTLST).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_PRTLST).o $(PATH_IN)$(QZ_F_PRTLST).c

$(QZ_F_ADDLSTE).o: $(QZ_F_ADDLSTE).c $(QZ_F_ADDLSTE).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_ADDLSTE).o $(PATH_IN)$(QZ_F_ADDLSTE).c

$(QZ_F_DTEXTR).o: $(QZ_F_DTEXTR).c $(QZ_F_DTEXTR).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_DTEXTR).o $(PATH_IN)$(QZ_F_DTEXTR).c

$(QZ_F_DTEXCNG).o: $(QZ_F_DTEXCNG).c $(QZ_F_DTEXCNG).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_DTEXCNG).o $(PATH_IN)$(QZ_F_DTEXCNG).c

$(QZ_F_DTCMP).o: $(QZ_F_DTCMP).c $(QZ_F_DTCMP).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_DTCMP).o $(PATH_IN)$(QZ_F_DTCMP).c