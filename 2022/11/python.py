import sys
import math

class Monkey:
    def __init__(self, number, items, operation, test, true, false):
        self.number = number
        self.items = items
        self.operation = operation
        self.test = test
        self.true = true
        self.false = false
        self.inspected = 0
    
    def handle_item(self):
        self.inspected += 1
        item = self.items.pop(0)
        sign = self.operation[0]
        amount = self.operation[1:]
        if amount == "old":
            amount = item
        else:
            amount = int(amount)
        match sign:
            case '+':
                item += amount
            case '*':
                item *= amount
        # item = math.floor(item / 3)
        divider = 2*3*5*7*11*13*15*17*19
        if item > divider:
            item = item % divider
        if item % self.test:
            return self.false, item
        else:
            return self.true, item
    
    def add_item(self, item):
        self.items.append(item)
    
    def print_items(self):
        print(self.items)
        print(self.inspected)

def init_data(lines):
    monkies = []
    i = 1
    for line in lines:
        if i % 7 == 1:
            number = line.split(':')[0][-1]
            # print(number)
        elif i % 7 == 2:
            items = [int(i.strip()) for i in line.split(':')[1].strip().split(',')]
            # print(items)
        elif i % 7 == 3:
            operation = line.split(' ')[6:]
            operation = operation[0] + operation[1].strip()
            # print(operation)
        elif i % 7 == 4:
            test = int(line.split(' ')[5])
            # print(test)
        elif i % 7 == 5:
            true = int(line.split(' ')[9])
            # print(true)
        elif i % 7 == 6:
            false = int(line.split(' ')[9])
            monkies.append(Monkey(number, items, operation, test, true, false))
        i += 1
    return monkies

def do_round(monkies):
    for i in range(len(monkies)):
        while len(monkies[i].items):
            to_whom, item = monkies[i].handle_item()
            monkies[to_whom].add_item(item)
    # for i in range(len(monkies)):
    #     monkies[i].print_items()

def part_one(monkies):
    inspected =[]
    for i in range(len(monkies)):
        inspected.append(monkies[i].inspected)
    inspected.sort(reverse=True)
    print(inspected[0] * inspected[1])

if __name__ == "__main__":
    file = open(sys.argv[1])
    lines = file.readlines()

    monkies = init_data(lines)
    for i in range(10000):
        do_round(monkies)
    part_one(monkies)
