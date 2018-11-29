#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <string>

struct Node;

typedef std::pair<Node*, int> node_weigh;
typedef std::list<node_weigh> node_list;
typedef std::vector<Node*> node_vec;
typedef std::vector<node_vec> node_vec_of_vecs;
typedef std::vector<bool> bool_vec;
typedef std::string str;
typedef unsigned int uint;
typedef std::vector<uint> uint_vec;

struct Path{
	str path;
	uint length = 0;
	bool done = 0;
};

bool allNodesChecked(Path* p, uint size){
	for(uint i = 0; i < size; i++){
		if ( ! (p+i)->done ) return 0;
	}
	return 1;
}

bool findSameLetter(str a, str b){
	int shortest;
	if (a.size() > b.size()) shortest = b.size();
	else shortest = a.size();
	for(int i = 0; i < shortest; i++){
		if ( a[i] == b[i] ) return 1;
	}
	return 0;
}

uint findInVector(node_vec vec, Node* elem){
	uint i = 0;
	while(vec.at(i) != elem){
		i++;
	}
	return i;
}

struct Node{
	char name, status;
	bool visited;
	int start_time, end_time;
	node_list neighbours;
	uint_vec weights;
	bool_vec dirs;
	Node(char name){
		this->name = name;
		this->visited = 0;
		this->status = 'u'; //unvisited
	}
	void add_neighbour(Node* a, int w){
		node_weigh temp;
		temp.first = a;
		temp.second = w;
		weights.push_back(w);
		neighbours.push_back(temp);
	}
	//TO_FILL
};

class Graph{
public:
	node_vec nodes;
	node_vec reversed_topological_list;
	Graph();
	void add_node(char a);
	void add_edge(Node* a, Node* b, int w, bool dir); //w is weigh, on dir: 0 is no direction, 1 is A->B
	int dfs(Node* u, int cur_time);
	int dfs_tl(Node* u, int cur_time); //dfs topological list
	void bfs(Node* s);
	uint Dijkstra(Node* start, Node* goal); //DISCLAIMER: Este para nada es el mejor Dijkstra y tiene (al menos) 69*10^(69) mejoras posibles de hecho
private:
	uint findByValue(char val);
	void Dijks(Node* strt_pnt, Node*& node, Path* p);
	void setMinNode(Path* p, uint size, Node*& minNode);
};

Graph::Graph(){
	node_vec nodes;
	this->nodes = nodes;
}

void Graph::add_node(char a){
	Node* t = new Node(a);
	nodes.push_back(t);
}

void Graph::add_edge(Node* a, Node* b, int w, bool dir){
	a->add_neighbour(b, w);
	if (! dir) b->add_neighbour(a, w);
}

int Graph::dfs(Node* u, int cur_time){ //works
	u->start_time = cur_time;
	cur_time++;
	u->status = 'i'; //in progress, yellow
	for(node_list::iterator it = u->neighbours.begin(); it != u->neighbours.end(); it++){
		if ( ((*it).first)->status == 'u' ){ //unvisited, gray
			cur_time = dfs( ((*it).first), cur_time);
			cur_time++;
		}
	}
	u->end_time = cur_time;
	u->status = 'd'; //done, black
	return cur_time;
}

int Graph::dfs_tl(Node* u, int cur_time){
	u->start_time = cur_time;
	cur_time++;
	u->status = 'i'; //in progress, yellow
	for(node_list::iterator it = u->neighbours.begin(); it != u->neighbours.end(); it++){
		if ( ((*it).first)->status == 'u' ){ //unvisited, gray
			cur_time = dfs( ((*it).first), cur_time);
			cur_time++;
		}
	}
	u->end_time = cur_time;
	u->status = 'd'; //done, black
	reversed_topological_list.push_back(u);
	return cur_time;
}

void Graph::bfs(Node* s){ //Works
	node_vec_of_vecs L (nodes.size());
	node_vec temp;
	Node* tmp;
	temp.push_back(s);
	L.at(0) = temp;
	s->visited = 1;
	temp.clear();
	for (int i = 0; i < nodes.size() - 1; i++){
		for(int j = 0; j < L.at(i).size(); j++){
			tmp = L.at(i).at(j);
			for (node_list::iterator it = tmp->neighbours.begin(); it != tmp->neighbours.end(); it++){
				if ( ! (*it).first->visited ){ //visited is 0
					(*it).first->visited = 1;
					L.at(i+1).push_back( (*it).first );
				}
			}
		}
		std::cout << "size of L at " << i << " : " << L.at(i).size() << '\n'; //TEST PURPOSES
	}
}

void Graph::setMinNode(Path* p, uint size, Node*& minNode){
	uint min = -1;
	for(uint i = 0; i < size; i++){
		if (!(p+i)->length || (p+i)->done ) continue;
		if (min > (p+i)->length){
			min = (p+i)->length;
			minNode = nodes[i];
		}
	}
	p[findInVector(nodes, minNode)].done = 1;
}

uint Graph::findByValue(char val){
	uint i = 0;
	while(nodes.at(i)->name != val){
		i++;
	}
	return i;
}

