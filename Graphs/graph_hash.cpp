#include <iostream>
#include <vector>
#include <string>
#include <utility>

#define huge_value 150000000

typedef std::vector<int> int_vec;
typedef std::vector<char> char_vec;
typedef std::pair<int, int> edge_weight; //first: neighbour, second: weight
typedef std::vector<edge_weight> edge_vec; //vector of edges
typedef std::string str;

void print_matrix(const int& a, const int& b, int** c){ //test purposes
	for (int i = 0; i < a; i++){
		for (int j = 0; j < b; j++){
			std::cout << c[i][j] << ' ';
		}
		std::cout << '\n';
	}
}

struct Path{
	str path;
	int length = 0;
	bool done = 0;
};

class H_Graph{
private:
	int V, E, cur_edge, cur_node;
	int_vec where_to;
	edge_vec edges;
	char_vec nodes;
	bool all_nodes_checked(Path* p);
	void getMinNode(Path* p, int& min_node);
	void Dijks(const int& start_point, int& node, Path* p);
public:
	H_Graph(const int& v, const int& E);
	void add_node(const char& name, const int& num_edges);
	void add_edge(const int& a, const int& b, const int& w); //goes from a to b, has weight w
	void draw();
	void matrix_draw();
	int Dijkstra(int start, const int& goal);
};

H_Graph::H_Graph(const int& v, const int& E){
	this->V = v;
	this->E = E;
	edges.resize(this->E, std::make_pair(0,0) );
	where_to.resize(this->V + 1, 0);
	nodes.resize(V, 0);
	cur_edge = cur_node = 0;
	where_to.at(0) = 0;
}

void H_Graph::add_node(const char& name, const int& num_edges){
	nodes.at(cur_node) = name;
	if (cur_node) where_to.at(cur_node+1) = num_edges + where_to.at(cur_node);
	else where_to.at(cur_node+1) = num_edges;
	cur_node++;
	//if (cur_node == this->V - 1) where_to.at(cur_node) = V;
}

void H_Graph::add_edge(const int& a, const int& b, const int& w){
	edges.at(cur_edge++) = std::make_pair(b, w);
}

bool H_Graph::all_nodes_checked(Path* p){
	for (int i = 0; i < V; i++){
		if (! p[i].done) return 0; //there's at least one node that hasn't been checked
	}
	return 1;
}

void H_Graph::getMinNode(Path* p, int& min_node){ //gets min weight from available nodes
	int min = huge_value;
	for(int i = 0; i < V; i++){
		if (!(p+i)->length || (p+i)->done ) continue;
		if (min > (p+i)->length){
			min = (p+i)->length;
			min_node = i;
		}
	}
	p[min_node].done = 1;
}

void H_Graph::Dijks(const int& start_point, int& node, Path* p){
	if ( all_nodes_checked(p) ) return;
	int i = 0, prevLen, minNode;
	Path* ptr; //to check if it's already gone through that node or not
	str newPath;
	for(int j = this->where_to.at(node); j < this->where_to.at(node+1); j++){
		if (p[this->edges.at(j).first].done) continue; //been there, done that...
		ptr = &p[this->edges.at(j).first];
		newPath = p[node].path + this->nodes.at(this->edges.at(j).first); //possible new Path
		prevLen = p[node].length; //storing previous length
		if (ptr->done) continue;
		if ( !ptr->length || ptr->length > prevLen + this->edges.at(j).second ){ //if new length is shorter
			ptr->length = prevLen + this->edges.at(j).second ; //we update distance
			ptr->path = newPath; //and the path
		}
	}
	getMinNode(p, minNode); //current node with the minimum distance
	/*if (node == minNode){ 
		minNode = start_point;
		Dijks(start_point, minNode, p);
	}*/
	node = minNode; //next Dijkstra will be called here
	return;
}

int H_Graph::Dijkstra(int start, const int& goal){
	Path* paths = new Path[V];
	int copy = start;
	paths[start].done = 1; //ya "paso" por el nodo de inicio
	paths[start].path = nodes.at(start); //camino: el mismo nodo
	for (int i = 0; i < V; i++){ //Dijkstra to each node
		Dijks(copy, start, paths);
		if (start == goal) break; //we found the distance to the point we wanted
		//if we want to calculate all distances, we just comment that line
	}
	int res = paths[goal].length;
	if ( !paths[goal].path.empty() )  std::cout << "Camino: " << paths[goal].path << std::endl;
	else{
		std::cout << "No hay camino del nodo " << nodes.at(start) << " al nodo " << nodes.at(goal) << "\n";
		delete[] paths;
		return -1;
	}
	delete[] paths;
	return res;
}

