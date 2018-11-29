#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <set>
#include <ctime>
#include <cstdlib>
#include <sstream>

using namespace std;

struct Node;
struct Edge;
struct edge_minor;

typedef pair<Node*, int> node_weigh; //node and it's weight
typedef list<node_weigh> node_list; //list of adjacent nodes
typedef vector<Node*> node_vec; //vector of nodes
typedef vector<Edge*> edge_vec; //vector of edges
typedef set<Edge*, edge_minor> edge_set; //set of edges
typedef vector<bool> bool_vec; //vector of booleans
typedef vector<int> int_vec; //vector of integers

node_vec temp;

string intToString(const int &z) {
	stringstream leString;
	leString << z;
	return leString.str();
}

struct Node{
	string name;
	char colour;
	node_list neighbours;
	int_vec weights;
	Node (string name){
		this->name = name;
		this->colour = 'w';
	}
	void add_neighbour(Node* a, int w){
		node_weigh temp;
		temp.first = a;
		temp.second = w;
		weights.push_back(w);
		neighbours.push_back(temp);
	}
	bool find_neighbour(Node* a){
		for (typename list<node_weigh>::iterator it = neighbours.begin(); it != neighbours.end(); ++it){ //neighbours
			if ((*it).first == a) return 1;
		}
		return 0;
	}
};

void print_nodevec(node_vec& t){
	for (int i = 0; i < t.size(); i++){
		cout << t[i]->name << ' ';
	}
	cout << endl;
}

bool find_in_path(Node* a, node_vec& path){
	for (int i = 0; i < path.size(); i++){
		if (path[i] == a) return 1;
	}
	return 0;
}

struct Edge{
	int weight;
	bool direction;
	Node* a, *b;
	Edge(Node* a, Node* b, int w, bool dir){
		this->a = a;
		this->b = b;
		this->weight = w;
		this->direction = dir;
	}
	/*bool operator<(Edge b){
		return weight < b.weight;
	}*/
};

bool edge_minor_w(Edge* a, Edge* b){
	return a->weight < b->weight;
}

struct edge_minor{
	bool operator()(Edge* e1, Edge* e2) { //different cases because
		if (e1->weight == e2->weight){ //<set> stores different values
			if (e1->a->name == e2->a->name)
				return e1->b->name < e2->b->name;
			else return e1->a->name < e2->a->name;
		}
		return e1->weight < e2->weight;
	}
};

class Graph{
public:
	node_vec nodes;
	Graph();
	void add_node(string a);
	void add_edge(Node* a, Node* b, int w = 1, bool dir = 0); //w is the weight, dir: 0 is no direction, 1 is A->B
	void draw();
	void fill_graph(int num_nodes, int num_edges = 0);
	void dfs(Node* v);
	void bfs(Node* v);
	friend bool find_path(Graph G, int k, Node* cur_node, node_vec& m_path);
	friend bool longest_path(Graph G, int k, node_vec& m_path = temp, int cur_node = -1);
	friend bool hamiltonian_cycle(Graph G, int cur_node = 0);
private:
	edge_vec edges;
	edge_set my_edges;
	stack<Node*> my_stack;
	queue<Node*> my_queue;
	void real_dfs();
	void real_bfs();
	int find_in_graph(string name);
	void reset_colours();
};

Graph::Graph(){
	node_vec nodes;
	this->nodes = nodes;
}

void Graph::add_node(string a){
	Node* t = new Node(a);
	nodes.push_back(t);
}

void Graph::add_edge(Node* a, Node* b, int w, bool dir){
	a->add_neighbour(b, w);
	if (! dir) b->add_neighbour(a, w);
	Edge* e = new Edge(a, b, w, dir);
	edges.push_back(e);
	my_edges.insert(e);
}

void Graph::fill_graph(int num_nodes, int num_edges){
	if (num_edges == 0) num_edges = 3 * num_nodes;
	int difference = num_edges / num_nodes;
	string node_name;
	for (int i = 0; i < num_nodes; i++){
		node_name = intToString(i);
		add_node(node_name);
	}
	srand(time(NULL));
	for (int i = 0; i < num_edges/difference; i++){
		for (int j = 0; j < difference; j++){
			add_edge(nodes[i], nodes[rand() % nodes.size()] );
		}
	}
}

void Graph::dfs(Node* v){
	while (! my_stack.empty() ){ //emptying stack
		my_stack.pop();
	}
	my_stack.push(v);
	v->colour = 'g';
	real_dfs();
	reset_colours();
}

