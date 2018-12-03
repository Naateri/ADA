import operator
import time
import random

ds_nodes = list()

graph_sizes = [10, 100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000]

class ds_node():
    def __init__(self,x):
        self.value = x
        self.parent = self
        self.rank = 0
        self.size = 1

def make_set(x):
    temp_node = ds_node(x)
    return temp_node

def find(x):
    if (type(x) == int):
        x = ds_nodes[x]
    if x.parent != x:
        x.parent = find(x.parent)
    return x.parent

def union(x,y):
    xRoot = find(x)
    yRoot = find(y)
    if xRoot == yRoot:
        return

    if xRoot.rank < yRoot.rank:
        xRoot, yRoot = yRoot, xRoot

    yRoot.parent = xRoot

    if xRoot.rank == yRoot.rank:
        xRoot.rank = xRoot.rank + 1

class Node():
    def __init__(self, name):
        self.name = name
        self.neighbours = list()
        self.color = 'w' #color for dfs

    def add_neighbour(self, node, w):
        self.neighbours.append([node, w])

def print_nodelist(le_list):
    for node in le_list:
        print(node.name, end=" ")
    print()

class Edge():
    def __init__(self, a, b, w, dire):
        self.a = a
        self.b = b
        self.dire = dire
        self.weight = w

    def __lt__(self, e2): #less than
        return self.weight < e2.weight
    

class Graph(): #Weighted Graph
    def __init__(self):
        self.nodes = list()
        self.edges = list()
        self.nodes_names = list()

    def add_node(self, name):
        temp_node = Node(name)
        self.nodes.append(temp_node)
        self.nodes_names.append(name)

    def add_edge(self, a, b, w, dire = 0): #a and b are nodes, dire: 0 <->, 1->
        a.add_neighbour(b,w)
        if (dire == 0):
            b.add_neighbour(a,w)
        e = Edge(a,b, w, dire)
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
                print (neighbour[0].name + str(neighbour[1]), end = ' ')
            print( )

    def reset_colors(self):
        for node in self.nodes:
            node.color = 'w'

    def find_path(self, start, end): #start and end are nodes
        stack = [start] #dfs algorithm
        start.color = 'g'
        while len(stack) > 0:
            current = stack.pop()
            if current == end:
                self.reset_colors()
                #print ("path from " + current.name + " to " + neighbour[0].name)
                return True
                
            for neighbour in current.neighbours:
                if neighbour[0].color == 'w':
                    stack.append(neighbour[0])
                    neighbour[0].color = 'g'
                    flag = True
            current.color = 'b' #black means it's over
        self.reset_colors()
        return False

    def fill_graph(self, num_nodes, num_edges = 0):
        if num_edges == 0:
            num_edges = 3*num_nodes
        difference = num_edges//num_nodes
        for i in range(num_nodes):
            node_name = str(i)
            self.add_node(node_name)
        for i in range(num_edges//difference):
            for j in range(difference):
                self.add_edge(self.nodes[i], self.nodes[random.randrange(len(self.nodes))], random.randrange(1000))

def kruskal(G):
    new_graph = Graph()
    temp_edges = sorted(G.edges)
    #for edge in temp_edges:
    #    print("Edge weight: " + str(edge.weight))
    #    print("Edge a " + str(edge.a.name) + ", edge b " + str(edge.b.name))
    #print()
    #while len(new_graph.nodes) < len(G.nodes):
    for nodes in G.nodes:
        new_graph.add_node(nodes.name)
    while len(new_graph.edges) < len(G.nodes) - 1:
        if len(temp_edges) == 0:
            print("No minimal spanning tree found")
            return
        temp_edge = temp_edges.pop(0)
        a = temp_edge.a
        b = temp_edge.b
        index_a = new_graph.find_in_graph(a.name)
        index_b = new_graph.find_in_graph(b.name)
        if new_graph.find_path(new_graph.nodes[index_a],new_graph.nodes[index_b]):
            continue
        new_graph.add_edge(new_graph.nodes[index_a], new_graph.nodes[index_b],temp_edge.weight)

    return new_graph

def kruskal_union_find(G):
    new_graph = Graph()
    temp_edges = sorted(G.edges)
    disjoint_set_nodes = list()
    for nodes in G.nodes:
        new_graph.add_node(nodes.name)
        temp_node = make_set(nodes.name)
        ds_nodes.append(temp_node)

    while len(new_graph.edges) < len(G.nodes) - 1:
        if len(temp_edges) == 0:
            print ("No minimal spanning tree found")
            return
        temp_edge = temp_edges.pop(0)
        
        a = temp_edge.a
        b = temp_edge.b
        index_a = new_graph.find_in_graph(a.name)
        index_b = new_graph.find_in_graph(b.name)
        if find(index_a) != find(index_b):
            union(index_a, index_b)
            new_graph.add_edge(new_graph.nodes[index_a], new_graph.nodes[index_b],temp_edge.weight)

    return new_graph

def times_kruskal():
    for i in graph_sizes:
        G = Graph()
        G.fill_graph(i)
        print("Graph |V|: " + str(i))
        start = time.time()
        reg_kruskal = kruskal(G)
        end = time.time()
        print("Regular kruskal: " + str(end-start))
        start = time.time()
        uf_kruskal = kruskal_union_find(G)
        end = time.time()
        print("Disjoint sets kruskal: " + str(end-start))
        
G = Graph() #graph from youtu.be/JZBQLXgSGfs
G.add_node('A') #0
G.add_node('B') #1
G.add_node('C') #2
G.add_node('D') #3
G.add_node('E') #4
G.add_node('F') #5
G.add_node('G') #6
G.add_node('H') #7
G.add_node('I') #8
G.add_node('J') #9
G.add_edge(G.nodes[0],G.nodes[1],5)
G.add_edge(G.nodes[0],G.nodes[3],4)
G.add_edge(G.nodes[0],G.nodes[4],1)
G.add_edge(G.nodes[1],G.nodes[2],4)
G.add_edge(G.nodes[1],G.nodes[3],2)
G.add_edge(G.nodes[2],G.nodes[7],4)
G.add_edge(G.nodes[2],G.nodes[8],1)
G.add_edge(G.nodes[2],G.nodes[9],2)
G.add_edge(G.nodes[3],G.nodes[4],2)
G.add_edge(G.nodes[3],G.nodes[5],5)
G.add_edge(G.nodes[3],G.nodes[6],11)
G.add_edge(G.nodes[3],G.nodes[7],2)
G.add_edge(G.nodes[4],G.nodes[5],1)
G.add_edge(G.nodes[5],G.nodes[6],7)
G.add_edge(G.nodes[6],G.nodes[7],1)
G.add_edge(G.nodes[6],G.nodes[8],4)
G.add_edge(G.nodes[7],G.nodes[8],6)
G.add_edge(G.nodes[8],G.nodes[9],0)    
#G.draw()
G_MST = kruskal(G)
print("Regular Kruskal")
G_MST.draw()

G_MST_UF = kruskal_union_find(G)
print("Kruskal using disjoint sets")
G_MST_UF.draw()

times_kruskal()
