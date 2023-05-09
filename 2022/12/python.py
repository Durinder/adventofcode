import sys
import string

def get_map(lines):
    map = []
    for line in lines:
        map.append(line.strip())
    return map

def check_valid(connected, cur, visited):
    if visited == 1:
        return 0
    alphabet = ['S'] + list(string.ascii_lowercase) + ['E']
    if cur == 'S':
        cur = 'a'
    if connected == 'E':
        connected = 'z'
    if alphabet.index(connected) <= alphabet.index(cur) + 1:
        return 1
    return 0

def part_one(map):
    visited = [[0 for x in range(len(map[0]))] for i in range(len(map))]
    queue = []
    start = end = [0,0]
    for y in range(len(map)):
        for x in range(len(map[0])):
            if map[y][x] == 'S':
                start = y,x
            elif map[y][x] == 'E':
                end = y,x
    queue.append([start[0], start[1]] + [0])
    while True:
        next = queue.pop(0)
        no = next[2]
        cur = map[next[0]][next[1]]
        if cur == 'E':
            break
        if next[0] > 0:
            if check_valid(map[next[0] - 1][next[1]], cur, visited[next[0] - 1][next[1]]):
                queue.append([next[0] - 1,next[1], no + 1])
                visited[next[0] - 1][next[1]] = 1
        if next[0] < len(map) - 1:
            if check_valid(map[next[0] + 1][next[1]], cur, visited[next[0] + 1][next[1]]):
                queue.append([next[0] + 1, next[1], no + 1])
                visited[next[0] + 1][next[1]] = 1
        if next[1] > 0:
            if check_valid(map[next[0]][next[1] - 1], cur, visited[next[0]][next[1] - 1]):
                queue.append([next[0], next[1] - 1, no + 1])
                visited[next[0]][next[1] - 1] = 1
        if next[1] < len(map[0]) - 1:
            if check_valid(map[next[0]][next[1] + 1], cur, visited[next[0]][next[1] + 1]):
                queue.append([next[0], next[1] + 1, no + 1])
                visited[next[0]][next[1] + 1] = 1
    print(next[2])

def check_valid_two(connected, cur, visited):
    if visited == 1:
        return 0
    alphabet = ['S'] + list(string.ascii_lowercase) + ['E']
    if cur == 'E':
        cur = 'z'
    if connected == 'S':
        connected = 'a'
    if alphabet.index(connected) >= alphabet.index(cur) - 1:
        return 1
    return 0

def part_two(map):
    visited = [[0 for x in range(len(map[0]))] for i in range(len(map))]
    queue = []
    start = [0,0]
    for y in range(len(map)):
        for x in range(len(map[0])):
            if map[y][x] == 'E':
                start = y,x
    queue.append([start[0], start[1]] + [0])
    while True:
        next = queue.pop(0)
        no = next[2]
        cur = map[next[0]][next[1]]
        if cur == 'a':
            break
        if next[0] > 0:
            if check_valid_two(map[next[0] - 1][next[1]], cur, visited[next[0] - 1][next[1]]):
                queue.append([next[0] - 1,next[1], no + 1])
                visited[next[0] - 1][next[1]] = 1
        if next[0] < len(map) - 1:
            if check_valid_two(map[next[0] + 1][next[1]], cur, visited[next[0] + 1][next[1]]):
                queue.append([next[0] + 1, next[1], no + 1])
                visited[next[0] + 1][next[1]] = 1
        if next[1] > 0:
            if check_valid_two(map[next[0]][next[1] - 1], cur, visited[next[0]][next[1] - 1]):
                queue.append([next[0], next[1] - 1, no + 1])
                visited[next[0]][next[1] - 1] = 1
        if next[1] < len(map[0]) - 1:
            if check_valid_two(map[next[0]][next[1] + 1], cur, visited[next[0]][next[1] + 1]):
                queue.append([next[0], next[1] + 1, no + 1])
                visited[next[0]][next[1] + 1] = 1
    print(next[2])

if __name__ == "__main__":
    file = open(sys.argv[1])
    lines = file.readlines()

    map = get_map(lines)
    part_one(map)
    part_two(map)