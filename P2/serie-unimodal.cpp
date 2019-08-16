#include <iostream>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>

#define UMBRAL 10

using namespace std;
using namespace chrono;

double uniforme() {
	double u;
	u = (double) rand();
	u = u/(double)(RAND_MAX+1.0);
	return u;
}

int encuentra_p(int * v, int tam){
	int p;
	
	for(int i=0; i<tam-1; ++i){
		if(v[i]>v[i+1]){
			p=i;
			break;
		}
	}
	return p;
}

int encuentra_p_divide(int * v, int tam){
	int p, m;
	bool md, mi;
	
	if(tam<=UMBRAL){
		p=encuentra_p(v, tam);
	}else{
		m=(tam/2)-1;
		md=v[m]<v[m+1];
		mi=v[m-1]<v[m];
		
		if(md && mi){
			p=encuentra_p_divide(v+m+1, tam-m-2);
		}else if(!md && !mi){
			p=encuentra_p_divide(v, m);
		}else{
			p=m;
			cout << "P en centro" << endl;
		}
	}
	return p;
}


int main(int argc, char** argv){
	if (argc != 2) {
		cerr << "Formato " << argv[0] << " <num_elem>" << endl;
		return -1;
	}
	
	int n = strtol(argv[1], NULL, 10);
	int P;
	int * T = new int[n];
	chrono::_V2::system_clock::time_point t1, t2;
	unsigned long t;
	
	assert(T);
	
	srand(time(0));
	double u=uniforme();
	int p=1+(int)((n-2)*u);
	T[p]=n-1;
	for (int i=0; i<p; i++) T[i]=i;
	for (int i=p+1; i<n; i++) T[i]=n-1-i+p;
	
	
	t1=high_resolution_clock::now();
	P=encuentra_p_divide(T, n);
	t2=high_resolution_clock::now();
	
	
	/*for (int i=0; i<n; ++i){
		cout << T[i] << "  ";
	}
	cout << endl;
	cout << "P: " << P << endl;*/
	
	t=duration_cast<nanoseconds>(t2-t1).count();
	
	cout << n << "\t\t" << t << endl;
	delete[] T;
	
	return 0;
}
