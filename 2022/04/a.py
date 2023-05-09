def contains(haystack, needle):
    if haystack[0] <= needle[0] and haystack[1] >= needle[1]:
        return 1
    return 0

def part_two(haystack, needle):
    if needle[0] >= haystack[0] and needle[0] <= haystack[1]:
        return 1
    elif needle[1] >= haystack[0] and needle[1] <= haystack[1]:
        return 1
    return 0

file = open("input.txt")
lines = file.readlines()

ret = 0
for line in lines:
    split = line.split(',')
    first = list(map(int, split[0].split('-')))
    second = list(map(int, split[1].split('-')))
    if first[1] - first[0] < second[1] - second[0]:
        ret += part_two(second, first)
    else:
        ret += part_two(first, second)
print(ret)

