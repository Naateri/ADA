#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iterator>

#define MAX_VAL 50000
#define MIN_ITERATIONS 10

typedef std::vector<int> int_vec;
typedef std::vector<int_vec> vec_of_vecs;

void swap(int& a, int& b){
	int c = a;
	a = b;
	b = c;
}

int find_elem(int_vec A, int val){
	for(int i = 0; i < A.size(); i++){
		if (A.at(i) == val) return i;
	}
}

int_vec create_vector(int size, int max = MAX_VAL){
	int_vec ret (size);
	srand(time(NULL));
	for (int_vec::iterator it = ret.begin(); it != ret.end(); it++){
		*it = rand() % max;
	}
	return ret;
}

void print_vec(int_vec& vec){
	for (int_vec::iterator it = vec.begin(); it != vec.end(); it++){
		std::cout << (*it) << ' ';
	}
	std::cout << '\n';
}

int first_partition(int_vec& A, const int& start, const int& end){
	int pivot = A.at(end), i = start - 1;
	for (int j = start; j < end; j++){
		if (A.at(j) < pivot){
			i++;
			swap(A.at(i), A.at(j));
		}
	}
	swap(A.at(i+1), A.at(end));
	return i+1;
}

void quicksort(int_vec& A, const int& start, const int& end){
	int q;
	if (start < end){
		q = first_partition(A, start, end);
		quicksort(A, start, q-1);
		quicksort(A, q+1, end);
	}
}

double quicksort_test(const int& size){
	double elapsed_time;
	int_vec test = create_vector(size);
	clock_t begin = clock();
	quicksort(test, 0, size-1);
	clock_t end = clock();
	elapsed_time = double(end-begin)/CLOCKS_PER_SEC;
	return elapsed_time;
}

double quicksort_test_multiple(const int& size, const int& iterations = MIN_ITERATIONS){
	double total = 0.0;
	for(int i = 0; i < iterations; i++){
		total += quicksort_test(size);
	}
	return total / iterations;
}

int median(int_vec A){ //median for small elements
	std::sort(A.begin(), A.end());
	return (A)[A.size()>>1];
}

int select_k(int_vec A, int k); //algorithm that finds the k-th element in O(n) time

int smartly_choose_pivot(int_vec A){ //algorithm that'll find the median of medians
	int m, j, p, p_i, tempi;
	m = ceil(A.size() / float(5));
	int_vec candidate_pivots, temp;
	int_vec cop(A); ///cop = copy of A
	vec_of_vecs groups (m);
	for(int i = 0; i < m; i++){
		j = 5;
		temp.clear();
		while (j > 0 && !cop.empty() ){
			temp.push_back(cop.front() ); ///adding to temp first element of A's copy
			cop.erase(cop.begin() ); ///then deleting that number
			j--;
		}
		groups.at(i) = temp;
	}
	for(int i = 0; i < m-1; i++){
		p_i = median(groups.at(i)); //quick
		candidate_pivots.push_back(p_i);
	}
	if (candidate_pivots.size() == 1) tempi = candidate_pivots.at(0);
	else tempi = select_k(candidate_pivots, m/2/*, 0, candidate_pivots.size()>>1*/);
	p = find_elem(A, tempi);
	return p;
}

int partition(int_vec A, int p, int_vec& L, int_vec& R){ //for select_k
	L.clear(); //L are values lesser than p
	R.clear(); //R are values bigger than p
	for (int i= 0; i < A.size(); i++){
		if (i == p) continue;
		else if (A.at(i) <= A.at(p) ) L.push_back(A.at(i));
		else if (A.at(i) > A.at(p) ) R.push_back(A.at(i) );
	}
	return A.at(p);
}

int select_k(int_vec A, int k){
	//if (end-start <= 5) return median(A);
	if (A.size() <= 5) return median(A);
	int p = smartly_choose_pivot(A);
	int_vec L, R;
	A.at(p) = partition(A, p, L, R);
	if (L.size() == k) return A.at(p);
	else if (L.size() > k) return select_k(L, k);
	else if (L.size() < k) return select_k(R, k-L.size()-1);
}

int median_partition(int_vec& A, const int& start, const int& end){
	int_vec cop;
	std::copy(A.begin(), A.begin() + (end-start), std::back_inserter(cop));
	int pivot = find_elem(A, select_k(cop, cop.size()>>1) ), i = start - 1; //median element
	swap(A.at(pivot), A.at(end));
	for (int j = start; j < end; j++){
		if (A.at(j) < A.at(pivot)){
			i++;
			swap(A.at(i), A.at(j));
		}
	}
	swap(A.at(i+1), A.at(pivot));
	return i+1;	
}

void quicksort_median(int_vec& A, const int& start, const int& end){
	int q;
	if (start < end){
		q = median_partition(A, start, end);
		quicksort(A, start, q-1);
		quicksort(A, q+1, end);
	}
}

double quicksort_m_test(const int& size){
	double elapsed_time;
	int_vec test = create_vector(size);
	clock_t begin = clock();
	quicksort_median(test, 0, size-1);
	clock_t end = clock();
	elapsed_time = double(end-begin)/CLOCKS_PER_SEC;
	return elapsed_time;
}

double quicksort_m_test_multiple(const int& size, const int& iterations = MIN_ITERATIONS){
	double total = 0.0;
	for(int i = 0; i < iterations; i++){
		total += quicksort_m_test(size);
	}
	return total / iterations;
}


int main(int argc, char *argv[]) {
	int_vec test = create_vector(100, 500);
	print_vec(test);
	quicksort_median(test, 0, test.size() - 1);
	print_vec(test);
	std::cout << "Quicksort normal (pivote ultimo elemento):\n";
	std::cout << "1000 elementos: " << quicksort_test_multiple(1000) << " segundos.\n";
	std::cout << "10000 elementos: " << quicksort_test_multiple(10000) << " segundos.\n";
	std::cout << "50000 elementos: " << quicksort_test_multiple(50000) << " segundos.\n";
	std::cout << "100000 elementos: " << quicksort_test_multiple(100000) << " segundos.\n";
	std::cout << "500000 elementos: " << quicksort_test_multiple(500000) << " segundos.\n";
	//std::cout << "1000000 elementos: " << quicksort_test_multiple(1000000) << " segundos.\n";
	//std::cout << "5000000 elementos: " << quicksort_test_multiple(5000000) << " segundos.\n";
	std::cout << "\nQuicksort hallando una aproximacion de la mediana:\n";
	std::cout << "1000 elementos: " << quicksort_m_test_multiple(1000) << " segundos.\n";
	std::cout << "10000 elementos: " << quicksort_m_test_multiple(10000) << " segundos.\n";
	std::cout << "50000 elementos: " << quicksort_m_test_multiple(50000) << " segundos.\n";
	std::cout << "100000 elementos: " << quicksort_m_test_multiple(100000) << " segundos.\n";
	std::cout << "500000 elementos: " << quicksort_m_test_multiple(500000) << " segundos.\n";
	std::cout << "1000000 elementos: " << quicksort_m_test_multiple(1000000) << " segundos.\n";
	std::cout << "5000000 elementos: " << quicksort_m_test_multiple(5000000) << " segundos.\n";
	return 0;
}

