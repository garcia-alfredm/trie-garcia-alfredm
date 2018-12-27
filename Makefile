#############################
#
#	Makefile
#	Linux Compilation
#
#############################

#FLAGS
C++FLAG = -g -std=c++11 -Wall

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.

#Rules for .cpp files
# .SUFFIXES : .cpp .o

cpp.o:
		g++ $(C++FLAG) $(INCLUDES) -c $< -o $@

INCLUDES = -I.
LIBS_ALL = -L/usr/lib -L/user/local/lib $(MATH_LIBS)

#ZEROTH PROGRAM
ALL_OBJ0=Test_Trie.o 
PROGRAM_0=Test_Trie
$(PROGRAM_0): $(ALL_OBJ0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ0) $(INCLUDES) $(LIBS_ALL)

#FIRST PROGRAM
ALL_OBJ1=Test_Dict.o
PROGRAM_1=Test_Dict
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ1) $(INCLUDES) $(LIBS_ALL)

#SECOND PROGRAM
ALL_OBJ2=AutoComplete.o
PROGRAM_2=AutoComplete
$(PROGRAM_1): $(ALL_OBJ1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ2) $(INCLUDES) $(LIBS_ALL)

#Compiling all

all: 	
		make $(PROGRAM_0)
		make $(PROGRAM_1)
		make $(PROGRAM_2)

runtrietest:
		./$(PROGRAM_0) words.txt

rundicttest:
		./$(PROGRAM_1) words.txt

runautocomplete:
		./$(PROGRAM_2) words.txt
#Clean obj files

clean:
	(rm -f *.o; rm -f $(PROGRAM_0), rm -f $(PROGRAM_1))

(: