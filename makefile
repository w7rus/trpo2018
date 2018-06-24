GCC = gcc
GCCFLAGS = -c -Wall -Werror -Wno-unused-variable -std=c99 -std=gnu99
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
QZ_F_CRLFBF = quizrunner_crlfbufferfix
CTEST_MAIN = ctest_main
CTEST_TESTS = ctest_tests

all: app app2 test

app: $(QZ_F_MAIN).o $(QZ_F_CHDIR).o $(QZ_F_CFILE).o $(QZ_F_CRBUF).o $(QZ_F_OFILE).o $(QZ_F_WTBUF).o $(QZ_F_PRTLST).o $(QZ_F_ADDLSTE).o $(QZ_F_DTEXTR).o $(QZ_F_DTEXCNG).o $(QZ_F_DTCMP).o $(QZ_F_CRLFBF).o
	$(GCC) $(PATH_BUILD)$(QZ_F_MAIN).o $(PATH_BUILD)$(QZ_F_CHDIR).o $(PATH_BUILD)$(QZ_F_CFILE).o $(PATH_BUILD)$(QZ_F_CRBUF).o $(PATH_BUILD)$(QZ_F_OFILE).o $(PATH_BUILD)$(QZ_F_WTBUF).o $(PATH_BUILD)$(QZ_F_PRTLST).o $(PATH_BUILD)$(QZ_F_ADDLSTE).o $(PATH_BUILD)$(QZ_F_DTEXTR).o $(PATH_BUILD)$(QZ_F_DTEXCNG).o $(PATH_BUILD)$(QZ_F_DTCMP).o $(PATH_BUILD)$(QZ_F_CRLFBF).o -o $(PATH_OUT)quiz_runner.exe

test: $(CTEST_MAIN).o $(CTEST_TESTS).o $(QZ_F_CHDIR).o $(QZ_F_CFILE).o $(QZ_F_CRBUF).o $(QZ_F_OFILE).o $(QZ_F_WTBUF).o $(QZ_F_PRTLST).o $(QZ_F_ADDLSTE).o $(QZ_F_DTEXTR).o $(QZ_F_DTEXCNG).o $(QZ_F_DTCMP).o $(QZ_F_CRLFBF).o
	$(GCC) $(PATH_BUILD)$(CTEST_MAIN).o $(PATH_BUILD)$(CTEST_TESTS).o $(PATH_BUILD)$(QZ_F_CHDIR).o $(PATH_BUILD)$(QZ_F_CFILE).o $(PATH_BUILD)$(QZ_F_CRBUF).o $(PATH_BUILD)$(QZ_F_OFILE).o $(PATH_BUILD)$(QZ_F_WTBUF).o $(PATH_BUILD)$(QZ_F_PRTLST).o $(PATH_BUILD)$(QZ_F_ADDLSTE).o $(PATH_BUILD)$(QZ_F_DTEXTR).o $(PATH_BUILD)$(QZ_F_DTEXCNG).o $(PATH_BUILD)$(QZ_F_DTCMP).o $(PATH_BUILD)$(QZ_F_CRLFBF).o -o $(PATH_OUT)test_quiz_runner.exe

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

$(QZ_F_CRLFBF).o: $(QZ_F_CRLFBF).c $(QZ_F_CRLFBF).h
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QZ_F_CRLFBF).o $(PATH_IN)$(QZ_F_CRLFBF).c

QM_F_MAIN = quizmaker_main

app2: $(QM_F_MAIN).o
	$(GCC) $(PATH_BUILD)$(QM_F_MAIN).o -o $(PATH_OUT)quiz_maker.exe

$(QM_F_MAIN).o: $(QM_F_MAIN).c
	$(GCC) $(GCCFLAGS) -o $(PATH_BUILD)$(QM_F_MAIN).o $(PATH_IN)$(QM_F_MAIN).c