void H_Graph::draw(){
	for (int i = 0; i < this->nodes.size(); i++){
		std::cout << this->nodes.at(i) << "->";
		for (int j = this->where_to.at(i); j < this->where_to.at(i+1); j++){
			std::cout << this->nodes.at(this->edges.at(j).first);
		}
		std::cout << std::endl;
	}
}

void H_Graph::matrix_draw(){
	int** mat = new int*[V];
	int k;
	for (int i = 0; i < V; i++){
		mat[i] = new int[V];
	}
	for (int i = 0; i < V; i++){
		for (int j = 0; j < V; j++) {
			mat[i][j] = 0;
		}
	}
	for (int i = 0; i < this->nodes.size(); i++){
		//k = 0;
		for (int j = this->where_to.at(i); j < this->where_to.at(i+1); j++){
			/*while (k != this->edges.at(j).first){
				mat[i][k++] = 0;
			}*/
			mat[i][this->edges.at(j).first] = this->edges.at(j).second;
		}
	}
	print_matrix(V, V, mat);
	for (int i = 0; i < V; i++){
		delete[] mat[i];
	}
	delete[] mat;
}


int main(int argc, char *argv[]) {
	/*H_Graph Test(7, 18);
	Test.add_node('A', 2);
	Test.add_node('B', 2);
	Test.add_node('C', 2);
	Test.add_node('D', 4);
	Test.add_node('E', 2);
	Test.add_node('F', 4);
	Test.add_node('G', 2);
	Test.add_edge(0, 3, 8);
	Test.add_edge(0, 5, 5);
	Test.add_edge(1, 2, 2);
	Test.add_edge(1, 5, 10);
	Test.add_edge(2, 1, 2);
	Test.add_edge(2, 3, 12);
	Test.add_edge(3, 0, 8);
	Test.add_edge(3, 2, 12);
	Test.add_edge(3, 4, 5);
	Test.add_edge(3, 6, 3);
	Test.add_edge(4, 3, 5);
	Test.add_edge(4, 5, 3);
	Test.add_edge(5, 0, 5);
	Test.add_edge(5, 1, 10);
	Test.add_edge(5, 4, 3);
	Test.add_edge(5, 6, 7);
	Test.add_edge(6, 3, 3);
	Test.add_edge(6, 5, 7);
	Test.draw();
	Test.matrix_draw();
	std::cout << "Distance: " << Test.Dijkstra(3, 1) << std::endl;*/
	H_Graph Test1(11, 25);
	Test1.add_node('A', 2);
	Test1.add_node('B', 3);
	Test1.add_node('C', 1);
	Test1.add_node('D', 2);
	Test1.add_node('E', 1);
	Test1.add_node('F', 3);
	Test1.add_node('G', 3);
	Test1.add_node('H', 2);
	Test1.add_node('I', 3);
	Test1.add_node('J', 4);
	Test1.add_node('K', 1);
	Test1.add_edge(0, 3, 6);
	Test1.add_edge(0, 6, 8);
	Test1.add_edge(1, 0, 5);
	Test1.add_edge(1, 2, 10);
	Test1.add_edge(1, 7, 11);
	Test1.add_edge(2, 5, 6);
	Test1.add_edge(3, 1, 15);
	Test1.add_edge(3, 4, 18);
	Test1.add_edge(4, 8, 20);
	Test1.add_edge(5, 4, 16);
	Test1.add_edge(5, 8, 14);
	Test1.add_edge(5, 9, 7);
	Test1.add_edge(6, 0, 8);
	Test1.add_edge(6, 1, 1);
	Test1.add_edge(6, 7, 4);
	Test1.add_edge(7, 5, 2);
	Test1.add_edge(7, 6, 4);
	Test1.add_edge(8, 4, 20);
	Test1.add_edge(8, 5, 14);
	Test1.add_edge(8, 9, 25);
	Test1.add_edge(9, 5, 7);
	Test1.add_edge(9, 6, 8);
	Test1.add_edge(9, 7, 3);
	Test1.add_edge(9, 8, 25);
	Test1.add_edge(10, 9, 14);
	Test1.draw();
	std::cout << "Distance: " << Test1.Dijkstra(3, 9) << '\n';
	std::cout << "Distance: " << Test1.Dijkstra(0, 10);
	return 0;
}

