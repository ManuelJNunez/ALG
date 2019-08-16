//g++ -o traspuestadyv traspuestadyv.cpp
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace chrono;

const int MAXIMO=100000;

void TrasponDiagonal(int** &matriz, int** &traspuesta, int n, int m){
	int menor;
	if(n < m)
		menor = n;
	else if(m < n)
		menor = m;
	else
		menor = n;

	for(int i = 0; i < menor; ++i)
		traspuesta[i][i] = matriz[i][i];
}

void TrasponTrianguloInferior(int** &matriz, int** &traspuesta, int n, int m){
	int j = 1;
	int i = 0;
	bool terminado = false;

	if(n != 1)
		while(!terminado){
			traspuesta[i][j] = matriz[j][i];

			j++;

			if(j == n){
				i++;
				j = i+1;

				if(j == n || i == m)
					terminado = true;
			}
		}
}

void TrasponTrianguloSuperior(int** &matriz, int** &traspuesta, int n, int m){
	int j = 0;
	int i = 1;
	bool terminado = false;

	if(m != 1)
		while(!terminado){
			traspuesta[i][j] = matriz[j][i];

			i++;

			if(m == i){
				j++;
				i = j+1;
				
				if(j == n || i == m)
					terminado = true;
			}
		}
}

void traspuesta(int** &matriz, int &n, int &m){
	int** traspuesta;
	int aux;
	
	traspuesta=new int*[m];

	for (int i=0; i<m; ++i)
		traspuesta[i]=new int[n];

	TrasponDiagonal(matriz, traspuesta, n, m);
	TrasponTrianguloSuperior(matriz, traspuesta, n, m);
	TrasponTrianguloInferior(matriz, traspuesta, n, m);

	for (int i=0; i<n; ++i)
		delete[] matriz[i];
	delete[] matriz;
	
	matriz=traspuesta;
	aux=n;
	n=m;
	m=aux;
}

void imprimir(int** matriz, int n, int m){
	for (int i=0; i<n; ++i){
		for (int j=0; j<m; ++j)
			cout << matriz[i][j] << "   ";
		cout << endl;
	}
}

int main(int argc, char** argv){
	if (argc<3){
		cerr << "Necesarios dos argumentos: dimensiones de la matriz" << endl;
		return 1;
	}
	
	int n, m;
	int** matriz;
	srand(time(NULL));
	chrono::_V2::system_clock::time_point t1, t2;
	unsigned long t;
	
	
	n=strtol(argv[1], NULL, 10);
	m=strtol(argv[2], NULL, 10);
	
	matriz=new int*[n];
	for (int i=0; i<n; ++i){
		matriz[i]=new int[m];
		for(int j=0; j<m; ++j)
			matriz[i][j]=rand()%MAXIMO;
	}
	
	//imprimir(matriz, n, m);
	
	t1=high_resolution_clock::now();
	traspuesta(matriz, n, m);
	t2=high_resolution_clock::now();
	
	//cout << "TRASPUESTA" << endl;
	//imprimir(matriz, n, m);
	
	t=duration_cast<microseconds>(t2-t1).count();
	cout << n << "x" << m << "\t" << t << endl;
	
	return 0;
}