#include <iostream>
#include <vector>
#include <ctime>

typedef std::vector<int> int_vec;

int** create_matrix(int n){
	int** mat = new int*[n];
	mat[0] = new int[n*n];
	for (int i = 1; i < n; i++){
		mat[i] = mat[i-1] + n;
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			mat[i][j] = 0;
		}
	}
	return mat;
}

void print_matrix(int** m, int n){ //works only for squared matrices
	for(int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			std::cout << m[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool safe_queen(int** mat, const int& pos_x, const int& pos_y, const int& n){
	for(int i = 0; i < n; i++){  //vertical
		if (i == pos_x) continue;
		if (mat[i][pos_y]) return false;
	}
	for(int i = 0; i < n; i++){ //horizontal
		if (i == pos_y) continue;
		if (mat[pos_x][i]) return false;
	}
	for(int i = pos_x, j = pos_y; i >= 0 && j >= 0; i--, j--){ //upper-left
		if (mat[i][j]) return false;
	}
	for(int i = pos_x, j = pos_y; i < n && j < n; i++, j++){ //lower-right
		if (mat[i][j]) return false;
	}
	for(int i = pos_x, j = pos_y; i >= 0 && j < n; i--, j++){ //upper-right
		if (mat[i][j]) return false;
	}
	for(int i = pos_x, j = pos_y; i < n && j >= 0; i++, j--){ //lower-left
		if (mat[i][j]) return false;
	}
	return true;
}

bool n_queens_solver(int** mat, int queen, const int& n, const int& m){
	if (queen >= n) return true; //all queens placed
	for (int i = 0; i < m; i++){
		if (safe_queen(mat, i, queen, m)){
			mat[i][queen] = 1;
			if (n_queens_solver(mat, queen+1, n, m)) return true; //it found all queens
			mat[i][queen] = 0; //it failed
		}
	}
	return false;
}

void n_queens(const int& n, const int& m){
	if (n > m){
		std::cout << "No hay solucion\n";
		return;
	}
	int** mat = create_matrix(m);
	if (n_queens_solver(mat, 0, n, m)){
		print_matrix(mat, m);
	} else std::cout << "No hay solucion.\n";
}

int main(int argc, char *argv[]) {
	int m, n;
	std::cout << "Ingrese la cantidad de reinas\n";
	std::cin >> n;
	std::cout << "Ingrese la cantidad de filas y columnas del tablero:\n";
	std::cin >> m;
	clock_t begin = clock();
	n_queens(n, m);
	clock_t end = clock();
	std::cout << "Tiempo: " << double(end-begin)/CLOCKS_PER_SEC << " segundos.\n";
	return 0;
}

