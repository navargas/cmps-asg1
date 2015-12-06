ALLC    = $(wildcard *.c)
MAINC	= $(filter-out test.c,$(ALLC))
TESTC	= $(filter-out main.c,$(ALLC))

ALLO    = $(patsubst %.c,%.o,$(ALLC))
MAINO	= $(filter-out test.o,$(ALLO))
TESTO	= $(filter-out main.o,$(ALLO))

CC	= gcc
FLAGS	= -Wall -g
BIN	= BestStuffEver
TESTBIN	= BestStuffEver.test

.PHONY : all
all : $(BIN)

.PHONY : test
test : $(TESTBIN)
	valgrind ./$(TESTBIN)

.PHONY : clean
clean :
	rm -f *.o
	rm -f $(BIN)
	rm -f $(TESTBIN)

$(BIN)  : $(MAINC)
	$(CC) $(FLAGS) -c $(ALLC)
	$(CC) $(MAINO) -o $(BIN)

$(TESTBIN)  : $(TESTC)
	$(CC) $(FLAGS) -c $(TESTC)
	$(CC) $(TESTO) -o $(TESTBIN)

# Usually I have a src/ util/ bin/ directory structure and I can call
# this target from the root directory with make -c
# The "submit" tool does not allow directories, so I added the "all"
# and "test" targets above.
.PHONY : remote
remote :
	$(CC) $(FLAGS) -c $(ALLC)
