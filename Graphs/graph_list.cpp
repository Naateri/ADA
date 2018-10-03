#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <queue>
#include <stack>
#include <string>
#include <algorithm>
#include <set>

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

struct Node{
	char name, colour;
	node_list neighbours;
	int_vec weights;
	Node (char name){
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
};

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
	void add_node(char a);
	void add_edge(Node* a, Node* b, int w, bool dir); //w is the weight, dir: 0 is no direction, 1 is A->B
	void draw();
	void dfs(Node* v);
	void bfs(Node* v);
	friend Graph kruskal(Graph K, Node* v);
private:
	edge_vec edges;
	edge_set my_edges;
	stack<Node*> my_stack;
	queue<Node*> my_queue;
	void real_dfs();
	void real_bfs();
	bool path(Node* v1, Node* v2);
	int find_in_graph(char name);
	void reset_colours();
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
	Edge* e = new Edge(a, b, w, dir);
	edges.push_back(e);
	my_edges.insert(e);
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

int Graph::find_in_graph(char name){
	for(int i = 0; i < nodes.size(); i++){
		if (nodes[i]->name == name) return i;
	}
	return -1;
}

Graph kruskal(Graph K, Node* v){
	Graph res;
	int findA, findB;
	//sort(K.edges.begin(), K.edges.end(), edge_minor_w); //sorting edges by weight
	//for(int i = 0; i < K.edges.size(); i++){
	/*for (typename edge_set::iterator it = K.my_edges.begin(); it != K.my_edges.end(); it++){ //checking that it's ordered
		cout << "1: " << (*it)->a->name << " 2: " << (*it)->b->name << " peso: " << (*it)->weight << endl;		
	}*/
	for (typename edge_set::iterator it = K.my_edges.begin(); it != K.my_edges.end(); it++){
		findA = res.find_in_graph((*it)->a->name);
		findB = res.find_in_graph((*it)->b->name);
		if (findA == -1) {
			res.add_node((*it)->a->name); //not in the graph
			findA = res.find_in_graph((*it)->a->name); //updating position
		}
		if (findB == -1) {
			res.add_node((*it)->b->name); //not in the graph
			findB = res.find_in_graph((*it)->b->name); //updating position
		}
		if (! res.path(res.nodes[findA], res.nodes[findB])){ //we fill the edge
			/*res.add_edge(res.nodes[res.find_in_graph(K.edges[i]->a->name)], res.nodes[res.find_in_graph(K.edges[i]->b->name)], 
						 K.edges[i]->weight, K.edges[i]->direction);*/
			res.add_edge(res.nodes[findA], res.nodes[findB], 
						 (*it)->weight, (*it)->direction);
		}
		if (res.nodes.size() == K.nodes.size() ) return res; //all the nodes are in
	}
	
	return res;
}

bool Graph::path(Node* v1, Node* v2){
	while (! my_stack.empty() ){ //emptying stack
		my_stack.pop();
	}
	reset_colours();
	my_stack.push(v1);
	v1->colour = 'g';
	bool flag;
	Node* v;
	while (! my_stack.empty() ){
		flag = 0;
		v = my_stack.top();
		for (typename list<node_weigh>::iterator it = v->neighbours.begin(); it != v->neighbours.end(); ++it){ //we check v's neighbours
			if ( ((*it).first)->colour == 'w'){ //if the neighbour colour is white
				((*it).first)->colour = 'g'; //we colour it grey
				my_stack.push( (*it).first ); //we push the neighbour into the stack
				if ( (*it).first == v2) return 1;
				flag = 1; //we activate the flag
			}
		}
		if (! flag){
			v->colour = 'b';
			my_stack.pop();
		}
	}
	return 0;
}

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

int main(int argc, char *argv[]) {
	Graph A; //Graph used for DFS example at class 
	/*A.add_node('A');
	A.add_node('B');
	A.add_node('C');
	A.add_node('D');
	A.add_node('E');
	A.add_node('F');
	A.add_edge(A.nodes[0], A.nodes[1], 1, 0);
	A.add_edge(A.nodes[0], A.nodes[2], 1, 0);
	A.add_edge(A.nodes[1], A.nodes[3], 1, 0);
	A.add_edge(A.nodes[1], A.nodes[4], 1, 0);
	A.add_edge(A.nodes[2], A.nodes[5], 1, 0);
	A.add_edge(A.nodes[3], A.nodes[4], 1, 0);
	A.add_edge(A.nodes[4], A.nodes[5], 1, 0);
	A.draw();
	A.dfs(A.nodes[3]);*/
	/*Graph B; //Tree used for BFS example at class
	B.add_node('H');
	B.add_node('G');
	B.add_node('F');
	B.add_node('E');
	B.add_node('D');
	B.add_node('C');
	B.add_node('B');
	B.add_node('A');
	B.add_edge(B.nodes[7], B.nodes[6], 1, 0);
	B.add_edge(B.nodes[7], B.nodes[5], 1, 0);
	B.add_edge(B.nodes[7], B.nodes[4], 1, 0);
	B.add_edge(B.nodes[6], B.nodes[3], 1, 0);
	B.add_edge(B.nodes[6], B.nodes[2], 1, 0);
	B.add_edge(B.nodes[5], B.nodes[1], 1, 0);
	B.add_edge(B.nodes[4], B.nodes[0], 1, 0);
	B.draw();
	B.bfs(B.nodes[7]);*/
	Graph K, Krusk; //K: example for Kruskal algorithm used at class
	K.add_node('A');
	K.add_node('B');
	K.add_node('C');
	K.add_node('D');
	K.add_node('E');
	K.add_node('F');
	K.add_edge(K.nodes[0], K.nodes[1], 2, 0);
	K.add_edge(K.nodes[0], K.nodes[2], 1, 0);
	K.add_edge(K.nodes[1], K.nodes[2], 1, 0);
	K.add_edge(K.nodes[1], K.nodes[4], 3, 0);
	K.add_edge(K.nodes[1], K.nodes[5], 1, 0);
	K.add_edge(K.nodes[2], K.nodes[3], 3, 0);
	K.add_edge(K.nodes[2], K.nodes[4], 2, 0);
	K.add_edge(K.nodes[3], K.nodes[4], 3, 0);
	K.add_edge(K.nodes[4], K.nodes[5], 4, 0);
	//K.draw();
	Krusk = kruskal(K, K.nodes[0]);
	Krusk.draw();
	return 0;
}

 
