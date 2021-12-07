#include "Servidor.h"

Servidor::Servidor(unsigned int id, Usuario *dono, std::string nome)
{
	this->dono = dono;
	this->nome = nome;
	this->id = id;
};