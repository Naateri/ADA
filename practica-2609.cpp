#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define MAXI 1000000

using namespace std;

typedef vector<int> int_vec;

//helpful functions

void fill_vec(int_vec& A, int size, int max = MAXI){
	srand( time(NULL) );
	for (int i = 0; i < size; i++){
		A.push_back( rand() % max );
	}
}

void print_vec(int_vec A){
	for (int i = 0; i < A.size(); i++){
		cout << A.at(i) << ' ';
	}
	cout << endl;
}

void swap(int& a, int& b){
	int temp = a;
	a = b;
	b = temp;
}

//heap sort
//sons: 2*pos + 1, 2*pos+2
//father: (pos-1)>>1
//limited by size

void heapify(int_vec& A, int pos, int size){
	int left, right, max;
	left = 2*pos + 1; ///O(1)
	right = 2*pos + 2; ///O(1)
	if (left >= size || right >= size) return; ///O(1)
	heapify(A, left, size); ///T(n/2)
	heapify(A, right, size); ///T(n/2)
	if ( A.at(left) > A.at(right) ) max = left; ///O(1)
	else max = right; 
	if ( A.at(max) > A.at(pos) ){ ///O(1)
		swap(A.at(pos), A.at(max) ); ///O(1)
	}
}

void heap_sort(int_vec& A){
	int size = A.size();
	for (int i = size - 1; i > 0; i--){ ///O(n)
		heapify(A, 0, size--); ///O(n) * O(n) = O(n^2)
		swap( A.at(i), A.at(0) ); ///O(1) * O(n) = O(n)
	}
	if ( A.at(0) > A.at(1) ) swap (A.at(0), A.at(1)); ///O(1) + O(1) = O(1)
}


int main(int argc, char *argv[]) {
	int_vec test;
	char ans;
	cout << "Se ordenará un arreglo de 1k (1000) elementos\n";
	fill_vec(test, 1000, 5000);
	cout << "Desea ver el arreglo desordenado? (y/n)\n";
	cin >> ans;
	if (ans == 'y') print_vec(test);
	heap_sort(test);
	cout << "Arreglo ordenado. (Presione cualquier tecla y luego enter para verlo)\n";
	cin >> ans;
	print_vec(test);
	return 0;
}

