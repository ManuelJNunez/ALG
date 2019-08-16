#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

string SubsecuenciaMasLarga(string a, string b)
{
	//Reserva de memoria
	int **solucion = new int* [a.size()+1];
	for (int i = 0; i < a.size()+1; ++i)
		solucion[i] = new int[b.size()+1];
	
	//Calculo de la solucion
	for (int i = 0; i <= b.size(); ++i)
		solucion[0][i] = 0;
	for (int i = 0; i <= a.size(); ++i)
		solucion[i][0] = 0;
	
	for (int i = 1; i <= a.size(); ++i)
	{
		for (int j = 1; j <= b.size(); ++j)
		{
			if (a[i-1] == b[j-1])
				solucion[i][j] = solucion[i-1][j-1] + 1;
			else
				solucion[i][j] = (solucion[i-1][j] < solucion[i][j-1]) ? solucion[i][j-1]:solucion[i-1][j];
		}
	}
	
	//Reconstrucción del string sml
	int x = a.size(),
		y = b.size(),
		actual = solucion[x][y];

	string sml;
	
	while (actual != 0)
	{
		if (solucion[x][y-1] == actual)
		{
			y--;
		}
		else if (solucion[x-1][y] == actual)
		{
			x--;
		}
		else
		{
			sml.push_back(a[x-1]);
			x--;
			y--;
			actual = solucion[x][y];
		}
	}
	
	// Liberar memoria
	for (int i = 0; i < a.size()+1; ++i)
			delete [] solucion[i];
		delete [] solucion;
	
	return sml;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		if (argc > 1){
			if (strcmp(argv[1], "-manual") != 0)
			{
				cerr << "Usage: scml [-manual] <longStringA> <longStringB>" << endl;
				exit(1);
			}
			
		} else
			exit(1);
	}
	
	string a, b, solucion;
	const string A_TO_Z = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	if (strcmp(argv[1], "-manual") == 0)
	{
		cout << "Introduce el string a: ";
		cin >> a;
		
		cout << "Introduce el string b: ";
		cin >> b;
	}
	else
	{
		// Generación aleatoria de Strings
		unsigned seed = chrono::system_clock::now().time_since_epoch().count();
		default_random_engine generator (seed);
		uniform_int_distribution<int> distribution(0, A_TO_Z.size() - 1);

		for (int i = 0; i < stoi(argv[1]); ++i)
			a.push_back(A_TO_Z[distribution(generator)]);
		
		for (int i = 0; i < stoi(argv[2]); ++i)
			b.push_back(A_TO_Z[distribution(generator)]);
	}

	// Calculo de SML y salida
	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	solucion = SubsecuenciaMasLarga(a, b);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	
	auto duration = duration_cast<microseconds> (t2 - t1).count();
	
	cout << "String A (tam " << a.size() << "): " << a << "\nString B (tam " << b.size() << "): " << b << endl;
	
	cout << "Solución (tam " << solucion.size() << "): ";
	
	for (int i = solucion.size() - 1; i >= 0; --i)
		cout << solucion[i];
	
	cout << "\nTiempo: " << duration << endl;
	
	return 0;
}
