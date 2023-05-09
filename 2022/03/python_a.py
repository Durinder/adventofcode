import string

file = open("input.txt")
lines = file.readlines()

common = []
def find_common(first, second):
        for i in first:
            for j in second:
                if i == j:
                    return i

alphabet = list(string.ascii_lowercase) + list(string.ascii_uppercase)
print(alphabet)

for line in lines:
    first = line[:int(len(line)/2)]
    second = line[int(len(line)/2):]
    common.append(find_common(first, second))

ret = 0
count = 1
for i in alphabet:
    for j in common:
        if i == j:
            ret += count
    count += 1

print(ret)
print(len(lines))