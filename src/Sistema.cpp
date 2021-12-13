#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <algorithm>

/* COMANDOS */
string Sistema::quit() {
  return "Saindo...";
}

string Sistema::create_user (const string email, const string senha, const string nome) {
	std::cout << "Criando Usuário " << nome << "(" << email << ")" << std::endl;
	if (this->findUsuarioByEmail(email) != NULL) {
		return "Usuário já existe!	";
	}
	Usuario usuario(&this->idUsuario, email, senha, nome);
	this->usuarios.push_back(usuario);
	return "Usuario criado";
}

std::string Sistema::delete_user (const std::string email, const std::string senha){
	Usuario * usuario = this->findUsuarioByEmail(email);
	if (usuario == NULL) {
		return "Usuario não cadastrado!";
	}
	else{
		if (usuario->senha == senha) {
			this->usuarios.erase(std::remove(this->usuarios.begin(), this->usuarios.end(), *usuario), this->usuarios.end());
			return "Usuario deletado";
		}
		else{
			return "Senha incorreta";
		}
	}
}

string Sistema::login(const string email, const string senha) {
	Usuario * usuario = this->findUsuarioByEmail(email);
	if (usuario == NULL) {
		return "Senha ou usuário inválidos!";
	}
	else{
		if (usuario->senha == senha) {
			usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(usuario->id, std::pair<unsigned int, unsigned int>(0, 0)));
			currentUserId = usuario->id;
			return "Logado como " + usuario->email;
		}
	}
	return "Senha ou usuário inválidos!";

}

string Sistema::disconnect(int id) {
		if (currentUserId != 0){
			if (usuariosLogados.find(id) != usuariosLogados.end()) {
				string msg = "Usuário " + this->findUsuarioById(usuariosLogados.find(id)->first)->email + " desconectado! ";
				usuariosLogados.erase(id);
				return msg;
			}
			else{
				return "Usuário não está logado!";
			}
		}
		else{
			return "Nenhum usuário logado, realize o login antes!";
		}
}

string Sistema::create_server(int id, const string nome) {
	if (this->findServidorByNome(nome) != NULL) {
		return "Servidor já existe!";
	}
	this->servidores.push_back(Servidor(id, (Usuario*)this->findUsuarioById(id), nome));
	return "Servidor " + nome + " criado com sucesso!";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	Servidor * server = this->findServidorByNome(nome);
	if (server == NULL) {
		return "Servidor não encontrado!";
	}
	else{
		if(server->id == id){
			server->descricao = descricao;
			return "Descrição alterada com sucesso!";
		}
		else{
			return "Você não tem permissão para alterar esta descrição!";
		}
	}
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	if(this->findServidorByNome(nome) == NULL){
		return "Servidor não encontrado!";
	}
	else{
		if(this->findServidorByNome(nome)->id == id){
			this->findServidorByNome(nome)->codigoConvite = codigo;
			return "Código alterado com sucesso!";
		}
		else{
			return "Você não tem permissão para alterar este código!";
		}
	}
}

string Sistema::list_servers(int id) {
	stringstream ss;
	for(std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it){
		if(it->id == id){
			ss << it->nome << endl;
		}
	}
	return ss.str();
}

string Sistema::remove_server(int id, const string nome) {
	if (this->findServidorByNome(nome) == NULL) {
		return "Servidor não encontrado!";
	}
	else{
		if(this->findServidorByNome(nome)->id == id){
			string msg = "Servidor " + this->findServidorByNome(nome)->nome + " removido com sucesso!";
			this->servidores.erase(std::remove(this->servidores.begin(), this->servidores.end(), *this->findServidorByNome(nome)), this->servidores.end());
			return msg;
		}
		else{
			return "Você não tem permissão para remover este servidor!";
		}
	}
	
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	if (this->findServidorByNome(nome) == NULL) {
		return "Servidor não encontrado!";
	}
	else{
		if (this->findServidorByNome(nome)->codigoConvite == codigo || this->findUsuarioById(id)->id == this->currentUserId)
		{
			this->usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(id, std::pair<unsigned int, unsigned int>(this->findServidorByNome(nome)->id, 0)));
			return "Entrou no servidor " + this->findServidorByNome(nome)->nome;
		}
		else
		{
			return "Código de convite incorreto ou id inválido!";
		}
	}
}

string Sistema::leave_server(int id, const string nome) {
	if (this->findServidorByNome(nome) == NULL) {
		return "Servidor não encontrado!";
	}
	else{
		this->usuariosLogados.erase(id);
		return "Saiu do servidor " + this->findServidorByNome(nome)->nome;
	}
}

string Sistema::list_participants(int id) {
	if (this->usuariosLogados.find(id) == this->usuariosLogados.end()) {
		return "Usuário não tem permissão para realizar a operação ou não está logado!";
	}
	else{
		stringstream ss;
		for(std::vector<Usuario>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it){
			if(it->id == this->usuariosLogados.find(id)->first){
				ss << it->email << endl;
			}
		}
		cout << ss.str();
		return "";
	}
}	

