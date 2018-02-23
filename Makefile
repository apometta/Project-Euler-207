#Author: Andrew H. Pometta
#Last Updated: 2/23/2018

#This Makefile is for compiling the HackerRank edition of Project Euler
#problem #207, available at:
#https://www.hackerrank.com/contests/projecteuler/challenges/euler207
#The default target, or main, compiles for the relevant files the main
#integer_partition executable.  clean removes the executable.  Naive runs the
#python program, and test tests the program on the three test files in the
#test directory.

#The use of an unnecessarily large amount of macros is an old habit.

COMP = g++ -std=c++11 -Wall -Wextra
DEP = ratio_k_calculator
EXEC = integer_partition
HSRC = $(DEP).hpp
CSRC = $(DEP).cpp $(EXEC).cpp
OFLS = $(DEP).o
TST1 = test/test.txt
TST2 = test/test2.txt
TST3 = test/test3.txt
TFLS = test/test*.txt
PSRC = naive_attempt.py

all: main

#Compiles main program.
main: $(CSRC)
	$(COMP) $(CSRC) -o $(EXEC)

$(DEP).cpp: $(DEP).hpp
	$(COMP) -c $@

$(EXEC).cpp:
	$(COMP) -c $@

clean: $(EXEC)
	rm $(EXEC)

naive: PSRC
	python3 $(PSRC)

test: $(TFLS)
	./$(EXEC) <$(TST1)
	./$(EXEC) <$(TST2)
	./$(EXEC) <$(TST3)
