#############################
#
#	Makefile
#	Linux Compilation
#
#############################

CC := g++
LFLAGS := -std=c++14
CFLAGS := -c -Wall
OBJECTS01 := main.o
OBJECTS02 := test.o
OBJECTS03 := Trie.o Dictionary.o

.PHONY: all
all: AutoComplete Test

AutoComplete: main.o Trie.o Dictionary.o
	#g++ -g -o AutoComplete main.o Trie.o Dictionary.o
	$(CC) $(LFLAGS) -g -o AutoComplete $(OBJECTS01) $(OBJECTS03)

Test: test.o Trie.o Dictionary.o
	#g++ -g -o Test test.o Trie.o Dictionary.o
	$(CC) $(LFLAGS) -g -o Test $(OBJECTS02) $(OBJECTS03)

main.o: Dictionary.h

Trie.o: Trie.h

Dictionary.o: Dictionary.h

.PHONY: clean
clean:
	\rm AutoComplete Test $(OBJECTS01) $(OBJECTS02) $(OBJECTS03)

