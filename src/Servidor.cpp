#include "Servidor.h"


Servidor::Servidor(unsigned int id, Usuario *dono, std::string nome){
	this->dono = dono;
	this->nome = nome;
	this->id = id;
};


unsigned int Servidor::getId(){
	return this->id;
}

void Servidor::setId(unsigned int id){
	this->id = id;
}

Usuario* Servidor::getDono(){
	return this->dono;
}

void Servidor::setDono(Usuario* dono){
	this->dono = dono;
}

std::string Servidor::getNome(){
	return this->nome;
}

void Servidor::setNome(std::string nome){
	this->nome = nome;
}

std::string Servidor::getDescricao(){
	return this->descricao;
}

void Servidor::setDescricao(std::string descricao){
	this->descricao = descricao;
}

std::string Servidor::getCodigoConvite(){
	return this->codigoConvite;
}

void Servidor::setCodigoConvite(std::string codigoConvite){
	this->codigoConvite = codigoConvite;
}

std::vector<CanalTexto> Servidor::getCanaisTexto(){
	return this->canaisTexto;
}

void Servidor::setCanaisTexto(std::vector<CanalTexto> canaisTexto){
	this->canaisTexto = canaisTexto;
}

void Servidor::addCanalTexto(CanalTexto canalTexto){
	this->canaisTexto.push_back(canalTexto);
}

std::vector<Usuario*> Servidor::getParticipantes(){
	return this->participantes;
}

void Servidor::setParticipantes(std::vector<Usuario*> participantes){
	this->participantes = participantes;
}

void Servidor::setParticipante(Usuario* participante){
	this->participantes.push_back(participante);
}

bool Servidor::operator==(const Servidor &servidor){
	return (this->id == servidor.id);
}