class TreeNode:
    def __init__(self, name, data=0):
        self.name = name
        self.data = data
        self.children = []
        self.parent = None
    
    def add_child(self, child):
        self.child = child
        child.parent = self
        self.children.append(child)
    
    def print_tree(self):
        print('  '*self.get_level() + '|--' + self.name, end='')
        print('  '* (self.get_level() + 1) + ' ' + str(self.data))
        if self.children:
            for each in self.children:
                each.print_tree()
    
    def add_data(self, data):
        self.data += data

    def get_level(self):
        level = 0
        p = self.parent
        while p:
            p = p.parent
            level += 1
        return level

    def get_total_size(self):
        total = self.data
        if self.children:
            for each in self.children:
                total += each.get_total_size()
        self.data = total
        return total
    
def part_one(node):
    sum = 0
    if node.data <= 100000:
        sum += node.data
    if node.children:
        for each in node.children:
            sum += part_one(each)
    return sum

def find_smallest(node, need, current):
    if node.data >= need and (node.data < current or current == 0):
        current = node.data
    if node.children:
        for each in node.children:
            current = find_smallest(each, need, current)
    return current

def part_two(root, used_size):
    total_size = 70000000
    free = total_size - used_size
    update = 30000000
    need = update - free

    print(find_smallest(root, need, 0))

if __name__ == "__main__":
    file = open("input.txt")
    lines = file.readlines()

    root = TreeNode(name="root", data=0)
    current = root
    for line in lines:
        if line[2:6] == "cd /":
            current = root
        elif line[2:7] == "cd ..":
            if current.parent:
                current = current.parent
        elif line[2:4] == "cd":
            name = line[5:]
            new = TreeNode(name=name, data=0)
            current.add_child(new)
            for child in current.children:
                if child.name == name:
                    current = child
                    break
        elif line[0] != '$' and line[0].isnumeric():
            number = line.split(' ')
            current.add_data(int(number[0]))

root.print_tree()
used_size = root.get_total_size()
print(part_one(root))
part_two(root, used_size)