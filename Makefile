ALLC    = $(wildcard src/*.c)
MAINC	= $(filter-out src/test.c,$(ALLC))
TESTC	= $(filter-out src/main.c,$(ALLC))
BIN	= bin/hash
TESTBIN = bin/hash.test

.PHONY : all
all 	: $(BIN)

.PHONY : run
run	: $(BIN)
	$(BIN)

.PHONY : test
test 	: $(TESTBIN)
	$(TESTBIN)

$(BIN)  : $(MAINC)
	@echo $^
	gcc -Wall $^ -o $(BIN)

$(TESTBIN) : $(TESTC)
	@echo $^
	gcc -Wall $^ -o $(TESTBIN)