string Sistema::list_channels(int id) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			stringstream ss;
			for (std::vector<CanalTexto>::iterator it2 = it->canaisTexto.begin(); it2 != it->canaisTexto.end(); ++it2) {
				ss << it2->nome << endl;
			}
			std::cout << ss.str();
		}else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
		
	}
	return "Erro ao listar canais!";
}

string Sistema::create_channel(int id, const string nome) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->findCanalByNome(nome) == NULL) {
				it->canaisTexto.push_back(CanalTexto(&idCanalTexto, nome, this->findUsuarioById(id)));
				return "Canal criado com sucesso!";
			}
			else {
				return "Canal já existe!";
			}
		}
		else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
	}
	return "Erro ao criar canal!";
}

string Sistema::remove_channel(int id, const string nome) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->findCanalByNome(nome) == NULL) {
				return "Canal não encontrado!";
			}
			else {
				it->canaisTexto.erase(std::remove(it->canaisTexto.begin(), it->canaisTexto.end(), *this->findCanalByNome(nome)), it->canaisTexto.end());
				return "Canal removido com sucesso!";
			}
		}
		else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
	}	
	return "Erro ao remover canal!";
}

string Sistema::enter_channel(int id, const string nome) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->findCanalByNome(nome) == NULL) {
				return "Canal não encontrado!";
			}
			else {
				this->usuariosLogados.find(id)->second.second = this->findCanalByNome(nome)->id;
				return "O usuário " + this->findUsuarioById(id)->email + " entrou no canal " + this->findCanalByNome(nome)->nome;
			}
		}
		else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
	}
	return "Erro ao entrar no canal!";
}

string Sistema::leave_channel(int id) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->usuariosLogados.find(id)->second.second == 0) {
				return "Você não está em nenhum canal!";
			}
			else {
				this->usuariosLogados.find(id)->second.second = 0;
				return "O usuário " + this->findUsuarioById(id)->email + " saiu do canal " + this->findCanalById(this->usuariosLogados.find(id)->second.second)->nome;
			}
		}
		else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
	}
	return "Erro ao sair do canal!";
}

string Sistema::send_message(int id, const string mensagem) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->usuariosLogados.find(id)->second.second == 0) {
				return "Você não está em nenhum canal!";
			}
			else {
				it->canaisTexto.at(this->usuariosLogados.find(id)->second.second).mensagens.push_back(Mensagem(&idMensagem, this->findUsuarioById(id), mensagem));
			}
		}
		else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
	}
	return "Erro ao enviar mensagem!";
}

string Sistema::list_messages(int id) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->usuariosLogados.find(id)->second.second == 0) {
				return "Você não está em nenhum canal!";
			}
			else {
				std::stringstream ss;
				for (std::vector<Mensagem>::iterator it2 = it->canaisTexto.at(this->usuariosLogados.find(id)->second.second).mensagens.begin(); it2 != it->canaisTexto.at(this->usuariosLogados.find(id)->second.second).mensagens.end(); ++it2) {
					ss << it2->enviadaPor->email << ": " << it2->conteudo << endl;
				}
				std::cout << ss.str();
				return "";
			}
		}
		else
		{
			return "Você não tem permissão para realizar esta operação ou não está em nenhum servidor!";
		}
	}
	return "Você não possúi nenhuma mensagem!";
}

Usuario * Sistema::findUsuarioByEmail(string email){
	for (std::vector<Usuario>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it) {
		if (it->email == email) {
			return &(*it);
		}
	}
	return NULL;	
}

Usuario * Sistema::findUsuarioById(unsigned int id){
	for (std::vector<Usuario>::iterator it = this->usuarios.begin(); it != this->usuarios.end(); ++it) {
		if (it->id == id) {
			return &(*it);
		}
	}
	return NULL;
}

Servidor * Sistema::findServidorByNome(std::string nome){
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->nome == nome) {
			return &(*it);
		}
	}
	return NULL;
}

Servidor * Sistema::findServidorById(unsigned int id){
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == id) {
			return &(*it);
		}
	}
	return NULL;
}

CanalTexto * Sistema::findCanalByNome(std::string nome){
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		for (std::vector<CanalTexto>::iterator it2 = it->canaisTexto.begin(); it2 != it->canaisTexto.end(); ++it2) {
			if (it2->nome == nome) {
				return &(*it2);
			}
		}
	}
	return NULL;
}

CanalTexto * Sistema::findCanalById(unsigned int id){
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		for (std::vector<CanalTexto>::iterator it2 = it->canaisTexto.begin(); it2 != it->canaisTexto.end(); ++it2) {
			if (it2->id == id) {
				return &(*it2);
			}
		}
	}
	return NULL;
}