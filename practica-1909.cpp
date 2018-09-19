#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define MAXI 1000000

using namespace std;

typedef vector<int> int_vec;

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

void insert_sort(int_vec& A){
	int temp, j;
	for (int i = 1; i < A.size(); i++){
		temp = A.at(i);
		j = i-1;
		while ( j >= 0 && A.at(j) > temp ){
			//swap( A.at(j+1), A.at(j) );
			A.at(j+1) = A.at(j);
			j--;
		}
		A.at(j+1) = temp;
	}
}

/*int_vec merge(int_vec A, int start, int mid, int end){
	int_vec res;
	int a_temp = A.at(start), b_temp = A.at(mid);
		
}*/

int_vec merge(int_vec A, int_vec B){
	int_vec result;
	while (!A.empty() && !B.empty()){
		if (A.front() < B.front()){
			result.push_back(A.front());
			A.erase(A.begin());
		} else {
			result.push_back(B.front());
			B.erase(B.begin());
		}
	}
	std::copy(std::begin(A), std::end(A), std::back_inserter(result));
	std::copy(std::begin(B), std::end(B), std::back_inserter(result));
	return result;
}

/*int_vec mergesort(int_vec A, int start, int end){
	int_vec res;
	if (start < end){
		int mid = (start+end)>>1;
		mergesort(A, start, mid);
		mergesort(A, mid+1, end);
		merge(A, start, mid, end);
	}
	
}*/

int_vec mergesort(int_vec A){
	int_vec left, right, result;
	if (A.size() <= 1){
		return A;
	}
	int mid = (A.size())>>1;
	copy(begin(A), begin(A) + mid, back_inserter(left) );
	copy(begin(A) + mid, end(A), back_inserter(right) );
	result = merge(mergesort(left), mergesort(right));
	return result;
}

int_vec mergesort_k(int_vec A, int k){
	int_vec left, right, result;
	if (A.size() <= k){
		insert_sort(A);
		return A;
	}
	int mid = (A.size())>>1;
	copy(begin(A), begin(A) + mid, back_inserter(left) );
	copy(begin(A) + mid, end(A), back_inserter(right) );
	result = merge(mergesort(left), mergesort(right));
	return result;
}


/*void mergesort_k(int_vec& A, int start, int end, int k){
	if (start < end || (end-start) >= k){
		int mid = (start+end)>>1;
		mergesort(A, start, mid);
		mergesort(A, mid+1, end);
		merge(A, start, mid, end);
	}
}*/

int main(int argc, char *argv[]) {
	
	int_vec A;
	fill_vec(A, 128, 500);
	print_vec(A);
	//insert_sort(A);
	//A = mergesort(A);
	//cout << A.size() << endl;
	A = mergesort_k(A, 8);
	print_vec(A);
	
	return 0;
}

