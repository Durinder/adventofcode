import sys

def part_one(cmds):
    cycle = 0
    register = 1
    stack = []
    i = 0
    ret = 0
    while i < len(cmds) or len(stack):
        cycle += 1
        # print("start", cycle, stack, register)
        if i < len(cmds):
            cmd = cmds[i].strip().split(' ')
            if cmd[0] == "addx":
                stack.append(0)
                stack.append(int(cmd[1]))
            elif cmd[0] == "noop":
                stack.append(0)
        if (cycle + 20) % 40 == 0:
            ret += register * cycle
            # print("stack", cycle, stack, register)
        register += stack.pop(0)
        i += 1
        # print("end  ", cycle, stack, register)
    return ret

def part_two(cmds):
    cycle = 0
    register = 1
    stack = []
    i = 0
    CRT = []
    while i < len(cmds) or len(stack):
        cycle += 1
        if i < len(cmds):
            cmd = cmds[i].strip().split(' ')
            if cmd[0] == "addx":
                stack.append(0)
                stack.append(int(cmd[1]))
            elif cmd[0] == "noop":
                stack.append(0)
        position = cycle - 1
        position %= 40
        if register - 2 < position and register + 2 > position:
            pixel = '#'
        else:
            pixel = '.'
        CRT.append(pixel)
        register += stack.pop(0)
        i += 1
    for i in range(len(CRT)):
        print(CRT[i], end = '')
        if (i + 1) % 40 == 0:
            print()

if __name__ == "__main__":
    file = open(sys.argv[1])
    lines = file.readlines()

    print(part_one(lines))
    part_two(lines)