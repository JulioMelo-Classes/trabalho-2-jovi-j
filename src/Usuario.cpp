#include "Usuario.h"
#include <string>

Usuario::Usuario(unsigned int id, std::string nome, std::string email, std::string senha)
{
	this->id = id;
	this->nome = nome;
	this->email = email;
	this->senha = senha;
}

bool Usuario::operator==(const Usuario &u1){
	return this->id == u1.id;
}
