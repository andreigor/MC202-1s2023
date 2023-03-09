CC=gcc
CFLAGS=-std=c99 -pedantic -Wall
BINARY=bin
OBJECTS=TabuleiroXadrez_b.o
TESTS=tests
TEST_INPUT=$(TESTS)/inputs/input
TEST_OUTPUT=$(TESTS)/outputs/output


all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) -o $@ $^
	
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BINARY) *.o test_out.txt


test: $(BINARY) $(TEST_INPUT)*.txt 

.PHONY: $(TEST_OUTPUT)*.txt

$(TEST_INPUT)%.txt: $(TEST_OUTPUT)%.txt
	@ echo "####################################"
	@ echo "Test $(subst .txt,,$(subst $(TEST_INPUT),,$@))..." 
	@ ./$(BINARY) < $@ > test_out.txt
	@ diff $^ test_out.txt && echo "Passed!" || echo "Failed!"
