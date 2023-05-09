import sys

def get_dimensions(lines: list[str]) -> int | int:
    x = y = max_x = max_y = min_x = min_y = 0
    for line in lines:
        amount = int(line[2:])
        match line[0]:
            case 'D':
                for i in range(amount):
                    y += 1
                    if y > max_y:
                        max_y = y
            case 'U':
                for i in range(amount):
                    y -= 1
                    if y < min_y:
                        min_y = y
            case 'R':
                for i in range(amount):
                    x += 1
                    if x > max_x:
                        max_x = x
            case 'L':
                for i in range(amount):
                    x -= 1
                    if x < min_x:
                        min_x = x
    return abs(min_x) + max_x + 1, abs(min_y) + max_y + 1, abs(min_x), abs(min_y)

def move(dir, H, T, bridge):
    H[0] += dir[0]
    H[1] += dir[1]

    diff_y = H[0] - T[0]
    diff_x = H[1] - T[1]

    if diff_y == 2:
        T[0] += 1
        if abs(diff_x):
            T[1] += diff_x
    elif diff_y == -2:
        T[0] -= 1
        if abs(diff_x):
            T[1] += diff_x
    
    if diff_x == 2:
        T[1] += 1
        if abs(diff_y):
            T[0] += diff_y
    elif diff_x == -2:
        T[1] -= 1
        if abs(diff_y):
            T[0] += diff_y

    if bridge[T[0]][T[1]] != 's':
        bridge[T[0]][T[1]] = '#'
    return H, T

def execute_commands(bridge, x, y, lines):
    H = [y, x]
    T = [y, x]
    bridge[T[0]][T[1]] = 's'
    for line in lines:
        amount = int(line[2:])
        if line[0] == 'D':
            for i in range(amount):
                H, T = move([1, 0], H, T, bridge)
        elif line[0] == 'U':
            for i in range(amount):
                H, T = move([-1, 0], H, T, bridge)
        elif line[0] == 'R':
            for i in range(amount):
                H, T = move([0, 1], H, T, bridge)
        elif line[0] == 'L':
            for i in range(amount):
                H, T = move([0, -1], H, T, bridge)
    return bridge

def move_two(dir, H, T):
    H[0] += dir[0]
    H[1] += dir[1]

    diff_y = H[0] - T[0]
    diff_x = H[1] - T[1]

    touching = True
    if abs(diff_y) + abs(diff_x) > 2:
        touching = False

    if diff_y > 1:
        T[0] = H[0] - 1
        if not touching:
            if diff_x > 0:
                T[1] += 1
            else:
                T[1] -= 1
    elif diff_y < -1:
        T[0] = H[0] + 1
        if not touching:
            if diff_x > 0:
                T[1] += 1
            else:
                T[1] -= 1
    elif diff_x > 1:
        T[1] = H[1] - 1
        if not touching:
            if diff_y > 0:
                T[0] += 1
            else:
                T[0] -= 1
    elif diff_x < -1:
        T[1] = H[1] + 1
        if not touching:
            if diff_y > 0:
                T[0] += 1
            else:
                T[0] -= 1

    return H, T    

def part_two(bridge, x, y, lines):
    rope = [[y, x] for i in range(10)]
    bridge[rope[0][0]][rope[0][1]] = 's'
    for line in lines:
        amount = int(line[2:])
        if line[0] == 'D':
            for i in range(amount):
                rope[0], rope[1] = move_two([1, 0], rope[0], rope[1])
                for j in range(1, 9):
                    rope[j], rope[j+1] = move_two([0,0], rope[j], rope[j+1])
                    if j == 8:
                        bridge[rope[j+1][0]][rope[j+1][1]] = '#'
        elif line[0] == 'U':
            for i in range(amount):
                rope[0], rope[1] = move_two([-1, 0], rope[0], rope[1])
                for j in range(1, 9):
                    rope[j], rope[j+1] = move_two([0,0], rope[j], rope[j+1])
                    if j == 8:
                        bridge[rope[j+1][0]][rope[j+1][1]] = '#'
        elif line[0] == 'R':
            for i in range(amount):
                rope[0], rope[1] = move_two([0, 1], rope[0], rope[1])
                for j in range(1, 9):
                    rope[j], rope[j+1] = move_two([0,0], rope[j], rope[j+1])
                    if j == 8:
                        bridge[rope[j+1][0]][rope[j+1][1]] = '#'
        elif line[0] == 'L':
            for i in range(amount):
                rope[0], rope[1] = move_two([0, -1], rope[0], rope[1])
                for j in range(1, 9):
                    rope[j], rope[j+1] = move_two([0,0], rope[j], rope[j+1])
                    if j == 8:
                        bridge[rope[j+1][0]][rope[j+1][1]] = '#'
    return bridge

if __name__ == "__main__":
    file = open(sys.argv[1])
    lines = file.readlines()

    x, y, start_x, start_y = get_dimensions(lines)
    bridge = [['.'] * x for i in range(y)]

    # bridge  = execute_commands(bridge, start_x, start_y, lines)

    bridge = part_two(bridge, start_x, start_y, lines)

    # for line in bridge:
    #     print(line)

    count = 0
    for line in bridge:
        for char in line:
            if char == '#' or char == 's':
                count += 1
    print(count)