void Graph::real_dfs( ){
	bool flag;
	Node* v;
	if (! my_stack.empty() ){
		flag = 0;
		v = my_stack.top();
		for (typename list<node_weigh>::iterator it = v->neighbours.begin(); it != v->neighbours.end(); 
				++it){ //we check v's neighbours
			if ( ((*it).first)->colour == 'w'){ //if the neighbour colour is white
				((*it).first)->colour = 'g'; //we colour it grey
				my_stack.push( (*it).first ); //we push the neighbour into the stack
				flag = 1; //we activate the flag
			}
		}
		if (! flag){
			v->colour = 'b';
			cout << v->name << ' ';
			my_stack.pop();
		}
		real_dfs();
	}
}

void Graph::bfs(Node* v){
	my_queue.push(v);
	v->colour = 'g';
	real_bfs();
	reset_colours();
}

void Graph::real_bfs( ){
	Node* v;
	if (! my_queue.empty() ){
		v = my_queue.front();
		my_queue.pop();
		v->colour = 'b';
		cout << v->name << ' ';
		for (typename list<node_weigh>::iterator it = v->neighbours.begin(); it != v->neighbours.end(); ++it){ //we check v's neighbours
			if ( ((*it).first)->colour == 'w'){ //if the neighbour colour is white
				((*it).first)->colour = 'g'; //we colour it grey
				my_queue.push( (*it).first ); //we push the neighbour into the stack
			}
		}
		real_bfs();
	}
}

int Graph::find_in_graph(string name){
	for(int i = 0; i < nodes.size(); i++){
		if (nodes[i]->name == name) return i;
	}
	return -1;
}


/**
  ************* LONGEST PATH **********
 **/

bool find_path(Graph G, int k, Node* cur_node, node_vec& m_path){
	if (m_path.size() - 1 >= k) return true;
	for (typename list<node_weigh>::iterator it = cur_node->neighbours.begin(); it != cur_node->neighbours.end(); ++it){ //we check neighbours
		if (find_in_path((*it).first, m_path)) continue;
		m_path.push_back((*it).first);
		if (find_path(G, k, (*it).first, m_path)) return true;
		m_path.erase(m_path.begin() + m_path.size() - 1);
	}
	return false;
	
}

bool longest_path(Graph G, int k, node_vec& m_path, int cur_node){
	temp.clear();
	int index;
	srand(time(NULL));
	if (cur_node == -1){
		index = rand() % (G.nodes.size());
	} else index = cur_node;
	m_path.push_back(G.nodes[index]);
	if (find_path(G, k, G.nodes[index], m_path) == 0) return 0;
	else {
		//print_nodevec(m_path); //comment once tested
		return 1;
	}
}


/**
 *************************** HAM PATH ******************
 **/

bool hamiltonian_cycle(Graph G, int cur_node){
	if (cur_node >= G.nodes.size()) return 0;
	node_vec path;
	Node* first, *last;
	if (longest_path(G, G.nodes.size() - 1, path, cur_node)){
		first = path[0];
		last = path[path.size() - 1];
		if (first->find_neighbour(last)){
			//print_nodevec(path); //comment once tested
			return 1;
		} else {
			return hamiltonian_cycle(G, cur_node+1);
		}
	} else {
		return hamiltonian_cycle(G, cur_node+1);
	}
}

/**
 *** REST OF CODE 
**/

void Graph::reset_colours(){
	for(int i = 0; i < nodes.size(); i++){
		nodes[i]->colour = 'w';
	}
}

void Graph::draw(){
	for (int i = 0; i < nodes.size(); i++){
		cout << nodes[i]->name << "->";
		for (typename list<node_weigh>::iterator it = nodes[i]->neighbours.begin(); it != nodes[i]->neighbours.end();
				++it){
			cout << ((*it).first)->name;
		}
		cout << endl;
	}
}

void times_to(int num){
	Graph G;
	G.fill_graph(num);
	cout << "Graph size: " << num << endl;
	for (int i = 0; i <= num; i+=1000){
		clock_t start = clock();
		longest_path(G, i);
		clock_t end = clock();
		cout << "Time with " << i << " elements on a Graph with " << num << " nodes: ";
		cout << double(end-start)/CLOCKS_PER_SEC << endl;
	}
}

int main(int argc, char *argv[]) {
	Graph G;
	G.add_node("A");
	G.add_node("B");
	G.add_node("C");
	G.add_node("D");
	G.add_node("E");
	G.add_edge(G.nodes[0], G.nodes[1]);
	G.add_edge(G.nodes[0], G.nodes[2]);
	G.add_edge(G.nodes[0], G.nodes[3]);
	G.add_edge(G.nodes[1], G.nodes[2]);
	G.add_edge(G.nodes[1], G.nodes[4]);
	G.add_edge(G.nodes[2], G.nodes[3]);
	G.add_edge(G.nodes[2], G.nodes[4]);
	/*times_to(20);
	times_to(30);
	times_to(40);
	times_to(50);*/
	times_to(10000);
	/*G.draw();
	cout << "Longest path k = 4: "; longest_path(G,4);
	cout << "Ham cycle: "; hamiltonian_cycle(G);*/
	return 0;
}

 