void Graph::Dijks(Node* strt_pnt, Node*& node, Path* p){
	Path* ptr; //para saber si ya paso por ese nodo o no
	Node* minNode;
	str newpath;
	uint prevLen;
	int i = 0;
	if (allNodesChecked(p, nodes.size())) return;
	//cout << "Cur Node: " << node->m_data << endl;
	for(node_list::iterator it = node->neighbours.begin(); it != node->neighbours.end(); it++){
		//if (p[findInVector(nodes, (*it)->m_nodes[node == (*it)->m_nodes[0]])].done) continue;
		if (p[findInVector(nodes, (*it).first)].done) continue;
		//if ((*it)->m_dir){ //arista direccional
		//if ( (*it)->m_nodes[1] == node) continue;
		ptr = &p[findInVector(nodes, (*it).first)];
		newpath = p[findInVector(nodes, node)].path + (*it).first->name; //posible nuevo camino
		prevLen = p[findInVector(nodes, node)].length; 
		if (ptr->done) continue;
		//ptr->path = newpath;
		if ( !ptr->length || ptr->length > prevLen + node->weights.at(i)){ //si la nueva distancia
			//ptr->length = prevLen + (*it).first->m_data; //es menor
			ptr->length = prevLen + node->weights.at(i); //es menor
			ptr->path = newpath;
		}
		/*} else { //arista bidireccional 
		if (node == (*it)->m_nodes[0]){ //el nodo esta en la primera pos de la arista
		ptr = &p[findInVector(m_nodes, (*it)->m_nodes[1])]; //nos lleva a la segunda
		newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[1]->m_data;
		//cout << "Connected to: " << (*it)->m_nodes[1]->m_data << endl;
		} else {
		ptr = &p[findInVector(m_nodes, (*it)->m_nodes[0])];
		newpath = p[findInVector(m_nodes, node)].path + (*it)->m_nodes[0]->m_data;
		//cout << "Connected to: " << (*it)->m_nodes[0]->m_data << endl;
		}
		prevLen = p[findInVector(m_nodes, node)].length; 
		if (ptr->done) continue;
		if ( !ptr->length || ptr->length > prevLen + (*it)->m_data){ //si la nueva distancia
		ptr->length = prevLen + (*it)->m_data; //es menor a la ya guardada
		ptr->path = newpath;
		}
		//}*/
		i++;
	}
	setMinNode(p, nodes.size(), minNode);
	if (node == minNode){
		minNode = strt_pnt;
		Dijks(strt_pnt, minNode, p);
	}
	node = minNode;
	return;
}

uint Graph::Dijkstra(Node* start, Node* goal){
	Path* paths = new Path[nodes.size()];
	Node* copy = start;
	paths[findInVector(nodes, start)].done = 1; //ya "paso" por el nodo de inicio
	paths[findInVector(nodes, start)].path = start->name; //y el camino es el mismo nodo
	for(uint i = 0; i < nodes.size(); i++){
		Dijks(copy, start, paths);
		if (start == goal) break;
	}
	uint res = paths[findInVector(nodes, goal)].length;
	std::cout << "Camino: " << paths[findInVector(nodes, goal)].path << std::endl;
	delete[] paths;
	return res;
}


int main(int argc, char *argv[]) {
	/*Graph Test; //graph found at slides
	Test.add_node('A');
	Test.add_node('B');
	Test.add_node('C');
	Test.add_node('D');
	Test.add_node('E');
	Test.add_node('F');
	Test.add_node('G');
	Test.add_node('H');
	Test.add_edge(Test.nodes[0], Test.nodes[1], 1, 0);
	Test.add_edge(Test.nodes[0], Test.nodes[6], 1, 0);
	Test.add_edge(Test.nodes[0], Test.nodes[7], 1, 0);
	Test.add_edge(Test.nodes[1], Test.nodes[2], 1, 0);
	Test.add_edge(Test.nodes[1], Test.nodes[4], 1, 0);
	Test.add_edge(Test.nodes[1], Test.nodes[5], 1, 0);
	Test.add_edge(Test.nodes[2], Test.nodes[3], 1, 0);
	Test.add_edge(Test.nodes[3], Test.nodes[4], 1, 0);
	Test.add_edge(Test.nodes[3], Test.nodes[5], 1, 0);
	Test.add_edge(Test.nodes[5], Test.nodes[6], 1, 0);
	std::cout << Test.dfs(Test.nodes[0], 0) << '\n';
	Test.bfs(Test.nodes[0]);
	std::cout << Test.Dijkstra(Test.nodes[6], Test.nodes[3]) << '\n'; */
	Graph Barbachan;
	Barbachan.add_node('A'); //nodo 0
	Barbachan.add_node('B'); //nodo 1
	Barbachan.add_node('C'); //nodo 2
	Barbachan.add_node('D'); //.....
	Barbachan.add_node('E');
	Barbachan.add_node('F'); //nodo 4
	///aristas
	///add_edge(nodoa, nodob, peso, 0 si es para ambas direcciones)
	Barbachan.add_edge(Barbachan.nodes[0], Barbachan.nodes[1], 110, 0);
	Barbachan.add_edge(Barbachan.nodes[0], Barbachan.nodes[4], 110, 0);
	Barbachan.add_edge(Barbachan.nodes[1], Barbachan.nodes[2], 80, 0);
	Barbachan.add_edge(Barbachan.nodes[1], Barbachan.nodes[2], 80, 0);
	Barbachan.add_edge(Barbachan.nodes[2], Barbachan.nodes[3], 200, 0);
	Barbachan.add_edge(Barbachan.nodes[3], Barbachan.nodes[4], 90, 0);
	Barbachan.add_edge(Barbachan.nodes[4], Barbachan.nodes[5], 50, 0);
	std::cout << Barbachan.Dijkstra(Barbachan.nodes[3], Barbachan.nodes[2]) << std::endl;
	std::cout << Barbachan.Dijkstra(Barbachan.nodes[3], Barbachan.nodes[1]) << std::endl;
	std::cout << Barbachan.Dijkstra(Barbachan.nodes[3], Barbachan.nodes[5]) << std::endl;
	
	std::cout << Barbachan.Dijkstra(Barbachan.nodes[4], Barbachan.nodes[2]) << std::endl;
	std::cout << Barbachan.Dijkstra(Barbachan.nodes[4], Barbachan.nodes[5]) << std::endl;
	return 0;
}
