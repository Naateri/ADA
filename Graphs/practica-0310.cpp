#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>

using namespace std;

struct Node;

typedef list<Node*> node_list; //list of adjacent nodes and graph nodes
typedef vector<Node*> node_vec; //vector of nodes

struct Node{ //nodes without weight (enough for dfs and bfs)
	char name, colour;
	node_list neighbours;
	Node (const char& name){
		this->name = name;
		this->colour = 'w';
	}
	~Node(){
		neighbours.clear();
	}
	void add_neighbour(Node*& a){ 
		neighbours.push_back(a);
	}
};

class Graph{
public:
	node_vec nodes;
	Graph();
	void add_node(const char& a);
	void add_edge(Node*& a, Node*& b, const bool& dir); //dir: 0 is no direction, 1 is A->B
	void delete_edge(Node*& a, Node*& b, const bool& dir);
	void delete_node(const char& a);
	void draw(); //A->B means: A is connected to B
	void dfs(Node*& v);
	void bfs(Node*& v);
private:
	stack<Node*> my_stack;
	queue<Node*> my_queue;
	void real_dfs();
	void real_bfs();
	int find_in_graph(const char& name); //returns -1 if it doesn't exist, else returns the position
	void reset_colours();
};

Graph::Graph(){
	node_vec nodes;
	this->nodes = nodes;
}

void Graph::add_node(const char& a){
	Node* t = new Node(a);
	nodes.push_back(t);
}

void Graph::add_edge(Node*& a, Node*& b, const bool& dir){
	a->add_neighbour(b);
	if (! dir) b->add_neighbour(a);
}

void Graph::delete_edge(Node*& a, Node*& b, const bool& dir){
	for (node_list::iterator it = a->neighbours.begin(); it != a->neighbours.end(); it++){
		if ( (*it) == b){
			a->neighbours.erase(it); //deleting the edge from a's list
		}
	}
	if (!dir){
		for (node_list::iterator it = b->neighbours.begin(); it != b->neighbours.end(); it++){
			if ( (*it) == a){
				b->neighbours.erase(it); //deleting the edge from b's list
			}	//undirectioned edge
		}
	}
}

void Graph::delete_node(const char& a){
	Node* temp = nodes[find_in_graph(a)];
	nodes.erase(nodes.begin() + find_in_graph(a) ); //deleting the node from the vector
	delete temp; //clearing memory
}

void Graph::dfs(Node*& v){
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
		for (typename node_list::iterator it = v->neighbours.begin(); it != v->neighbours.end(); ++it){ //we check v's neighbours
			if ( (*it)->colour == 'w'){ //if the neighbour colour is white
				(*it)->colour = 'g'; //we colour it grey
				my_stack.push( (*it) ); //we push the neighbour into the stack
				flag = 1; //we activate the flag
			}
		}
		if (! flag){
			v->colour = 'b';
			cout << v->name << ' '; //proof sake
			my_stack.pop();
		}
		real_dfs();
	}
}

void Graph::bfs(Node*& v){
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
		cout << v->name << ' '; //proof sake
		for (typename node_list::iterator it = v->neighbours.begin(); it != v->neighbours.end(); ++it){ //we check v's neighbours
			if ( (*it)->colour == 'w'){ //if the neighbour colour is white
				(*it)->colour = 'g'; //we colour it grey
				my_queue.push( (*it) ); //we push the neighbour into the stack
			}
		}
		real_bfs();
	}
}

int Graph::find_in_graph(const char& name){
	for(int i = 0; i < nodes.size(); i++){
		if (nodes[i]->name == name) return i;
	}
	return -1;
}

void Graph::reset_colours(){ //if we want to call dfs or bfs again
	for(int i = 0; i < nodes.size(); i++){
		nodes[i]->colour = 'w';
	}
}

void Graph::draw(){
	for (int i = 0; i < nodes.size(); i++){
		cout << nodes[i]->name << "->";
		for (typename node_list::iterator it = nodes[i]->neighbours.begin(); it != nodes[i]->neighbours.end();
		++it){
			cout << (*it)->name;
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	cout << "dfs\n";
	Graph A; //Graph used for DFS example at class 
	A.add_node('A');
	A.add_node('B');
	A.add_node('C');
	A.add_node('D');
	A.add_node('E');
	A.add_node('F');
	A.add_edge(A.nodes[0], A.nodes[1], 0);
	A.add_edge(A.nodes[0], A.nodes[2], 0);
	A.add_edge(A.nodes[1], A.nodes[3], 0);
	A.add_edge(A.nodes[1], A.nodes[4], 0);
	A.add_edge(A.nodes[2], A.nodes[5], 0);
	A.add_edge(A.nodes[3], A.nodes[4], 0);
	A.add_edge(A.nodes[4], A.nodes[5], 0);
	A.draw();
	A.dfs(A.nodes[3]);
	cout << endl;
	
	cout << "Bfs: " << endl;
	Graph B; //Tree used for BFS example at class
	B.add_node('H');
	B.add_node('G');
	B.add_node('F');
	B.add_node('E');
	B.add_node('D');
	B.add_node('C');
	B.add_node('B');
	B.add_node('A');
	B.add_edge(B.nodes[7], B.nodes[6], 0);
	B.add_edge(B.nodes[7], B.nodes[5], 0);
	B.add_edge(B.nodes[7], B.nodes[4], 0);
	B.add_edge(B.nodes[6], B.nodes[3], 0);
	B.add_edge(B.nodes[6], B.nodes[2], 0);
	B.add_edge(B.nodes[5], B.nodes[1], 0);
	B.add_edge(B.nodes[4], B.nodes[0], 0);
	B.draw();
	B.bfs(B.nodes[7]);
	return 0;
}

