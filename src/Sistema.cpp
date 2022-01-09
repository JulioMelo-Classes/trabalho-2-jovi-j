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

//Pro checkin 1 estaria quase ok, faltando só gerar automaticamente o id.
string Sistema::create_user (const string email, const string senha, const string nome) {
	if (this->findUsuarioByEmail(email).getId() != 0) {
		return "Usuário já existe!	";
	}
	std::cout << "Criando Usuário " << nome << "(" << email << ")" << std::endl;
	Usuario usuario = Usuario(this->idUsuario, nome, email, senha);
	this->idUsuario++;
	this->usuarios.push_back(usuario);

	return "Usuario criado";
}

std::string Sistema::delete_user (const std::string email, const std::string senha){
	Usuario usuario = this->findUsuarioByEmail(email);
	if (usuario.getId() == 0) {
		return "Usuario não cadastrado!";
	}
	else{
		if (usuario.senha == senha) {
			//isso aqui só funciona se for possível comparar usuários, sugiro vc usar primeiro find_if e depois erase
			this->usuarios.erase(std::remove(this->usuarios.begin(), this->usuarios.end(), usuario), this->usuarios.end());
			return "Usuario deletado";
		}
		else{
			return "Senha incorreta";
		}
	}
}

string Sistema::login(const string email, const string senha) {
	Usuario usuario = this->findUsuarioByEmail(email);
	if (usuario.getId() == 0) {
		return "Senha ou usuário inválidos!";
	}
	else{
		if (usuario.senha == senha) {
			usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(usuario.getId(), std::pair<unsigned int, unsigned int>(0, 0)));
			return "Logado como " + usuario.email;
		}
	}
	return "Senha ou usuário inválidos!";

}

string Sistema::disconnect(int id){
	if (this->isUsuarioLogado(id)){
		string msg = "Usuário " + this->findUsuarioById(usuariosLogados.find(id)->first).email + " desconectado! ";
		usuariosLogados.erase(id);
		return msg;
	}
	else{
		return "Usuário não está logado!";
	}
}

//Pro checkin 2 vou considerar 0.2 uma vez que a lógica faz sentido mas você está usando muitas
//estruturas da forma errada e ainda houveram muitos erros para eu resolver.
string Sistema::create_server(int id, const string nome) {
	if (this->findServidorByNome(nome).getId() != 0) {
		return "Um Servidor com este nome já existe!";
	}
	Usuario u = this->findUsuarioById(id);
	if (u.getId() == 0) {
		return "Usuário não cadastrado!";
	}
	if (this->isUsuarioLogado(id)) {
		Servidor servidor = Servidor(this->idServidor, &u, nome);
		this->idServidor++;
		this->servidores.push_back(servidor);
		return "Servidor " + nome + " criado com sucesso!";
	}else{
		return "Usuário não está logado!";
	}
}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	Servidor server = this->findServidorByNome(nome);
	if (server.getId() == 0) {
		return "Servidor não encontrado!";
	}
	else{
		Usuario u = this->findUsuarioById(id);
		if (u.getId() == 0) {
			return "Usuário não cadastrado!";
		}
		if(this->isUsuarioLogado(id)){
			if(server.dono->id == u.getId()){
				server.descricao = descricao;
				return "Descrição alterada com sucesso!";
			}
			else{
				return "Você não tem permissão para alterar esta descrição pois você não é dono do servidor!";
			}
		}	
		else{
			return "Usuário não está logado!";
		}
	}
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	Servidor server = this->findServidorByNome(nome);
	if (server.getId() == 0) {
		return "Servidor não encontrado!";
	}
	else{
		Usuario u = this->findUsuarioById(id);
		if (u.getId() == 0) {
			return "Usuário não cadastrado!";
		}
		if(this->isUsuarioLogado(id)){
			if(server.dono->id == u.getId()){
				server.codigoConvite = codigo;
				return "Código alterado com sucesso!";
			}
			else{
				return "Você não tem permissão para alterar o código de convite pois você não é dono do servidor!";
			}
		}	
		else{
			return "Usuário não está logado!";
		}
	}
}

string Sistema::list_servers(int id){
	if (this->isUsuarioLogado(id)){
		for (Servidor servidor : this->servidores){
			cout << servidor.nome << endl;
		}
		return "";
	}
	else{
		return "Você não está logado!";
	}
}

string Sistema::remove_server(int id, const string nome) {
	Servidor servidor = this->findServidorByNome(nome);
	if (servidor.getId() == 0) {
		return "Servidor não encontrado!";
	}
	else{
		if (this->isUsuarioLogado(id)){
			if (servidor.dono->id == id){
				for(Usuario *usuario : servidor.participantes){
					if(isUsuarioOnServidor(usuario->id, servidor.getId())){
						this->leave_server(usuario->id, servidor.nome);
					}
				}
				this->servidores.erase(std::remove(this->servidores.begin(), this->servidores.end(), servidor), this->servidores.end());
				return "Servidor removido com sucesso!";
			}
			else{
				return "Você não tem permissão para remover este servidor!";
			}
		}else{
			return "Usuário não está logado!";
		}
	}
	
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	Servidor servidor = this->findServidorByNome(nome);
	if (servidor.getId() == 0) {
		return "Servidor não encontrado!";
	}
	else{
		if (servidor.codigoConvite == codigo){
			if (this->isUsuarioLogado(id)){
				if (this->isUsuarioOnServidor(id, servidor.getId())){
					return "O usuário já está nesse servidor!";
				}
				this->usuariosLogados.insert(make_pair(id, make_pair(servidor.getId(), 0)));
				// se o usuário não estiver no vector servidor.participantes, então adiciona ele
				if(std::find(servidor.participantes.begin(), servidor.participantes.end(), &this->findUsuarioById(id)) == servidor.participantes.end()){
					servidor.participantes.push_back(&this->findUsuarioById(id));
				}
				
				return "Entrando no servidor " + servidor.nome;
			}
			else{
				return "Usuário não está logado!";
			}
		}
		else{
			return "Código de convite incorreto!";
		}
	}
}

