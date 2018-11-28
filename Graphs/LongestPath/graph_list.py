import random
import time

class Node():
    def __init__(self, name):
        self.name = name
        self.neighbours = list()

    def add_neighbour(self, node):
        self.neighbours.append(node)

def print_nodelist(le_list):
    for node in le_list:
        print(node.name, end=" ")
    print()

class Edge():
    def __init__(self, a, b, dire, w):
        self.a = a
        self.b = b
        self.dire = dire
        self.weight = w

class Graph(): #Undirected Graph
    def __init__(self):
        self.nodes = list()
        self.edges = list()

    def add_node(self, name):
        temp_node = Node(name)
        self.nodes.append(temp_node)

    def add_edge(self, a, b, dire = 0, w = 1): #a and b are nodes, dire: 0 <->, 1->
        a.add_neighbour(b)
        if (dire == 0):
            b.add_neighbour(a)
        e = Edge(a,b, dire, w)
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
                print (neighbour.name, end = ' ')
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

###################### LONGEST PATH ###################

def find_path(G, k, cur_node, path): #G = (V,E)
    if (len(path) - 1 >= k): #we've found a simple path of the desired length
        return True
    for neighbour in cur_node.neighbours: #visitng A's neighbours
        if neighbour in path: #it's already on the path
            continue #we do nothing
        path.append(neighbour) #we add the neighbour to the path
        if (find_path(G, k, neighbour, path) == True): #We call find_path again 
            return True #until (if it does) it finds a simple path of
            #the desired length
        path.pop() #it wasn't meant to be, we put it out of the path
    return False #we couldn't find a path of the desired length
    
def longest_path(G, k, path = list(),cur_node=-1):
    if cur_node == -1:
        index = random.randrange(len(G.nodes))
    else:
        index = cur_node
    
    path.append(G.nodes[index])
    if find_path(G, k, G.nodes[index], path) == False:
        #print ("No")
        return False
    else:
        print_nodelist(path)
        return True


################## Ham path ##################

def hamiltonian_cycle(G,cur_node=0): #G = (V,E)
    if cur_node >= len(G.nodes): #current node exceeds the length of
        return False #nodes @ G
    path = list() #to store the path for future use
    if longest_path(G, len(G.nodes)-1, path,cur_node): #it found a
        #path of length |V| - 1
        first_node = path[0]
        last_node = path[len(path)-1]
        if last_node in first_node.neighbours:
            print("Ham path found.")
            return True #we've found a cycle
        else:
            return hamiltonian_cycle(G,cur_node+1) #we try starting with the
            #next node
    else:
        return False #it didn't find a path of length |V| - 1

def time_path(amount):
    """for k in range(5,amount+1,5):
        G = Graph()
        G.fill_graph(k*10)
        print ("Graph size: "+ str(k))
        for i in range(5,k,5):
            start = time.time()
            G.longest_path(i)
            end = time.time()
            print("time with " + str(i) + " elements: " + str(end-start))"""
    G = Graph()
    G.fill_graph(amount)
    print ("Graph size: "+ str(amount))
    for i in range(5, amount+1, 5):
        start = time.time()
        G.longest_path(i)
        end = time.time()
        print("time with " + str(i) + " elements, total " + str(amount) + ": " + str(end-start))

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
longest_path(G,5)
hamiltonian_cycle(G)

"""G2 = Graph()
G2.add_node('A')
G2.add_node('B')
G2.add_node('C')
G2.add_node('D')
G2.add_node('E')
G2.add_node('F')
G2.add_node('G')
G2.add_edge(G2.nodes[0], G2.nodes[2])
G2.add_edge(G2.nodes[0], G2.nodes[3])
G2.add_edge(G2.nodes[1], G2.nodes[2])
G2.add_edge(G2.nodes[1], G2.nodes[3])
G2.add_edge(G2.nodes[2], G2.nodes[3])
G2.add_edge(G2.nodes[2], G2.nodes[5])
G2.add_edge(G2.nodes[2], G2.nodes[6])
G2.add_edge(G2.nodes[3], G2.nodes[4])
G2.add_edge(G2.nodes[3], G2.nodes[6])
G2.draw()
longest_path(G2,5) """

#H = Graph()
#H.fill_graph(5000)
#H.draw()
#H.hamiltonian_cycle()

#time_path(10)
