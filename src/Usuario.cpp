#include "Usuario.h"
#include <string>

Usuario::Usuario(unsigned int *id, std::string nome, std::string email, std::string senha)
{
	this->id = *id;
	this->nome = nome;
	this->email = email;
	this->senha = senha;
	*id++;
}

bool operator==(Usuario &u1, Usuario &u2)
{
	return u1.id == u2.id;
}
