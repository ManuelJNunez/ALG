#include <iostream>
#include <map>
#include <cstdlib>
#include <time.h>

using namespace std;

const unsigned int K=1000;
const unsigned int MAX_PESO=200;

unsigned int maximizar_n_contenedores(map<unsigned int, unsigned int> contenedores, map<unsigned int, unsigned int> & resultado){
	pair<unsigned int, unsigned int> optimo;
	unsigned int peso_carga=0;
	map<unsigned int, unsigned int>::iterator it;
	
	resultado.clear();
	
	while(peso_carga<=K or contenedores.empty()){
		
		it=contenedores.begin();
		optimo.first=(*it).first;
		optimo.second=(*it).second;
		++it;
		for (; it!=contenedores.end(); ++it){
			if((*it).second < optimo.second ){
				optimo.first=(*it).first;
				optimo.second=(*it).second;
			}
		}
		
		//cout << "Óptimo: " << optimo.first << "  " << optimo.second << endl;
		
		peso_carga+=optimo.second;
		if(peso_carga>K or contenedores.empty()){
			peso_carga-=optimo.second;
			break;
		}
		contenedores.erase(optimo.first);
		resultado[optimo.first]=optimo.second;
	}
	return peso_carga;
}

unsigned int maximizar_carga(map<unsigned int, unsigned int> contenedores, map<unsigned int, unsigned int> & resultado){
	pair<unsigned int, unsigned int> optimo;
	unsigned int peso_carga=0;
	map<unsigned int, unsigned int>::iterator it;
	
	resultado.clear();
	
	while(peso_carga<=K or contenedores.empty()){
		
		it=contenedores.begin();
		optimo.first=(*it).first;
		optimo.second=(*it).second;
		++it;
		for (; it!=contenedores.end(); ++it){
			if((*it).second > optimo.second ){
				optimo.first=(*it).first;
				optimo.second=(*it).second;
			}
		}
		
		//cout << "Óptimo: " << optimo.first << "  " << optimo.second << endl;
		
		peso_carga+=optimo.second;
		if(peso_carga>K or contenedores.empty()){
			peso_carga-=optimo.second;
			break;
		}
		contenedores.erase(optimo.first);
		resultado[optimo.first]=optimo.second;
	}
	return peso_carga;
}

int main(){
	map<unsigned int, unsigned int> contenedores, resultado;
	map<unsigned int, unsigned int>::const_iterator it;
	unsigned int total_pesos=0;
	unsigned int aux, i=0;
	unsigned int peso_carga;
	
	srand(time(NULL));
	
	while(total_pesos <= (K+K)){
		aux=rand()%MAX_PESO;
		total_pesos+=aux;
		contenedores[i]=aux;
		++i;
	}
	cout << "K = " << K << endl;
	cout << "Contenedores: " << endl;;
	for(i=0; i<contenedores.size(); ++i){
		cout << "[" << i << " , " << contenedores[i] << "]\n";
	}
	cout << endl;
	
	
	
	cout << "\nMAXIMIZAMOS NUMERO DE CONTENEDORES" << endl;
	
	peso_carga=maximizar_n_contenedores(contenedores, resultado); 
	
	cout << "Solución: carga " << peso_carga << endl;
	
	for(it=resultado.begin(); it!=resultado.end(); ++it){
		cout << "[" << (*it).first << " , " << (*it).second << "]\n";
	}
	cout << endl;
	
	cout << "\nMAXIMIZAMOS CARGA" << endl;
	
	peso_carga=maximizar_carga(contenedores, resultado); 
	
	cout << "Solución: carga " << peso_carga << endl;
	
	for(it=resultado.begin(); it!=resultado.end(); ++it){
		cout << "[" << (*it).first << " , " << (*it).second << "]\n";
	}
	cout << endl;
	
	return 0;
}
