def move(amount, src, dst):
    for i in range(amount):
        stacks[dst].append(str(stacks[src].pop()))

def part_two(amount, src, dst):
    stacks[dst] += stacks[src][len(stacks[src]) - amount:]
    stacks[src] = stacks[src][:len(stacks[src]) - amount]
    

file = open("input.txt")
lines = file.readlines()

stacks = ["" for i in range(0, 9)]
for i in range(7, -1, -1):
    k = 1
    for j in range(0, 9):
        if (lines[i][k] != ' '):
            stacks[j] += (lines[i][k])
        k += 4
print(stacks)

for i in range(10, 512):
    line = lines[i].strip().split(' ')
    # move(int(line[1]), int(line[3]) -1, int(line[5]) -1)
    part_two(int(line[1]), int(line[3]) -1, int(line[5]) -1)
    if i == 10:
        print(stacks)

ret = ""
for stack in stacks:
    ret += (stack[len(stack) - 1])

print(ret)