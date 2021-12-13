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
	if (this->findUsuarioByEmail(email).id != 0) {
		return "Usuário já existe!	";
	}
	std::cout << "Criando Usuário " << nome << "(" << email << ")" << std::endl;
	Usuario usuario = Usuario(this->idUsuario, nome, email, senha);
	idUsuario++;
	this->usuarios.push_back(usuario);

	return "Usuario criado";
}

std::string Sistema::delete_user (const std::string email, const std::string senha){
	Usuario usuario = this->findUsuarioByEmail(email);
	if (usuario.id == 0) {
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
	if (usuario.id == 0) {
		return "Senha ou usuário inválidos!";
	}
	else{
		if (usuario.senha == senha) {
			usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(usuario.id, std::pair<unsigned int, unsigned int>(0, 0)));
			return "Logado como " + usuario.email;
		}
	}
	return "Senha ou usuário inválidos!";

}

string Sistema::disconnect(int id) {
		if (currentUserId != 0){
			if (usuariosLogados.find(id) != usuariosLogados.end()) {
				string msg = "Usuário " + this->findUsuarioById(usuariosLogados.find(id)->first).email + " desconectado! ";
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

//Pro checkin 2 vou considerar 0.2 uma vez que a lógica faz sentido mas você está usando muitas
//estruturas da forma errada e ainda houveram muitos erros para eu resolver.
string Sistema::create_server(int id, const string nome) {
	if (this->findServidorByNome(nome).id != 0) {
		return "Servidor já existe!";
	}
	Usuario u = this->findUsuarioById(id);
	this->servidores.push_back(Servidor(idServidor, &u, nome));
	idServidor++;
	return "Servidor " + nome + " criado com sucesso!";

}

string Sistema::set_server_desc(int id, const string nome, const string descricao) {
	Servidor server = this->findServidorByNome(nome);
	if (server.id == 0) {
		return "Servidor não encontrado!";
	}
	else{
		Usuario u = this->findUsuarioById(id);
		if(server.dono == &u){
			server.descricao = descricao;
			return "Descrição alterada com sucesso!";
		}
		else{
			return "Você não tem permissão para alterar esta descrição!";
		}
	}
}

string Sistema::set_server_invite_code(int id, const string nome, const string codigo) {
	Servidor server = this->findServidorByNome(nome);
	if (server.id == 0) {
		return "Servidor não encontrado!";
	}
	else{
		Usuario u = this->findUsuarioById(id);
		if(server.dono == &u){
			server.codigoConvite = codigo;
			return "Código de convite alterado com sucesso!";
		}
		else{
			return "Você não tem permissão para alterar o código de convite!";
		}
	}
}

string Sistema::list_servers(int id) {
	if(this->usuariosLogados.find(id) != this->usuariosLogados.end()){
		if (this->usuariosLogados.find(id)->second.first != 0) {
			for (Servidor servidor : this->servidores) {
				cout << servidor.nome << endl;
			}
			return "";
		}
		else{
			return "Você não está em nenhum servidor!";
		}
	}
	else{
		return "Você não está logado!";
	}
}

string Sistema::remove_server(int id, const string nome) {
	if (this->findServidorByNome(nome).id == 0) {
		return "Servidor não encontrado!";
	}
	else{
		if(this->findServidorByNome(nome).id == id){
			// isso aqui só funciona se for possível comparar servidores, sugiro vc tentar usar primeiro find_if e depois o remove.
			this->servidores.erase(std::remove(this->servidores.begin(), this->servidores.end(), this->findServidorByNome(nome)), this->servidores.end());

			return "Servidor removido com sucesso!";
		}
		else{
			return "Você não tem permissão para remover este servidor!";
		}
	}
	
}

string Sistema::enter_server(int id, const string nome, const string codigo) {
	if (this->findServidorByNome(nome).id == 0) {
		return "Servidor não encontrado!";
	}
	else{
		if (this->findServidorByNome(nome).codigoConvite == codigo || this->findUsuarioById(id).id == this->currentUserId)
		{
			//c++ é verboso, mas não tanto assim, vc pode usar make_pair nesse caso, o compilador resolve os tipos pra vc
			//this->usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(id, std::pair<unsigned int, unsigned int>(this->findServidorByNome(nome)->id, 0)));
			this->usuariosLogados.insert(make_pair(id, make_pair(this->findServidorByNome(nome).id, 0)));
			return "Entrando no servidor " + this->findServidorByNome(nome).nome;
		}
		else
		{
			return "Código de convite incorreto ou id inválido!";
		}
	}
}

string Sistema::leave_server(int id, const string nome) {
	if (this->findServidorByNome(nome).id == 0) {
		return "Servidor não encontrado!";
	}
	else{
		this->usuariosLogados.erase(id);
		return "Saiu do servidor " + this->findServidorByNome(nome).nome;
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
			CanalTexto ct = this->findCanalByNome(nome);
			Usuario u = this->findUsuarioById(id);
			if (ct.id == 0) {
				it->canaisTexto.push_back(CanalTexto(idCanalTexto, nome, &u));
				idCanalTexto++;
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
			if (this->findCanalByNome(nome).id == 0) {
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
			if (this->findCanalByNome(nome).id == 0) {
				return "Canal não encontrado!";
			}
			else {
				this->usuariosLogados.find(id)->second.second = this->findCanalByNome(nome).id;
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
		if (u.id == id) {
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
		if(s.id == id){
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
			if(c.id == id){
				return c;
			}
		}
	}
	return CanalTexto(0, "", nullptr);
	
}
