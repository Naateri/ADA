class ds_node():
    def __init__(self,x):
        self.value = x
        self.parent = self
        self.rank = 0
        self.size = 1

"""
find: path compression (every node points to the root)
other finds:
path halving: every other node on the path points to its grandparent
path splitting: every node on the path points to its grandparent

Union: by rank (attaches the shorter tree to the rooot of the taller tree)
other union:
by size: attach the tree with fewer elements to the root of the tree with
more elements
"""

class disjoint_set():
    def __init__(self):
        self.nodes = list()

    def make_set(self, x):
        temp_node = ds_node(x)
        if temp_node not in self.nodes:
            temp_node.parent = temp_node
            self.nodes.append(temp_node)

    
    def find(self, x):
        if x.parent != x:
            x.parent = self.find(x.parent)
        return x.parent

    def union(self, x, y):
        xRoot = self.find(x)
        yRoot = self.find(y)

        if xRoot == yRoot:
            return

        if xRoot.rank < yRoot.rank:
            xRoot, yRoot = yRoot, xRoot

        yRoot.parent = xRoot

        print("y's " + str(yRoot.value) + " parent: " + str(yRoot.parent.value))
        
        if xRoot.rank == yRoot.rank:
            xRoot.rank = xRoot.rank + 1

    def print_nodes(self):
        for node in self.nodes:
            print("node " + str(node.value) + ", ", end=" ")
        print()

    def print_subtrees(self, node):
        print ("node " + str(node.value) + ", father: ", end = " ")
        while node.parent != node:
            node = node.parent
            print ("node " + str(node.value) + ", father: ", end = " ")
            #return
        #self.print_subtrees(root.parent)
        print ("None.")

    def print_all_subtrees(self):
        for node in self.nodes:
            self.print_subtrees(node)
            

dsu = disjoint_set()
for i in range(1,11): #elems 1-10
    dsu.make_set(i)

dsu.print_nodes()
dsu.union(dsu.nodes[0],dsu.nodes[1])
dsu.union(dsu.nodes[2],dsu.nodes[3])
dsu.union(dsu.nodes[4],dsu.nodes[5])
dsu.union(dsu.nodes[6],dsu.nodes[7])
dsu.union(dsu.nodes[8],dsu.nodes[9])
dsu.union(dsu.nodes[0],dsu.nodes[2])
dsu.union(dsu.nodes[3],dsu.nodes[8])
dsu.union(dsu.nodes[6],dsu.nodes[9])

dsu.print_all_subtrees()

