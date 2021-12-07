#ifndef CANAISTEXTO_H
#define CANAISTEXTO_H
#include "Mensagem.h"
#include "Usuario.h"
#include <string>
#include <vector>

class CanalTexto {
	public:
	unsigned int id;
	std::string nome;
	Usuario* dono;
	std::vector<Mensagem> mensagens;
	CanalTexto(unsigned int *id, std::string nome, Usuario* dono){
		this->id = *id;
		this->nome = nome;
		this->dono = dono;
		*id++;
	}
};

#endif // !CANAISTEXTO