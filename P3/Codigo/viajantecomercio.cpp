#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <string>
#include <cmath>
#include <set>

using namespace std;
using namespace chrono;

struct ciudad{
	double x, y;
};

vector<ciudad> LeeCiudades(istream& is){
	vector<ciudad> leidas;
	ciudad leida;
	string linea;
	int indice;

	getline(is, linea);

	while(linea != "NODE_COORD_SECTION")
		getline(is, linea);

	while(is >> indice){
		is >> leida.x;
		is >> leida.y;
		leidas.push_back(leida);
	}

	return leidas;
}

vector<int> LeeCaminoOptimo(istream& is){
	vector<int> optimo;
	string linea;
	int indice;

	getline(is, linea);

	while(linea != "TOUR_SECTION")
		getline(is, linea);

	is >> indice;

	while(indice != -1){
		optimo.push_back(indice);
		is >> indice;
	}

	optimo.push_back(optimo[0]);

	return optimo;
}

vector<vector<double>> GeneraMatrizDistancias(const vector<ciudad>& ciudades){
	vector<vector<double>> distancias(ciudades.size(), vector<double>(ciudades.size(), 0));
	double distancia;
	for(int i = 0; i < ciudades.size(); ++i){
		for(int j = 0; j < i; ++j){
			distancia = sqrt(pow(ciudades[j].x - ciudades[i].x,2) + pow(ciudades[j].y - ciudades[i].y,2));
			distancias[j][i] = distancias[i][j] = distancia;
		}
	}

	/*for(int i = 0; i < ciudades.size(); ++i){
		for(int j = 0; j < ciudades.size(); ++j)
			cout << distancias[i][j] << "\t";

		cout << endl;
	}*/

	return distancias;
}

double CalculaDistanciaPath(vector<int> path, vector<vector<double>> distancias){
	double distancia;

	for(int i = 0; i < path.size()-1; ++i)
		distancia += distancias[path[i]-1][path[i+1]-1];

	return distancia;
}

vector<int> TSPCercania(const vector<ciudad>& ciudades,const vector<vector<double>>& distancias, int ciudadinicial){
	vector<int> path;
	vector<bool> usadas(ciudades.size(), false);
	int ciudadactual, proximaciudad, primeraciudad;
	double minimo;

	ciudadactual = --ciudadinicial;
	primeraciudad = ciudadactual;
	minimo = 2000000000;
	usadas[ciudadactual] = true;
	path.push_back(ciudadactual+1);

	for(int i = 0; i < ciudades.size()-1; ++i){
		for(int j = 0; j < ciudades.size(); ++j){
			if(distancias[ciudadactual][j] < minimo && !usadas[j]){
				minimo = distancias[ciudadactual][j];
				proximaciudad = j;
			}
		}
		ciudadactual = proximaciudad;
		usadas[ciudadactual] = true;
		path.push_back(ciudadactual+1);
		minimo = 2000000000;
	}

	path.push_back(primeraciudad+1);

	return path;
}

vector<int> CalculaCicloMasCorto(vector<int> caminoparcial, const vector<vector<double>>& distancias, set<int> nousadas, const int posinsercion, double &distancia){
	double min = 2000000000, distancia1;
	vector<int> ciclomascorto;
	set<int>::const_iterator itset;
	vector<int>::iterator posinsert = caminoparcial.begin();

	advance(posinsert, posinsercion);
	caminoparcial.insert(posinsert, 0);

	for(itset = nousadas.begin(); itset != nousadas.end(); ++itset){
		caminoparcial[posinsercion] = (*itset) + 1;
		distancia = CalculaDistanciaPath(caminoparcial, distancias);
		distancia += distancias[caminoparcial.size()-1][caminoparcial[0]];

		if(min > distancia){
			min = distancia;
			ciclomascorto = caminoparcial;
		}
	}

	distancia = min;

	return ciclomascorto;
}

