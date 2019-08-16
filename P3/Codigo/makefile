all: ./contenedores ./TSP

contenedores: contenedores.cpp
	g++ -o $@ $^ -std=c++11 

TSP: viajantecomercio.cpp
	g++ -o $@ $^ -std=c++11 
	
clean:
	rm contenedores TSP
