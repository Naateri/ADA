#include <iostream>
#include <vector>
#include <ctime>

typedef std::vector<int> int_vec;

const int_vec pasos = {0, 1, 2, 3, 4, 5, 6, 7};
const int_vec horizontal = {2, 1, -1, -2, -2, -1, 1, 2};
const int_vec vertical = {1, 2, 2, 1, -1, -2, -2, -1};

bool in(int_vec vector, int num){ //finds if a number is in a vector
	for(int_vec::iterator it = vector.begin(); it != vector.end(); it++){ //change for a binary_search
		if ( (*it) == num) return 1;
	}
}

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

void prueba(const int& i, const int& x, const int& y, bool& q, int** mat, const int& n){
	int xn, yn, m = 0, n2 = n*n;
	bool q1;
	do{
		q1 = 0;
		xn = x + horizontal.at(m);
		yn = y + vertical.at(m);
		if ( (xn < n && xn >= 0) && (yn < n && yn >= 0) ){
			if (mat[xn][yn] == 0){
				mat[xn][yn] = i;
				if ( i < (n2) ){
					prueba(i+1, xn, yn, q1, mat, n);
					if ( ! q1){
						mat[xn][yn] = 0;
					}
				} else {
					q1 = 1;
				}
			}
		}
		m++;
	} while(!q1 && m < 8);
	q = q1;
}

void paseo_de_caballo(const int& n, const int& start_x, const int& start_y){
	bool q;
	int** mat;
	mat = create_matrix(n);
	mat[start_x][start_y] = 1;
	prueba(2, start_x, start_y, q, mat, n);
	if (q) print_matrix(mat, n);
	else std::cout << "no hay solucion\n";
	delete[] mat;
}

int main(int argc, char *argv[]) {
	int n, x, y;
	std::cout << "Ingrese la cantidad de filas y columnas:\n";
	std::cin >> n;
	std::cout << "Ingrese la posicion inicial (empezando de 0):\n";
	std::cin >> x >> y;
	clock_t begin = clock();
	paseo_de_caballo(n, x, y);
	clock_t end = clock();
	std::cout << double(end-begin)/CLOCKS_PER_SEC << " segundos.\n";
	return 0;
}

