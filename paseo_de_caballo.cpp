#include <iostream>
#include <vector>

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
	for (int i = 0; i < n; i++){
		mat[i] = new int[n];
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			mat[i][j] = 0;
		}
	}
	return mat;
}

void prueba(int i, int x, int y, bool& q, int** mat, const int& n){
	int xn, yn, m = 0, n2 = n*n;
	bool q1;
	std::cout << "prueba " << i << "\n";
	do{
		q1 = 0;
		std::cout << "m: " << m << std::endl;
		xn = x + horizontal.at(m);
		yn = y + vertical.at(m);
		if ( in(pasos, xn) && in(pasos, yn) ){
			if (mat[xn][yn] == 0){
				mat[xn][yn] = i;
				std::cout << "i " << i << '\n';
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
	} while(!q1 || m < n);
	q = q1;
}

void paseo_de_caballo(int n, int start_x, int start_y){
	bool q;
	int** mat;
	mat = create_matrix(n);
	mat[start_x][start_y] = 1;
	std::cout << "hola\n";
	prueba(2, start_x, start_y, q, mat, n);
	std::cout << "hola2\n";
	if (q) std::cout << "solucion\n";
	else std::cout << "no hay solucion\n";
	delete[] mat;
}

int main(int argc, char *argv[]) {
	paseo_de_caballo(8, 0, 0);
	return 0;
}

