ALLC    = $(wildcard src/*.c)
MAINC	= $(filter-out src/test.c,$(ALLC))
TESTC	= $(filter-out src/main.c,$(ALLC))
ALLO    = $(patsubst %.c,%.o,$(ALLC))
MAINO	= $(filter-out src/test.o,$(ALLO))
TESTO	= $(filter-out src/main.o,$(ALLO))
MAKE	= make
SRC	= src/
BIN	= bin/hash
TESTBIN = bin/hash.test

RM := rm -f

.PHONY : all
all 	: $(BIN)

.PHONY : run
run	: $(BIN)
	$(BIN)

.PHONY : test
test 	: $(TESTBIN)
	valgrind $(TESTBIN)

.PHONY : vim
vim	:
	tmux-next make test

.PHONY : clean
clean	:
	$(RM) $(BIN) $(TESTBIN)
	$(RM) $(wildcard src/*.o)

$(BIN)  : $(MAINC)
	$(MAKE) -C $(SRC) all
	gcc $(MAINO) -o $(BIN)

$(TESTBIN) : $(TESTC)
	$(MAKE) -C $(SRC) all
	gcc $(TESTO) -o $(TESTBIN)
