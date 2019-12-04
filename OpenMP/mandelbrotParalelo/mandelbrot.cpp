#include <complex>
#include <iostream>
#include <omp.h>

using namespace std;

int main(){
	int max_row, max_column, max_n;
	cin >> max_row;
	cin >> max_column;
	cin >> max_n;

	double clock_timer;
	char **mat = (char**)malloc(sizeof(char*)*max_row);

	for (int i=0; i<max_row;i++)
		mat[i]=(char*)malloc(sizeof(char)*max_column);

	
	int r;
	int c;
	int n;
	
    clock_timer = omp_get_wtime();

	for(r = 0; r < max_row; ++r){
		#pragma omp parallel for firstprivate(r, max_n) schedule(dynamic)
		for(c = 0; c < max_column; ++c){
			complex<float> z;

			for(n=1; (n<max_n) && (abs(z)<2); ++n){
				z = pow(z, 2) + decltype(z)(
					(float)c * 2 / max_column - 1.5,
					(float)r * 2 / max_row - 1
				);
			}
		
			mat[r][c]=(n == max_n ? '#' : '.');
		}
	}
	cout << "Tempo: " << (double)(omp_get_wtime()- clock_timer) << endl;
	
	for(int r = 0; r < max_row; ++r){
		for(int c = 0; c < max_column; ++c)
			std::cout << mat[r][c];
		cout << '\n';
	}	
}