vector<int> TSPInsercionEconomica(const vector<ciudad>& ciudades,const vector<vector<double>>& distancias){
	vector<int> resultado;
	set<int> nousadas;
	int masalnorte, masaloeste, masaleste;
	double maximax, maximay, minimax;

	maximax = maximay = 0;
	minimax = 2000000000;

	for(int i = 0; i < ciudades.size(); ++i){
		nousadas.insert(i);
	}

	for(int i = 0; i < ciudades.size(); ++i){
		if(minimax > ciudades[i].x){
			minimax = ciudades[i].x;
			masaloeste = i;
		}else if(maximax < ciudades[i].x){
			maximax = ciudades[i].x;
			masaleste = i;
		}else if(maximay < ciudades[i].y){
			maximay = ciudades[i].y;
			masalnorte = i;
		}
	}

	nousadas.erase(masalnorte);
	nousadas.erase(masaloeste);
	nousadas.erase(masaleste);
	resultado.push_back(masaloeste+1);
	resultado.push_back(masaleste+1);
	resultado.push_back(masalnorte+1);

	vector<int> ciclomascorto, ciclomin;
	int posciudadusada;
	double dmin = 2000000000, dciclomascorto;

	while(!nousadas.empty()){
		for(int i = 0; i <= resultado.size(); ++i){
			ciclomascorto = CalculaCicloMasCorto(resultado, distancias, nousadas, i, dciclomascorto);

			if(dciclomascorto < dmin){
				dmin = dciclomascorto;
				ciclomin = ciclomascorto;
				posciudadusada = i;
			}
		}
		dmin = 2000000000;
		resultado = ciclomin;
		nousadas.erase(resultado[posciudadusada]-1);
	}

	resultado.push_back(resultado[0]);

	return resultado;
}

vector<int> EncuentraVerticeMasCercano(vector<int> caminoparcial, const vector<vector<double>>& distancias, set<int> nousadas, const int posinsercion, double &distancia){
	double min = 2000000000, distancia1;
	vector<int> ciclomascorto;
	set<int>::const_iterator itset;
	vector<int>::iterator posinsert = caminoparcial.begin();

	advance(posinsert, posinsercion);
	caminoparcial.insert(posinsert, 0);

	for(itset = nousadas.begin(); itset != nousadas.end(); ++itset){
		caminoparcial[posinsercion] = (*itset) + 1;
		distancia = distancias[caminoparcial[posinsercion-1]-1][caminoparcial[posinsercion]-1];

		if(min > distancia){
			min = distancia;
			ciclomascorto = caminoparcial;
		}
	}

	distancia = min;

	return ciclomascorto;
}

vector<int> TSPInsercionCercania(const vector<ciudad>& ciudades,const vector<vector<double>>& distancias){
	vector<int> resultado;
	set<int> nousadas;
	int masalnorte, masaloeste, masaleste;
	double maximax, maximay, minimax;

	maximax = maximay = 0;
	minimax = 2000000000;

	for(int i = 0; i < ciudades.size(); ++i){
		nousadas.insert(i);
	}

	for(int i = 0; i < ciudades.size(); ++i){
		if(minimax > ciudades[i].x){
			minimax = ciudades[i].x;
			masaloeste = i;
		}else if(maximax < ciudades[i].x){
			maximax = ciudades[i].x;
			masaleste = i;
		}else if(maximay < ciudades[i].y){
			maximay = ciudades[i].y;
			masalnorte = i;
		}
	}

	nousadas.erase(masalnorte);
	nousadas.erase(masaloeste);
	nousadas.erase(masaleste);
	resultado.push_back(masaloeste+1);
	resultado.push_back(masaleste+1);
	resultado.push_back(masalnorte+1);

	vector<int> nuevociclo, ciclomin;
	int posciudadusada;
	double dmin = 2000000000, dciclomascorto;

	while(!nousadas.empty()){
		for(int i = 1; i <= resultado.size(); ++i){
			nuevociclo = EncuentraVerticeMasCercano(resultado, distancias, nousadas, i, dciclomascorto);

			if(dciclomascorto < dmin){
				dmin = dciclomascorto;
				ciclomin = nuevociclo;
				posciudadusada = i;
			}
		}
		dmin = 2000000000;
		resultado = ciclomin;
		nousadas.erase(resultado[posciudadusada]-1);
	}

	resultado.push_back(resultado[0]);

	return resultado;
}

