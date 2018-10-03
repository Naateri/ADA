#include <iostream>
#include <list>
//not complete
using namespace std;

struct Node{
	int val;
	Node* nodes[2];
	Node* parent;
	bool colour; //0 = black, 1 = red
	Node(int x, Node* father){
		nodes[0] = nodes[1] = 0;
		val = x;
		colour = 1;
		parent = father;
	}
};

class RedBlack_Tree{
public:
	Node* root;
	RedBlack_Tree();
	bool find(int x, Node**& p, Node*& parent);
	bool insert(int x);
	bool remove(int x);
	void printTree(Node* p);
private:
	list < Node* > path;
	void recolor(Node* v);
	void right_rotate(Node* v);
	void left_rotate(Node* v);
};


RedBlack_Tree::RedBlack_Tree(){
	this->root = 0;
}

void RedBlack_Tree::right_rotate(Node* v){
	Node* father, *gfather, *temp, *bl, *gfather_father;
	list<Node*>::iterator it = path.end();
	while(v != *(it) ){
		it--;
	}
	gfather = v;
	gfather_father = gfather->parent;
	father = gfather->nodes[1];
	if ( (*it) != this->root ) {
		it--;
		temp = *(it);
	}
	bl = father->nodes[0];
	father->nodes[0] = gfather;
	gfather->parent = father;
	gfather->nodes[1] = bl;
	father->parent = gfather_father;
	if (root == gfather) {
		root = father;
		root->parent = 0;
	}
	else {
		if (father->val < temp->val ) temp->nodes[0] = father;
		else temp->nodes[1] = father;
		//father->parent = *(--it);
	}
}

void RedBlack_Tree::left_rotate(Node* v){
	Node* father, *gfather, *temp, *bl, *gfather_father;
	list<Node*>::iterator it = path.end();
	while(v != *(it) ){
		it--;
	}
	gfather = v;
	gfather_father = gfather->parent;
	father = gfather->nodes[0];
	if ( (*it) != this->root ) {
		it--;
		temp = *(it);
	}
	bl = father->nodes[0];
	father->nodes[1] = gfather;
	gfather->parent = father;
	gfather->nodes[0] = bl;
	father->parent = gfather_father;
	//temp = gfather_father;
	if (root == gfather) {
		root = father;
		root->parent = 0;
	}
	else {
		if (father->val < temp->val ) temp->nodes[0] = father;
		else temp->nodes[1] = father;
		//father->parent = *(--it);
	}
}


bool RedBlack_Tree::find(int x, Node**& p, Node*& parent){
	parent = *p;
	for (p = &root; *p && (*p)->val != x; p = &((*p)->nodes[(*p)->val < x]) ){
		path.push_back(*p);
		parent = *p;
	}
	//parent = *p;
	//cout << "find parent " << parent << endl;
	return !!*p;
}

bool RedBlack_Tree::insert(int x){
	Node** p, *parent;
	if (find(x,p, parent)) return 0;
	*p = new Node(x, parent);
	if (*p == root){
		(*p)->parent = 0;
		//(*p)->colour = 0;
	}
	path.push_back(*p);
	recolor(*p);
	root->colour = 0;
}

void RedBlack_Tree::recolor(Node* v){
	Node* p, *g_father, *uncle;
	bool gparent_son;
	if ( !(v->parent) ) return;
	p = v->parent;
	if ( !(p->parent) ) return;
	if (! p->colour) return; //0 -> black, 1 -> red
	g_father = p->parent;
	if (!g_father) return;
	/*if (g_father->nodes[1]) uncle = g_father->nodes[1]; //right son
	else return;*/
	if (!g_father->nodes[1] || g_father->nodes[1]->val != p->val){
		uncle = g_father->nodes[1];
		gparent_son = 1;
	} else {
		uncle = g_father->nodes[0];
		gparent_son = 0;
	}
	if (uncle && uncle->colour){
		p->colour = 0;
		uncle->colour = 0;
		g_father->colour = 1;
		recolor(g_father);
	} else /*if (! uncle->colour)*/{
		p->colour = 0;
		g_father->colour = 1;
		if (gparent_son) left_rotate(g_father);
		else right_rotate(g_father);
	}
}



void RedBlack_Tree::printTree(Node* p){
	if (!p) return;
	cout << "Valor: " << p->val << " color: ";
	if (p->colour) cout << "Rojo\n";
	else cout << "Negro\n";
	if (p->nodes[0]) cout << "Hijo izquierdo: " << p->nodes[0]->val << ' ';
	if (p->nodes[1]) cout << "Hijo derecho: " << p->nodes[1]->val << ' ';
	printTree(p->nodes[0]);
	printTree(p->nodes[1]);
}

int main(int argc, char *argv[]) {
	RedBlack_Tree A;
	A.insert(5);
	A.insert(4);
	A.insert(3);
	A.printTree(A.root);
	return 0;
}

