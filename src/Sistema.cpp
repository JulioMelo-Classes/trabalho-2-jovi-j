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
			//isso aqui só funciona se for possível comparar usuários, sugiro vc usar primeiro find_if e depois erase
			//this->usuarios.erase(std::remove(this->usuarios.begin(), this->usuarios.end(), *usuario), this->usuarios.end());
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
				string msg = "Desconectando usuário " + this->findUsuarioById(usuariosLogados.find(id)->first)->email;
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
	return "Servidor criado com sucesso!";

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
			//isso aqui só funciona se for possível comparar servidores, sugiro vc tentar usar primeiro find_if e depois o remove.
			//this->servidores.erase(std::remove(this->servidores.begin(), this->servidores.end(), *this->findServidorByNome(nome)), this->servidores.end());
			return "Servidor removido com sucesso!";
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
			//c++ é verboso, mas não tanto assim, vc pode usar make_pair nesse caso, o compilador resolve os tipos pra vc
			//this->usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(id, std::pair<unsigned int, unsigned int>(this->findServidorByNome(nome)->id, 0)));
			this->usuariosLogados.insert(make_pair(id, make_pair(this->findServidorByNome(nome)->id, 0)));
			return "Entrando no servidor " + this->findServidorByNome(nome)->nome;
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
		return "Saindo do servidor " + this->findServidorByNome(nome)->nome;
	}
}

string Sistema::list_participants(int id) {
	return "list_participants NÃO IMPLEMENTADO";
}

string Sistema::list_channels(int id) {
	return "list_channels NÃO IMPLEMENTADO";
}

string Sistema::create_channel(int id, const string nome) {
	return "create_channel NÃO IMPLEMENTADO";
}

string Sistema::remove_channel(int id, const string nome) {
	return "remove_channel NÃO IMPLEMENTADO";
}

string Sistema::enter_channel(int id, const string nome) {
	return "enter_channel NÃO IMPLEMENTADO";
}

string Sistema::leave_channel(int id) {
	return "leave_channel NÃO IMPLEMENTADO";
}

string Sistema::send_message(int id, const string mensagem) {
	return "send_message NÃO IMPLEMENTADO";
}

string Sistema::list_messages(int id) {
	return "list_messages NÃO IMPLEMENTADO";
}

//essas funções find estão todas erradas em termos semanticos
//uma vez que vc retornar o endereço da variável usuário ela vai ser destruída por sair do escopo da função
//da forma como vc está armazenando vc pode retornar um iterator ou uma cópia
Usuario * Sistema::findUsuarioByEmail(string email){
	for (Usuario usuario : this->usuarios) {
		if (usuario.email == email) {
			return &usuario;
		}
	}
	return NULL;
}

Usuario * Sistema::findUsuarioById(unsigned int id){
	for (Usuario usuario : this->usuarios) {
		if (usuario.id == id) {
			return &usuario;
		}
	}
	return NULL;
}

Servidor * Sistema::findServidorByNome(std::string nome){
	for (Servidor servidor : this->servidores) {
		if (servidor.nome == nome) {
			return &servidor;
		}
	}
	return NULL;
}