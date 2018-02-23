#Makefile, written by Andrew H. Pometta, for the purposes of compiling
#Project Euler Question 207 for HackerRank.  default target creates the
#integer_partition executable from ratio_k_calculator files and
#integer_partition.cpp.  Make naive makes the Python naive attempt.

COMP = g++ -std=c++11 -Wall -Wextra
DEP = ratio_k_calculator
MAIN = integer_partition
HSRC = $(DEP).hpp
CSRC = $(DEP).cpp $(MAIN).cpp
TEST = test/test*.txt
PSRC = naive_attempt.py

all: allX

#Compiles main program.
main: $(CSRC)
	$(COMP) $(CSRC) -o $(MAIN)

$(DEP).cpp: $(DEP).hpp
	$(COMP) -c $@

$(MAIN).cpp:
	$(COMP) -c $@

allX: main
	rm *.o
