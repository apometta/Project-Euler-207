import sys

file_lines = sys.stdin.readlines()
num_queries = int(file_lines[0])
del file_lines[0]
fract_list = []
goal_fract = 1.1
#first step: get list of fractions
for line in file_lines:
    space_ind = line.find(" ")
    a = int(line[:space_ind])
    b = int(line[(space_ind + 1):])
    fract = a/b
    if fract < goal_fract:
        goal_fract = fract
    fract_list.append(fract)

#now we build the list
two_t = 2
k_list = []
#insert reasoning later - faster way of figuring out if partition is pure
next_2_pow = 2
partitions = 0
pure_partitions = 0
smallest_fract = 1.1
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

print(k_list)
    
