"""This file, written by Andrew H. Pometta on 2/20/2018, is a Python 3 program
for solving Project Euler problem #207 on HackerRank.  The problem's 
description can be found at:
https://www.hackerrank.com/contests/projecteuler/challenges/euler/207

The readme file in this project explains the problem, solution and plan in 
more detail.  Please consult the readme for explanations for certain decisions.
Be aware that this current implementation is considered too slow to work: it 
times out on everything past the first test case.
"""

import sys

file_lines = sys.stdin.readlines()
del file_lines[0] #we don't need to know the number of queries

#first step: get list of fractions and place in list from file
#goal_fract stores the smallest one, so we know when to stop calculating later
fract_list = []
goal_fract = 1.1
for line in file_lines:
    space_ind = line.find(" ")
    a = int(line[:space_ind])
    b = int(line[(space_ind + 1):])
    fract = a/b
    if fract < goal_fract:
        goal_fract = fract
    fract_list.append(fract)

#now we build the list of tuples, (purity_ratio, corresponding k).  Only
#append to k_list when we find a purity_ratio smaller than the smallest current
#one, since otherwise there's no point in storing it.  Note that two_2 is
#2^t and the variable we incremement by - see readme.
two_t = 2
k_list = []
#whenever two_2 is a power of 2, we know we have a pure partition.  it's faster
#to just keep track of the next time we will have one rather than to calculate
#t with log base 2 and check for integer status every time.
next_2_pow = 2
partitions = 0
pure_partitions = 0
smallest_fract = 1.1 #the smallest P(m) so far
while two_t >= 2: #break this loop manually
    partitions += 1
    if two_t == next_2_pow:
        pure_partitions += 1
        next_2_pow *= 2
    purity_ratio = pure_partitions/partitions
    if purity_ratio < smallest_fract:
        k_list.append((purity_ratio, two_t**2 - two_t))
        smallest_fract = purity_ratio
    if purity_ratio < goal_fract:
        break
    two_t += 1


#With the way the code works, k_list is in decreasing order of purity ratio,
#and increasing order of k.
#last step: print out requests
for n in fract_list:
    for purity in k_list:
        if purity[0] < n:
            print(purity[1])
            break

