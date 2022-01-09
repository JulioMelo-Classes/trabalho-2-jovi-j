#ifndef MENSAGEM_H
#define MENSAGEM_H
#include "Usuario.h"
#include <string>
#include <ctime>

class Mensagem{
private:
	unsigned int id;
	std::string dataHora;
	Usuario * enviadaPor;
	std::string conteudo;
	time_t dataHoraUnix;

public:
	Mensagem(unsigned int id, Usuario * enviadaPor, std::string conteudo){
		this->id = id;
		this->enviadaPor = enviadaPor;
		this->conteudo = conteudo;
		dataHoraUnix = time(0);
		this->dataHora = ctime(&dataHoraUnix);
	}

	unsigned int getId();
	void setId(unsigned int id);

	Usuario * getEnviadaPor();
	void setEnviadaPor(Usuario * enviadaPor);

	std::string getConteudo();
	void setConteudo(std::string conteudo);

	std::string getDataHora();
	void setDataHora(std::string dataHora);

	time_t getDataHoraUnix();
	void setDataHoraUnix(time_t dataHoraUnix);

	bool operator==(const Mensagem &m1);

};

#endif // !MENSAGEM_H