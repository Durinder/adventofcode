def is_visible_direction(map, i, j, x, y):
    height = map[i][j]
    while i > 0 and j > 0 and i < len(map[0]) -1 and j < len(map) -1:
        i += y
        j += x
        if map[i][j] >= height:
            return 0
    return 1

def is_visible(map, i, j):
    for x in range(-1, 2, 1):
        for y in range(-1, 2, 1):
            if (x != 0 and y != 0) or (x == 0 and y == 0):
                continue
            if (is_visible_direction(map, i, j, x, y)):
                return 1
    return 0

def score_direction(map, i, j, x, y):
    height = map[i][j]
    count = 0
    while i > 0 and j > 0 and i < len(map[0]) -1 and j < len(map) - 1:
        i += y
        j += x
        if map[i][j] < height:
            count += 1
        elif map[i][j] >= height:
            count += 1
            break
    return count

def scenic_score(map, i, j):
    score = 1
    for x in range(-1, 2, 1):
        for y in range(-1, 2, 1):
            if (x != 0 and y != 0) or (x == 0 and y == 0):
                continue
            score *= score_direction(map, i, j, x, y)
    return score
            

if __name__ == "__main__":
    file = open("input.txt")
    lines = file.readlines()

    map = []
    for line in lines:
        map.append(line.strip())

    # count trees on the edges
    count = len(map[0]) * 2 + len(map) * 2 - 4
    for i in range(1, len(map[0])-1):
        for j in range(1, len(map)-1):
            count += is_visible(map, i, j)

    print(count)

    # part 2
    max = 0
    for i in range(0, len(map[0])):
        for j in range(0, len(map)):
            score = scenic_score(map, i, j)
            if score > max:
                max = score
    
    print(max)
