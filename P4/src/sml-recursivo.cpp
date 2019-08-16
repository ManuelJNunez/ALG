#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

string SubsecuenciaMasLarga(string a, string b)
{
	if (a.empty() || b.empty())
	{
		return "";
	}
	
	if (a.front() == b.front())
	{
		return a.front() + SubsecuenciaMasLarga(string(a, 1, -1), string(b, 1, -1));
	}
	else
	{
		string tmpa, tmpb;
		
		tmpa = SubsecuenciaMasLarga(string(a, 1, -1), b);
		tmpb = SubsecuenciaMasLarga(a, string(b, 1, -1));
		
		return (tmpa.size() < tmpb.size()) ? tmpb:tmpa;
	}
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
	
	cout << "Solución (tam " << solucion.size() << "): " << solucion << "\nTiempo: " << duration << endl;
	
	return 0;
}
