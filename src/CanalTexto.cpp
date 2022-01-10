#include "CanalTexto.h"

unsigned int CanalTexto::getId(){
	return this->id;
}

void CanalTexto::setId(unsigned int id){
	this->id = id;
}

std::string CanalTexto::getNome(){
	return this->nome;
}

void CanalTexto::setNome(std::string nome){
	this->nome = nome;
}

Usuario * CanalTexto::getDono(){
	return this->dono;
}

void CanalTexto::setDono(Usuario * dono){
	this->dono = dono;
}

std::vector<Mensagem> CanalTexto::getMensagens(){
	return this->mensagens;
}

void CanalTexto::setMensagens(std::vector<Mensagem> mensagens){
	this->mensagens = mensagens;
}

void CanalTexto::setMensagem(Mensagem mensagem){
	this->mensagens.push_back(mensagem);
}

