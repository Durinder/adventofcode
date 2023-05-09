import sys

def parse_line(line):
    packet = list
    count = 0
    for i in line:
        if i == '[':
            packet.append([])
        elif i == ']':
            count += 1
        elif i == ',':
            continue
        else:
            packet.append(int(i))
    print(packet)

def compare_lists(left, right):
    i = j = 0
    while True:
        if left[i] == ']' and right[j] != ']':
            return 2
        elif left[i] != ']' and right[j] == ']':
            return 1
        elif left[i] == '[' and right[j] == '[':
            ret = compare_lists(left[i+1:], right[j+1:])
            if ret == 1:
                return 1
            elif ret == 2:
                return 2
        elif left[i] 
    return 0

def is_right_order(left, right):
    i = j = 0
    while i < len(left):
        if left[i] == '[':
            if right[j] == '[':
                compare_lists(left[i+1:], right[j+1:])
            

    return True


def part_one(lines):
    for i in range(len(lines)):
        if i % 3 == 0:
            left = lines[i].strip()[1:-1]
        elif i % 3 == 1:
            right = lines[i].strip()[1:-1]
        else:
            is_right_order(left, right)

if __name__ == '__main__':
    file = open(sys.argv[1])
    lines = file.readlines()

    part_one(lines)