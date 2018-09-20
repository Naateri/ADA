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

//Sorts

void insert_sort(int_vec& A){
	int temp, j;
	for (int i = 1; i < A.size(); i++){
		temp = A.at(i);
		j = i-1;
		while ( j >= 0 && A.at(j) > temp ){
			A.at(j+1) = A.at(j);
			j--;
		}
		A.at(j+1) = temp;
	}
}

//Regular mergesort

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

int_vec mergesort(int_vec A){
	int_vec left, right, result;
	if (A.size() <= 1){
		return A;
	}
	int mid = (A.size())>>1;
	copy(A.begin(), A.begin() + mid, back_inserter(left) );
	copy(A.begin() + mid, A.end(), back_inserter(right) );
	result = merge(mergesort(left), mergesort(right));
	return result;
}

//mergesort where <=k elements get sorted with insertion sort

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

//mergesort using half the memory when it can

void merge_n2(int_vec& A, int start, int mid, int end){
	int tempS, tempE;
	tempS = start;
	tempE = mid+1;
	while (tempS < mid+1 && tempE < end){
		if ( A.at(tempS) < A.at(tempE) ){ //usual merge
			tempS++;
		} else {
			swap(A.at(tempS), A.at(tempE));
			tempE++;
			tempS++;
		}
	}
	while (tempS < end){
		if (A.at(tempS) < A.at(tempS + 1)) return;
		swap(A.at(tempS), A.at(tempS+1));
		tempS++;
	}
}

void mergesort_n2(int_vec& A, int start, int end){
	if (start < end){
		int mid = (start+end)>>1;
		mergesort_n2(A, start, mid);
		mergesort_n2(A, mid+1, end);
		merge_n2(A, start, mid, end);
	}
}

int main(int argc, char *argv[]) {
	
	int_vec A, A_merge, A_mergeK, A_mergeN2;
	/*char ask;
	int k;
	cout << "Todas las pruebas se realizarán con 1k (1000) datos.\n";
	fill_vec(A, 1000, 10000);
	cout << "Desea ver los datos generados? (y/n)"; cin >> ask; 
	if (ask == 'y'){
		print_vec(A);
	}
	cout << "Presione cualquier tecla para continuar\n"; cin >> ask;
	cout << "Mergesort normal\n";
	A_merge = mergesort(A);
	print_vec(A_merge);
	cout << "Presione cualquier tecla para continuar\n"; cin >> ask;
	cout << "Mergesort k (insert sort)\n";
	cout << "Ingrese un k\n"; cin >> k;
	A_mergeK = mergesort_k(A, k);
	print_vec(A_mergeK);
	cout << "Presione cualquier tecla para continuar\n"; cin >> ask;
	A.erase(A.begin(), A.end());
	*/
	fill_vec(A, 10, 1000);
	print_vec(A);
	mergesort_n2( A, 0, A.size() - 1 );
	print_vec(A);
	return 0;
}

