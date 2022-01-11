#include "Mensagem.h"

unsigned int Mensagem::getId(){
	return this->id;
}

void Mensagem::setId(unsigned int id){
	this->id = id;
}

Usuario* Mensagem::getEnviadaPor(){
	return this->enviadaPor;
}

void Mensagem::setEnviadaPor(Usuario* enviadaPor){
	this->enviadaPor = enviadaPor;
}

std::string Mensagem::getConteudo(){
	return this->conteudo;
}

void Mensagem::setConteudo(std::string conteudo){
	this->conteudo = conteudo;
}

std::string Mensagem::getDataHora(){
	return this->dataHora;
}

void Mensagem::setDataHora(std::string dataHora){
	this->dataHora = dataHora;
}

time_t Mensagem::getDataHoraUnix(){
	return this->dataHoraUnix;
}

void Mensagem::setDataHoraUnix(time_t dataHoraUnix){
	this->dataHoraUnix = dataHoraUnix;
}

bool Mensagem::operator==(const Mensagem &m1){
	return this->id == m1.id;
}
