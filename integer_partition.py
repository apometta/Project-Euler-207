"""This file, written by Andrew H. Pometta on 2/20/2018, is a Python 3 program
for solving Project Euler problem #207 on HackerRank.  The problem's
description can be found at:
https://www.hackerrank.com/contests/projecteuler/challenges/euler/207

The readme file in this project explains the problem, solution and plan in
more detail.  Please consult the readme for explanations for certain decisions.
"""

"""Quick function for getting k from a given 2^t."""
def convertTwoTToK(two_t):
    #k = 2^t * (2*t - 1).  See readme for explanation.
    return two_t * (two_t - 1)

"""Returns smallest perfection ratio achievable in a given t-range."""
def getSmallestRatioInRange(t_range):
    #Just return the perfection ratio of the largest 2^t in this range.
    #See readme for explanation.
    largest_two_t = 2**(t_range + 1) - 1
    return t_range/(largest_two_t - 1)

"""Function taking in ratio and t-range to return the smallest 2^t for which
the perfection ratio of that 2^t is smaller than the given ratio.  This
assumes the inputted t-range has one such valid one: error testing should be
done outside this function."""
def getSmallestTwoT(t_range, ratio):
    """r = t/(2^t - 1).  Solving for two_t grants:
       2^t = (t/r) + 1.  However, note that this can return one of two things:
    1. A 2^t which is not an integer.
    2. An integer 2^t whose perfection ratio is exactly equal to the desired
       ratio to beat.
    Both of these have the same solution: turn the acquired 2^t to an integer
    and add one."""
    two_t = int((t_range / ratio) + 1) + 1
    print ("two_t = " + str(two_t))
    return two_t

#Take in input and format it in queries list.
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

#Fill array of minimum ranges for faster computation/searching
min_ranges = [0] #0 stored in 0th spot to avoid potential crash
for t in range(1, 65):
    min_ranges.append(getSmallestRatioInRange(t))

for q in queries:
    print("q = " + str(q))
    t_range = 1
    while q <= min_ranges[t_range]:
        t_range += 1
    print("range = " + str(t_range))
    two_t = getSmallestTwoT(t_range, q)
    print(convertTwoTToK(two_t))
