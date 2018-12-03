class ds_node():
    def __init__(self,x):
        self.value = x
        self.parent = self
        self.rank = 0
        self.size = 1

class disjoint_set():
    def __init__(self):
        self.nodes = list()

    def make_set(self, x):
        temp_node = ds_node(x)
        if temp_node not in self.nodes:
            temp_node.parent = temp_node
            self.nodes.append(temp_node)

    def find(self, x):
        for node in self.nodes:
            if node.value == x:
        #        print(str(id(node)))
                return node
        return -1 #it found nothing

    def union(self, x, y):
        real_x = self.find(x)
        #print("union id: "+ str(id(real_x)))
        real_y = self.find(y)

        if real_x == real_y:
            return

        real_y.parent = real_x
        #print("y's " + str(real_y.value) + " parent: " + str(real_y.parent.value))
        if real_x.rank == real_y.rank:
            real_x.rank += 1

    def print_nodes(self):
        for node in self.nodes:
            print("node " + str(node.value) + ", ", end=" ")
        print()

    def print_subtrees(self, node):
        root = self.find(node)
        print ("node " + str(root.value) + ", father: ", end = " ")
        if root.parent == root:
            print ("None.")
            return
        self.print_subtrees(root.parent.value)

    def print_all_subtrees(self):
        for node in self.nodes:
            self.print_subtrees(node.value)
            

dsu = disjoint_set()
for i in range(1,11): #elems 1-10
    dsu.make_set(i)

dsu.print_nodes()
dsu.union(1,2)
dsu.union(3,4)
dsu.union(5,6)
dsu.union(7,8)
dsu.union(9,10)
dsu.union(1,3)

dsu.print_all_subtrees()

#not at all 100% working but we
