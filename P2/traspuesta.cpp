//g++ -o traspuesta traspuesta.cpp
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>

using namespace std;
using namespace chrono;

const int MAXIMO=100000;

void traspuesta(int** &matriz, int &n, int &m){
	int** traspuesta;
	int aux;
	
	traspuesta=new int*[m];
	for (int i=0; i<m; ++i){
		traspuesta[i]=new int[n];
		for (int j=0; j<n; ++j)
			traspuesta[i][j]=matriz[j][i];
	}
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
	cout << n << "\t\t" << m << "\t\t" << t << endl;
	
	return 0;
}
