.DEFAULT_GOAL := all

#quando adicionar uma nova dependencia não esqueça de atualizar aqui!
OBJECTS=build/Sistema.o build/Executor.o

build/Sistema.o: src/Sistema.cpp include/Sistema.h
	g++ -Iinclude src/Sistema.cpp -c -o build/Sistema.o

build/Executor.o: src/Executor.cpp include/Executor.h 
	g++ -Iinclude src/Executor.cpp -c -o build/Executor.o

#para adicionar novas regras apenas siga o formato
#build/usuario.o: src/usuario.cpp include/usuario.h
#	g++ -Iinclude src/usuario.cpp -c

objects: $(OBJECTS)

concordo: objects src/Concordo.cpp
	g++ -Wall -fsanitize=address -Iinclude $(OBJECTS) src/Concordo.cpp -o build/concordo

clean:
	rm build/*.o build/concordo

all: concordo

run:
	./build/concordo
