#include <iostream>
#include <vector>
#include <stack>
#include <queue>

//adjacency matrix
using namespace std;

struct Node;

typedef std::vector<Node*> node_vec;

void print_matrix(int a, int b, int** c){ //test purposes
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			std::cout << c[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

struct Node{
	char name, colour;
	Node(const char& name){
		this->name = name;
		this->colour = 'w';
	}
};

class Graph{
public:
	int size; //amount of nodes
	int** nodes; //matrix
	node_vec nodes_names;
	Graph(const int& n); //n is the amount of nodes to be had
	void add_node(const char& a); //just to put a name to the node
	void add_edge(const int& pos_a, const int& pos_b, const bool& dir); //dir: 0 is no direction, 1 is A->B
	void delete_edge(const int& pos_a, const int& pos_b, const bool& dir);
	void dfs(const int& pos);
	void bfs(const int& pos);
	void draw(); //A->B means: A is connected to B
private:
	void real_dfs();
	void real_bfs();
	void reset_colours(); //resets colours in case dfs or bfs are to be used again
	int find_in_graph(Node*& a); //-1 if the node doesn't exist, else returns the position of the node
	stack<int> my_stack;
	queue<int> my_queue;
};

Graph::Graph(const int& n){
	nodes = new int*[n];
	for (int i = 0; i < n; i++){
		(nodes)[i] = new int[n]; //Sorry...
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			nodes[i][j] = 0;
		}
	}
	this->size = n;
}

int Graph::find_in_graph(Node*& a){
	int i;
	for (i = 0; i < nodes_names.size(); i++){
		if (a == nodes_names[i]) return i;
	}
	return -1;
}

void Graph::add_node(const char& a){
	Node* t = new Node(a);
	nodes_names.push_back(t);
}

void Graph::add_edge(const int& pos_a, const int& pos_b, const bool& dir){
	nodes[pos_a][pos_b] = 1;
	if (! dir) nodes[pos_b][pos_a] = 1;
}

void Graph::delete_edge(const int& pos_a, const int& pos_b, const bool& dir){
	nodes[pos_a][pos_b] = 0;
	if (! dir) nodes[pos_b][pos_a] = 0;
}

void Graph::dfs(const int& pos){ 
	my_stack.push(pos);
	nodes_names[pos]->colour = 'g';
	real_dfs();
	reset_colours();
}

void Graph::real_dfs(){
	bool flag;
	int pos;
	if (! my_stack.empty() ){
		flag = 0;
		pos = my_stack.top();
		for (int i = 0; i < this->size; i++){ //we check v's neighbours
			if (nodes[pos][i] == 0) continue;
			if ( nodes_names[i]->colour == 'w'){ //if the neighbour colour is white
				nodes_names[i]->colour = 'g'; //we colour it grey
				my_stack.push( i ); //we push the neighbour into the stack
				flag = 1; //we activate the flag
			}
		}
		if (! flag){
			nodes_names[pos]->colour = 'b';
			cout << nodes_names[pos]->name << ' '; //proof sake
			my_stack.pop();
		}
		real_dfs();
	}
}

void Graph::bfs(const int& pos){ 
	my_queue.push(pos);
	nodes_names[pos]->colour = 'b';
	real_bfs();
	reset_colours();
}

void Graph::real_bfs(){
	int pos;
	if (! my_queue.empty() ){
		pos = my_queue.front();
		my_queue.pop();
		nodes_names[pos]->colour = 'b';
		cout << nodes_names[pos]->name << ' '; //proof sake
		for (int i = 0; i < this->size; i++){ //we check v's neighbours
			if (nodes[pos][i] == 0) continue;
			if ( nodes_names[i]->colour == 'w'){ //if the neighbour colour is white
				nodes_names[i]->colour = 'g'; //we colour it grey
				my_queue.push( i ); //we push the neighbour into the stack
			}
		}
		real_bfs();
	}
}

void Graph::reset_colours(){ //if we want to do bfs or dfs again
	for (int i = 0; i < size; i++){
		nodes_names[i]->colour = 'w';
	}
}

void Graph::draw(){
	for (int i = 0; i < size; i++){
		cout << nodes_names[i]->name << "->";
		for (int pos = 0; pos < size; pos++){
			if (nodes[pos][i] != 0){
				cout << nodes_names[pos]->name;
			}
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	cout << "dfs\n";
	Graph A(6); //Graph used for DFS example at class 
	A.add_node('A');
	A.add_node('B');
	A.add_node('C');
	A.add_node('D');
	A.add_node('E');
	A.add_node('F');
	A.add_edge(0, 1, 0);
	A.add_edge(0, 2, 0);
	A.add_edge(1, 3, 0);
	A.add_edge(1, 4, 0);
	A.add_edge(2, 5, 0);
	A.add_edge(3, 4, 0);
	A.add_edge(4, 5, 0);
	A.draw();
	A.dfs(3);
	cout << endl;
	
	cout << "Bfs: " << endl;
	Graph B(8); //Tree used for BFS example at class
	B.add_node('H');
	B.add_node('G');
	B.add_node('F');
	B.add_node('E');
	B.add_node('D');
	B.add_node('C');
	B.add_node('B');
	B.add_node('A');
	B.add_edge(7, 6, 0);
	B.add_edge(7, 5, 0);
	B.add_edge(7, 4, 0);
	B.add_edge(6, 3, 0);
	B.add_edge(6, 2, 0);
	B.add_edge(5, 1, 0);
	B.add_edge(4, 0, 0);
	B.draw();
	B.bfs(7);
	return 0;
}
