#ifndef MENSAGEM_H
#define MENSAGEM_H
#include "Usuario.h"
#include <string>
#include <ctime>

class Mensagem{
public:
	unsigned int id;
	std::string dataHora;
	Usuario * enviadaPor;
	std::string conteudo;
	time_t dataHoraUnix;

	Mensagem(unsigned int *id, std::string dataHora, Usuario * enviadaPor, std::string conteudo){
		this->id = *id;
		this->enviadaPor = enviadaPor;
		this->conteudo = conteudo;
		*id++;
		dataHoraUnix = time(0);
		this->dataHora = ctime(&dataHoraUnix);
	}

};

#endif // !MENSAGEM_H