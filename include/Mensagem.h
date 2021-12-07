#ifndef MENSAGEM_H
#define MENSAGEM_H
#include "Usuario.h"
#include <string>

class Mensagem{
public:
	unsigned int id;
	std::string dataHora;
	Usuario::Usuario * enviadaPor;
	std::string conteudo;

	Mensagem(unsigned int *id, std::string dataHora, Usuario::Usuario * enviadaPor, std::string conteudo){
		this->id = *id;
		this->dataHora = dataHora;
		this->enviadaPor = enviadaPor;
		this->conteudo = conteudo;
		*id++;
	}

};

#endif // !MENSAGEM_H