string Sistema::leave_server(int id, const string nome) {
	Servidor servidor = this->findServidorByNome(nome);
	if (servidor.getId() == 0){
		return "Servidor não encontrado!";
	}
	if (!this->isUsuarioLogado(id)){
		return "Usuário não está logado!";
	}
	if (this->isUsuarioOnServidor(id, servidor.getId())){
		this->usuariosLogados.find(id)->second.first = 0;
		this->usuariosLogados.find(id)->second.second = 0;
		// remove o usuario do vector servidor.participantes
		servidor.participantes.erase(std::remove(servidor.participantes.begin(), servidor.participantes.end(), &this->findUsuarioById(id)), servidor.participantes.end());
		return "Saindo do servidor " + nome;
	}
	else{
		return "O usuário não está nesse servidor!";
	}
}

string Sistema::list_participants(int id){
	if (this->isUsuarioLogado(id)){
		return "Usuário não está logado!";
	}
	else{
		Servidor servidor = this->findServidorById(this->usuariosLogados[id].first);
		if (servidor.getId() == 0){
			return "Servidor não encontrado!";
		}
		else{
			for (Usuario *usuario : servidor.participantes){
				cout << usuario->nome << endl;
			}
		}
	}
	return "";
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
	if (!this->isUsuarioLogado(id)){
		return "Usuário não está logado!";
	}
	else{
		Servidor servidor = this->findServidorById(this->usuariosLogados.find(id)->first);
		if (servidor.getId() == 0){
			return "Erro, o usuário não está em nenhum servidor!";
		}
		else{
			for (CanalTexto canal : servidor.canaisTexto){
				if (canal.nome == nome){
					return "Erro, o servidor já possui um canal com esse nome!";
				}
			}
			CanalTexto canal = CanalTexto(this->idCanalTexto, nome, &this->findUsuarioById(id));
			servidor.canaisTexto.push_back(canal);
			return "Canal de texto " + canal.nome + " criado com sucesso!";
		}
	}
}

string Sistema::remove_channel(int id, const string nome) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->id == this->usuariosLogados.find(id)->first) {
			if (this->findCanalByNome(nome).getId() == 0) {
				return "Canal não encontrado!";
			}
			else {
				it->canaisTexto.erase(std::remove(it->canaisTexto.begin(), it->canaisTexto.end(), this->findCanalByNome(nome)), it->canaisTexto.end());
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
			if (this->findCanalByNome(nome).getId() == 0) {
				return "Canal não encontrado!";
			}
			else {
				this->usuariosLogados.find(id)->second.second = this->findCanalByNome(nome).getId();
				return "O usuário " + this->findUsuarioById(id).email + " entrou no canal " + this->findCanalByNome(nome).nome;
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
				return "O usuário " + this->findUsuarioById(id).email + " saiu do canal " + this->findCanalById(this->usuariosLogados.find(id)->second.second).nome;
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
				Usuario u = this->findUsuarioById(id);
				it->canaisTexto.at(this->usuariosLogados.find(id)->second.second).mensagens.push_back(Mensagem(idMensagem, &u , mensagem));
				idMensagem++;
				return "Mensagem enviada com sucesso!";
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

//essas funções find estão todas erradas em termos semanticos
//uma vez que vc retornar o endereço da variável usuário ela vai ser destruída por sair do escopo da função
//da forma como vc está armazenando vc pode retornar um iterator ou uma cópia
Usuario Sistema::findUsuarioByEmail(string email){
	for (Usuario u : this->usuarios) {
		if (u.email == email) {
			return u;
		}
	}
	return Usuario(0, "", "", "");
}

Usuario Sistema::findUsuarioById(unsigned int id){
	for (Usuario u : this->usuarios) {
		if (u.getId() == id) {
			return u;
		}
	}
	return Usuario(0, "", "", "");
}

Servidor Sistema::findServidorByNome(std::string nome){
	for (Servidor s : this->servidores) {
		if (s.nome == nome) {
			return s;
		}
	}
	return Servidor(0, nullptr, "");
}

Servidor Sistema::findServidorById(unsigned int id){
	for(Servidor s : this->servidores){
		if(s.getId() == id){
			return s;
		}
	}
	return Servidor(0, nullptr, "");
}

CanalTexto Sistema::findCanalByNome(std::string nome){
	for(Servidor s : this->servidores){
		for(CanalTexto c : s.canaisTexto){
			if(c.nome == nome){
				return c;
			}
		}
	}
	return CanalTexto(0, "", nullptr);
}

CanalTexto Sistema::findCanalById(unsigned int id){
	for(Servidor s : this->servidores){
		for(CanalTexto c : s.canaisTexto){
			if(c.getId() == id){
				return c;
			}
		}
	}
	return CanalTexto(0, "", nullptr);
	
}

bool Sistema::isUsuarioLogado(unsigned int id){
	return this->usuariosLogados.find(id) != this->usuariosLogados.end();
}

bool Sistema::isUsuarioOnServidor(unsigned int id, unsigned int idServidor){
	return this->usuariosLogados.find(id)->second.first == idServidor;
}