void EscribeSolucionEnFichero(ostream & os, vector<int> path, vector<ciudad> ciudades){
	for(int i = 0; i < path.size(); ++i)
		os << path[i] << " " << ciudades[path[i]-1].x << " " << ciudades[path[i]-1].y << endl;
}

int main(int argc, char* argv[]){
	if(argc < 6){
		cerr << "Uso: ./viajantecomercio <archivoentrada> <archivo con camino optimo> <archivosalida1> <archivosalida2> <archivosalida3>" << endl;
		return 1;
	}
	ifstream in(argv[1]);
	ifstream archivooptimo(argv[2]);
	ofstream outnearest(argv[3]), outinsertion1(argv[4]), outinsertion2(argv[5]);
	vector<ciudad> ciudades;
	vector<int> caminocercania, caminoinsercioneconomica, caminoinsercioncercania, optimo;
	int ciudadinicial;
	chrono::_V2::system_clock::time_point t1, t2;
	vector<vector<double>> distancias;
	unsigned long t;

	ciudades = LeeCiudades(in);
	optimo = LeeCaminoOptimo(archivooptimo);
	distancias = GeneraMatrizDistancias(ciudades);

	cout << "Inserte la ciudad de inicio (número de 1 a " << ciudades.size() << "): ";
	cin >> ciudadinicial;

	t1=high_resolution_clock::now();
	caminocercania = TSPCercania(ciudades, distancias, ciudadinicial);
	t2=high_resolution_clock::now();
	t=duration_cast<microseconds>(t2-t1).count();

	cout << "Tiempo algoritmo cercanía: " << t << endl;

	t1=high_resolution_clock::now();
	caminoinsercioneconomica = TSPInsercionEconomica(ciudades, distancias);
	t2=high_resolution_clock::now();
	t=duration_cast<microseconds>(t2-t1).count();

	cout << "Tiempo algoritmo inserción económica: " << t << endl;

	t1=high_resolution_clock::now();
	caminoinsercioncercania = TSPInsercionCercania(ciudades, distancias);
	t2=high_resolution_clock::now();
	t=duration_cast<microseconds>(t2-t1).count();

	cout << "Tiempo algoritmo inserción por cercanía: " << t << endl;

	cout << endl << "Camino por cercanía: ";

	for(int i = 0; i < caminocercania.size(); ++i)
		cout << caminocercania[i] << " ";

	cout << endl << "Camino por inserción económica: ";

	for(int i = 0; i < caminoinsercioneconomica.size(); ++i)
		cout << caminoinsercioneconomica[i] << " ";

	cout << endl << "Camino por inserción por cercanía: ";

	for(int i = 0; i < caminoinsercioncercania.size(); ++i)
		cout << caminoinsercioncercania[i] << " ";

	cout << endl << endl;

	cout << "Coste del camino calculado por cercanía: " << CalculaDistanciaPath(caminocercania, distancias) << endl;
	cout << "Coste del camino calculado por inserción económica: " << CalculaDistanciaPath(caminoinsercioneconomica, distancias) << endl;
	cout << "Coste del camino calculado por inserción por cercanía: " << CalculaDistanciaPath(caminoinsercioncercania, distancias) << endl;
	cout << "Coste del camino optimo: " << CalculaDistanciaPath(optimo, distancias) << endl;

	EscribeSolucionEnFichero(outnearest, caminocercania, ciudades);
	EscribeSolucionEnFichero(outinsertion1, caminoinsercioneconomica, ciudades);
	EscribeSolucionEnFichero(outinsertion2, caminoinsercioncercania, ciudades);

	return 0;
}