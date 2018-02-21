import sys

file_lines = sys.stdin.readlines()
num_queries = int(file_lines[0])
del file_lines[0]
fract_list = []
#first step: get list of fractions
for line in file_lines:
    space_ind = line.find(" ")
    a = int(line[:space_ind])
    b = int(line[(space_ind + 1):])
    fract_list.append(a/b)

