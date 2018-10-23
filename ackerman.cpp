#include <iostream>
#include <ctime>

using namespace std;

unsigned long long ackerman(int m, int n){
	if (m == 0) return n+1;
	if (n == 0) return ackerman(m-1, 1);
	return ackerman(m-1, ackerman( m, n-1 ) );
}

double ackerman_time(int m, int n){
	clock_t begin = clock();
	cout << ackerman(m,n) << endl;
	clock_t end = clock();
	return double(end-begin)/CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) {
	cout << ackerman_time(5,0) << endl;
	cout << ackerman_time(4,1) << endl;
	cout << ackerman_time(5,1) << endl;
	return 0;
}

