#include "Servidor.h"

Servidor::Servidor(unsigned int id, Usuario::Usuario *dono, std::string nome)
{
	this->dono = dono;
	this->nome = nome;
	this->id = id;
};


bool operator==(const Servidor &s1, const Servidor &s2)
{
	return s1.id == s2.id;
}