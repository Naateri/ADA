#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

#define MAXIM 99999999

typedef int** mat;
typedef std::vector<int> int_vec;
typedef std::pair<int, int> mat_level; //used to get the order of multiplication
typedef std::list<mat_level> mlevel_list;
typedef std::list<int> int_list;
typedef std::vector<bool> bool_vec;

struct menor{
	bool operator()(const mat_level& one, const mat_level& two){
		if (one.second != two.second){
			return one.second < two.second;
		}
		else return two.first < one.first;
	}
}  less_than;

void print_mat(int f, int c, mat m){
	for(int i = 0; i < f; i++){
		for(int j = 0; j < c; j++){
			std::cout << m[i][j] << ' ';
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void print_list(mlevel_list t){
	for(mlevel_list::iterator it = t.begin(); it != t.end(); it++){
		std::cout << (*it).first << ' ';
	}
	std::cout << std::endl;
}

mat create_matrix(int n, int m){
	mat my_mat = new int*[n];
	my_mat[0] = new int[n*m];
	for (int i = 1; i < n; i++){
		my_mat[i] = my_mat[i-1] + m;
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			my_mat[i][j] = 0;
		}
	}
	return my_mat;
}

void print_intlist(int_list t){
	for(int_list::iterator it = t.begin(); it != t.end(); it++){
		std::cout << (*it) << ' ';
	}
	std::cout << std::endl;
}

void find_path(mat s, int i, int j, mlevel_list& path, int level = 0){
	int k;
	if (i == j) {
		path.push_back(std::make_pair(i, level));
	}
	else{
		k = s[i][j];
		find_path(s, i, k, path, level+1);
		find_path(s, k+1, j, path, level+1);
	}
}

///USELESS FUNCTION

/*int_list find_path2(mat m, int n){
	int_list path;
	int min = MAXIM, min_i, min_j;
	for(int i = 1; i < n-2; i++){
		min = MAXIM;
		for(int j = 1; j + i < n; j++){
			if (m[j][j+i] < min){
				min = m[j][j+i];
				min_i = j;
				min_j = j+i;
			}
		}
		if (std::find(path.begin(), path.end(), min_i) == path.end() ) 
			path.push_back(min_i);
		if (std::find(path.begin(), path.end(), min_j) == path.end() ) 
			path.push_back(min_j);
	}
	if (std::find(path.begin(), path.end(), 1) == path.end() ) 
		path.push_back(1);
	if (std::find(path.begin(), path.end(), n-1) == path.end() ) 
		path.push_back(n-1);
	return path;
} */

void print_path(mat s, int i, int j){
	if (i == j) std::cout << "mat_" << i << ' ';
	else {
		std::cout << "( ";
		print_path(s, i, s[i][j]);
		print_path(s, s[i][j] + 1, j);
		std::cout << " )";
	}
}

mlevel_list matrix_chain_dp(int_vec dim){ //dynamic programming
	int temp, j;
	mlevel_list path;
	mat m = create_matrix(dim.size(), dim.size()), s = create_matrix(dim.size(), dim.size());
	for (int h = 0; h < dim.size(); h++){
		for (int i = 0; i < dim.size()-h; i++){
			j = i+h;
			for (int k = i+1; k < j; k++){
				temp = m[i+1][k] + m[k+1][j] + (dim.at(i) * dim.at(k) * dim.at(j));
				if (m[i+1][j] != 0){
					if (temp < m[i+1][j]){
						m[i+1][j] = temp;
						s[i+1][j] = k;
					}
				} else{
					m[i+1][j] = temp;
					s[i+1][j] = k;
				}
			}
		}
	}
	//print_mat(dim.size(), dim.size(), m); //to print the matrix
	find_path(s, 1, dim.size()-1, path);
	path.sort(less_than);
	path.reverse();
	std::cout << "El orden de las matrices para multiplicarse es: ";
	print_list(path);
	print_path(s, 1, dim.size()-1);
	std::cout << std::endl;
	std::cout << "El costo minimo es: " << m[1][dim.size()-1] << std::endl;
	return path;
}

void matrix_chain_brute_force(int_vec dim){
	bool_vec done(dim.size()-1, 0);
	int min = MAXIM, acum = 0, mult, temp, min_i, min_j;
	int k;
	for(int i = 0; i < dim.size()-2; i++){ //multiplications to find
		min = MAXIM;
		min_i = min_j = 0;
		for(int j = 1; j < dim.size()-1; j++){
			if (done.at(j-1) && done.at(j) ) continue;
			if (!done.at(j-1)){
				//std::cout << "j: " << j << ", i: " << i << std::endl;
				k = j;
				while (done.at(k) && k < done.size()){ //to find where to multiply
					k++;
				}
				//k--;
				mult = dim.at(j-1) * dim.at(j) * dim.at(k+1);
				temp = acum + mult;
				//std::cout << "temp: " << temp << std::endl;
				if (temp < min){
					min = temp;
					min_i = j-1;
					//min_i = j;
					//min_j = j;
					min_j = k;
				}
			}
			if (!done.at(j)){
				//std::cout << "j_test_2: " << j << std::endl;
				k = j-1;
				while (done.at(k) && k > 0){ //to find where to multiply
					k--; 
				}
				//k++;
				//mult = dim.at(j-1) * dim.at(j) * dim.at(j+1);
				mult = dim.at(j+1) * dim.at(j) * dim.at(k);
				temp = acum + mult;
				if (temp < min){
					min = temp;
					min_i = k;
					//min_i = j-1;
					//min_j = j;
					min_j = j;
				}
			}
		}
		if (min == MAXIM) continue;
		acum = min;
		//std::cout << "acum: " << acum << std::endl;
		std::cout << min_i + 1 << ' ' << min_j + 1 << std::endl;
		done.at(min_i) = 1;
		done.at(min_j) = 1;
		/*for(int h = 0; h < done.size(); h++){
			std::cout << done.at(h) << ' ';
		}*/
		std::cout << std::endl;
	}
	//std::cout << std::endl;
	std::cout << "el minimo es: " << acum << std::endl;
}

int main(int argc, char *argv[]) {
	//int_vec temp = {10, 20, 50, 1, 100, 80, 15, 24, 2};
	//int_vec temp = {30,1,40,10,25};
	//int_vec temp = {10, 20, 50, 1, 100};
	int n;
	std::cin >> n;
	int_vec temp(n);
	for(int i = 0; i < n; i++){
		std::cin >> temp.at(i);
	}
	matrix_chain_dp(temp);
	//matrix_chain_brute_force(temp);
	return 0;
}
