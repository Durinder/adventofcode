def move_buffer(new):
    buffer[0] = buffer[1]
    buffer[1] = buffer[2]
    buffer[2] = buffer[3]
    buffer[3] = new

def isUnique(buffer):
    if buffer[0] != buffer[1] and buffer[0] != buffer[2] and buffer[0] != buffer[3]:
        if buffer[1] != buffer[2] and buffer[1] != buffer[3]:
            if buffer[2] != buffer[3]:
                return True
    return False

def part2MoveBuffer(new):
    new_buffer = []
    for i in range(13):
        new_buffer.append(buffer[i+1])
    if new in new_buffer:
        new_buffer[new_buffer.index(new)] = "0"
    new_buffer.append(new)
    return new_buffer

def part2IsUnique(buffer):
    if "0" not in buffer:
        return True
    return False

file = open("input.txt")
data = file.read()

buffer = ["0" for i in range(14)]
counter = 0
for i in range(len(data)):
    buffer = part2MoveBuffer(data[i])
    counter += 1
    if counter >= 4:
        if part2IsUnique(buffer):
            print(counter)
            exit()