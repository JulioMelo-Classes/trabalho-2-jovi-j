#include "Usuario.h"
#include <string>

Usuario::Usuario(unsigned int id, std::string nome, std::string email, std::string senha)
{
	this->id = id;
	this->nome = nome;
	this->email = email;
	this->senha = senha;
}


unsigned int Usuario::getId(){
	return this->id;
}

void Usuario::setId(unsigned int id){
	this->id = id;
}

std::string Usuario::getNome(){
	return this->nome;
}

void Usuario::setNome(std::string nome){
	this->nome = nome;
}

std::string Usuario::getEmail(){
	return this->email;
}

void Usuario::setEmail(std::string email){
	this->email = email;
}

std::string Usuario::getSenha(){
	return this->senha;
}

void Usuario::setSenha(std::string senha){
	this->senha = senha;
}

bool Usuario::operator==(const Usuario &u1){
	return this->id == u1.id;
}