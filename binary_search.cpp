#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> int_vec;

bool binary_search(int_vec a, int n, int start, int end){ //searchs for n in an ordered vector a
	if (start > end || end < start) return 0; //1
	int mid = (start + end) >> 1; //1
	if (a[mid] == n) return 1; //1
	if (a[mid] > n) return binary_search(a, n, start, mid-1); //1
	else return binary_search(a, n, mid+1, end); //1
	//T(n) = c + T(n/2)
}

void fill_vec(int_vec& a, int size){
	for (int i = 0; i < size; i++){
		a.push_back(i);
	}
}

int main(int argc, char *argv[]) {
	
	int_vec test;
	fill_vec(test, 1024);
	cout << binary_search(test, -2, 0, test.size() );
	
	return 0;
}

