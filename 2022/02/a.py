
def get_result(opp, player):
    result = 0
    if opp == 'A':
        if player == 'X':
            return 4
        elif player == 'Y':
            return 8
        elif player == 'Z':
            return 3
    elif opp == 'B':
        if player == 'X':
            return 0 + 1
        elif player == 'Y':
            return 3 + 2
        else:
            return 6 + 3
    else:
        if player == 'X':
            return 6 + 1
        elif player == 'Y':
            return 0 + 2
        else:
            return 3 + 3

def choose_result(opp, player):
    result = 0
    if opp == 'A':
        if player == 'X':
            return 0 + 3
        elif player == 'Y':
            return 3 + 1
        elif player == 'Z':
            return 6 + 2
    elif opp == 'B':
        if player == 'X':
            return 0 + 1
        elif player == 'Y':
            return 3 + 2
        else:
            return 6 + 3
    else:
        if player == 'X':
            return 0 + 2
        elif player == 'Y':
            return 3 + 3
        else:
            return 6 + 1


if __name__ == "__main__":
    file = open('input.txt')
    lines = file.readlines()

    score = 0
    for line in lines:
        # score += get_result(line[0], line[2])
        score += choose_result(line[0], line[2])

    print(score)