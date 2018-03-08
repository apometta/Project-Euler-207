"""This file, written by Andrew H. Pometta on 2/20/2018, is a Python 3 program
for solving Project Euler problem #207 on HackerRank.  The problem's
description can be found at:
https://www.hackerrank.com/contests/projecteuler/challenges/euler/207

The readme file in this project explains the problem, solution and plan in
more detail.  Please consult the readme for explanations for certain decisions.
"""

#Take in input and format it in queries list, sorted decreasing.
import sys
file_lines = sys.stdin.readlines()
num_queries = file_lines[0]
del file_lines[0] #makes iteration over the list easier later
queries = []
for line in file_lines:
    space_ind = line.find(" ")
    a = int(line[:space_ind])
    b = int(line[(space_ind + 1):])
    queries.append(a/b)
queries.sort(reverse = True) #decreasing list of fractions

#Create list of minimum ratio in a given t-range.
