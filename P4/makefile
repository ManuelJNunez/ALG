SRC = ./src
BIN = ./bin

CC = g++

Make: $(BIN)/sml-recursivo $(BIN)/sml-recursivo-dyn $(BIN)/sml-iterativo

$(BIN)/sml-recursivo:
	$(CC) -std=c++11 $(SRC)/sml-recursivo.cpp -o $(BIN)/sml-recursivo
	
$(BIN)/sml-recursivo-dyn:
	$(CC) -std=c++11 $(SRC)/sml-recursivo-dyn.cpp -o $(BIN)/sml-recursivo-dyn
	
$(BIN)/sml-iterativo:
	$(CC) -std=c++11 $(SRC)/sml-iterativo.cpp -o $(BIN)/sml-iterativo

Clean:
	rm $(BIN)/*

Prueba: Make
	$(BIN)/sml-recursivo 10 15
	$(BIN)/sml-recursivo-dyn 10 15
	$(BIN)/sml-iterativo 10 15
