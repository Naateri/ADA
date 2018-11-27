import random

class Node():
    def __init__(self, name):
        self.name = name
        self.neighbours = list()

    def add_neighbour(self, node):
        self.neighbours.append(node)

class Edge():
    def __init__(self, a, b):
        self.a = a
        self.b = b

class Graph(): #Undirected Graph
    def __init__(self):
        self.nodes = list()
        self.edges = list()

    def add_node(self, name):
        temp_node = Node(name)
        self.nodes.append(temp_node)

    def add_edge(self, a, b): #a and b are nodes
        a.add_neighbour(b)
        b.add_neighbour(a)
        e = Edge(a,b)
        self.edges.append(e)

    def find_in_graph(self, name):
        for i in range(len(self.nodes)):
            if self.nodes[i].name == name:
                return i
        return -1

    def draw(self):
        for node in self.nodes:
            print( node.name + "->", end = '')
            for neighbour in node.neighbours:
                print (neighbour.name, end = '')
            print( )
    def fill_graph(self, num_nodes, num_edges = 0):
        if num_edges == 0:
            num_edges = 3*num_nodes
        difference = num_edges//num_nodes
        for i in range(num_nodes):
            node_name = str(i)
            self.add_node(node_name)
        for i in range(num_edges//difference):
            for j in range(difference):
                self.add_edge(self.nodes[i], self.nodes[random.randrange(len(self.nodes))])

    def find_path(self, k, cur_node, path):
        if (len(path) - 1 >= k):
            return True
        #path.append(cur_node.name)
        for neighbour in cur_node.neighbours:
            if neighbour.name in path:
                continue
            path.append(neighbour.name)
            if (self.find_path(k, neighbour, path) == True):
                return True
            path.pop()
        return False
    
    def longest_path(self, k):
        path = list()
        path.append(self.nodes[0].name)
        if self.find_path(k, self.nodes[0], path) == False:
            print ("No")
            return False
        else:
            print (path)
            return True

    def hamiltonian_cycle(self):
        if self.longest_path(len(self.nodes)-1):
            return True
        else:
            return False

G = Graph()
G.add_node('A')
G.add_node('B')
G.add_node('C')
G.add_node('D')
G.add_node('E')
G.add_edge(G.nodes[0], G.nodes[1])
G.add_edge(G.nodes[0], G.nodes[2])
G.add_edge(G.nodes[0], G.nodes[3])
G.add_edge(G.nodes[1], G.nodes[2])
G.add_edge(G.nodes[1], G.nodes[4])
G.add_edge(G.nodes[2], G.nodes[3])
G.add_edge(G.nodes[2], G.nodes[4])
G.draw()
G.longest_path(4)
G.hamiltonian_cycle()

H = Graph()
H.fill_graph(100)
#H.draw()
H.longest_path(90)
