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
	if (this->findUsuarioByEmail(email).getNome() != "") {
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
	if (usuario.getNome() == "") {
		return "Usuario não cadastrado!";
	}
	else{
		if (usuario.getSenha() == senha) {
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
	if (usuario.getNome() == "") {
		return "Senha ou usuário inválidos!";
	}
	else{
		if (usuario.getSenha() == senha) {
			usuariosLogados.insert(std::map<int, std::pair<unsigned int, unsigned int>>::value_type(usuario.getId(), std::pair<unsigned int, unsigned int>(0, 0)));
			return "Logado como " + usuario.getEmail();
		}
	}
	return "Senha ou usuário inválidos!";

}

string Sistema::disconnect(int id){
	if (this->isUsuarioLogado(id)){
		string msg = "Usuário " + this->findUsuarioById(usuariosLogados.find(id)->first).getEmail() + " desconectado! ";
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
	if (this->findServidorByNome(nome).getNome() != "") {
		return "Um Servidor com este nome já existe!";
	}
	Usuario u = this->findUsuarioById(id);
	if (u.getNome() == "") {
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
	if (server.getNome() == "") {
		return "Servidor não encontrado!";
	}
	else{
		Usuario u = this->findUsuarioById(id);
		if (u.getNome() == "") {
			return "Usuário não cadastrado!";
		}
		if(this->isUsuarioLogado(id)){
			if(server.getDono()->getId() == u.getId()){
				server.setDescricao(descricao);
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
	if (server.getNome() == "") {
		return "Servidor não encontrado!";
	}
	else{
		Usuario u = this->findUsuarioById(id);
		if (u.getNome() == "") {
			return "Usuário não cadastrado!";
		}
		if(this->isUsuarioLogado(id)){
			if(server.getDono()->getId() == u.getId()){
				server.setCodigoConvite(codigo);
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
			cout << servidor.getNome() << endl;
		}
		return "";
	}
	else{
		return "Você não está logado!";
	}
}

string Sistema::remove_server(int id, const string nome) {
	Servidor servidor = this->findServidorByNome(nome);
	if (servidor.getNome() == "") {
		return "Servidor não encontrado!";
	}
	else{
		if (this->isUsuarioLogado(id)){
			if (servidor.getDono()->getId() == id){
				for(Usuario *usuario : servidor.getParticipantes()){
					if(isUsuarioOnServidor(usuario->getId(), servidor.getId())){
						this->leave_server(usuario->getId(), servidor.getNome());
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
	if (servidor.getNome() == "") {
		return "Servidor não encontrado!";
	}
	else{
		if (servidor.getCodigoConvite() == codigo){
			if (this->isUsuarioLogado(id)){
				if (this->isUsuarioOnServidor(id, servidor.getId())){
					return "O usuário já está nesse servidor!";
				}
				this->usuariosLogados.insert(make_pair(id, make_pair(servidor.getId(), 0)));
				Usuario usuario = this->findUsuarioById(id);
				if(std::find(servidor.getParticipantes().begin(), servidor.getParticipantes().end(), &usuario) == servidor.getParticipantes().end()){
					servidor.setParticipante(&usuario);
				}
				
				return "Entrando no servidor " + servidor.getNome();
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
	Usuario usuario = this->findUsuarioById(id);
	if (servidor.getNome() == ""){
		return "Servidor não encontrado!";
	}
	if (!this->isUsuarioLogado(id)){
		return "Usuário não está logado!";
	}
	if (this->isUsuarioOnServidor(id, servidor.getId())){
		this->usuariosLogados.find(id)->second.first = 0;
		this->usuariosLogados.find(id)->second.second = 0;
		std::vector all_parts = servidor.getParticipantes();
		all_parts.erase(std::remove(all_parts.begin(), all_parts.end(), &usuario), all_parts.end());
		servidor.setParticipantes(all_parts);
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
		if (servidor.getNome() == ""){
			return "Servidor não encontrado!";
		}
		else{
			for (Usuario *usuario : servidor.getParticipantes()){
				cout << usuario->getNome() << endl;
			}
		}
	}
	return "";
}

string Sistema::list_channels(int id) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->getId() == this->usuariosLogados.find(id)->first) {
			stringstream ss;
			for (std::vector<CanalTexto>::iterator it2 = it->getCanaisTexto().begin(); it2 != it->getCanaisTexto().end(); ++it2) {
				ss << it2->getNome() << endl;
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
		if (servidor.getNome() == ""){
			return "Erro, o usuário não está em nenhum servidor!";
		}
		else{
			for (CanalTexto canal : servidor.getCanaisTexto()){
				if (canal.getNome() == nome){
					return "Erro, o servidor já possui um canal com esse nome!";
				}
			}
			Usuario usuario = this->findUsuarioById(id);
			CanalTexto canal = CanalTexto(this->idCanalTexto, nome, &usuario);
			servidor.setCanalTexto(canal);
			return "Canal de texto " + canal.getNome() + " criado com sucesso!";
		}
	}
}

string Sistema::remove_channel(int id, const string nome) {
	for (std::vector<Servidor>::iterator it = this->servidores.begin(); it != this->servidores.end(); ++it) {
		if (it->getId() == this->usuariosLogados.find(id)->first) {
			if (this->findCanalByNome(nome).getNome() == "") {
				return "Canal não encontrado!";
			}
			else {
				std::vector<CanalTexto> canais = it->getCanaisTexto();
				canais.erase(std::remove(canais.begin(), canais.end(), this->findCanalByNome(nome)), canais.end());
				it->setCanaisTexto(canais);
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
		if (it->getId() == this->usuariosLogados.find(id)->first) {
			if (this->findCanalByNome(nome).getNome() == "") {
				return "Canal não encontrado!";
			}
			else {
				this->usuariosLogados.find(id)->second.second = this->findCanalByNome(nome).getId();
				return "O usuário " + this->findUsuarioById(id).getEmail() + " entrou no canal " + this->findCanalByNome(nome).getNome();
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
		if (it->getId() == this->usuariosLogados.find(id)->first) {
			if (this->usuariosLogados.find(id)->second.second == 0) {
				return "Você não está em nenhum canal!";
			}
			else {
				this->usuariosLogados.find(id)->second.second = 0;
				return "O usuário " + this->findUsuarioById(id).getEmail() + " saiu do canal " + this->findCanalById(this->usuariosLogados.find(id)->second.second).getNome();
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
		if (it->getId() == this->usuariosLogados.find(id)->first) {
			if (this->usuariosLogados.find(id)->second.second == 0) {
				return "Você não está em nenhum canal!";
			}
			else {
				Usuario u = this->findUsuarioById(id);
				std::vector<CanalTexto> canais = it->getCanaisTexto();
				CanalTexto c = canais.at(this->usuariosLogados.find(id)->second.second);
				c.setMensagem(Mensagem(idMensagem, &u , mensagem));
				this->idMensagem++;
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
		if (it->getId() == this->usuariosLogados.find(id)->first) {
			if (this->usuariosLogados.find(id)->second.second == 0) {
				return "Você não está em nenhum canal!";
			}
			else {
				std::stringstream ss;
				for (std::vector<Mensagem>::iterator it2 = it->getCanaisTexto().at(this->usuariosLogados.find(id)->second.second).getMensagens().begin(); it2 != it->getCanaisTexto().at(this->usuariosLogados.find(id)->second.second).getMensagens().end(); ++it2) {
					ss << it2->getEnviadaPor()->getEmail() << ": " << it2->getConteudo() << endl;
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
		if (u.getEmail() == email) {
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
		if (s.getNome() == nome) {
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
		for(CanalTexto c : s.getCanaisTexto()){
			if(c.getNome() == nome){
				return c;
			}
		}
	}
	return CanalTexto(0, "", nullptr);
}

CanalTexto Sistema::findCanalById(unsigned int id){
	for(Servidor s : this->servidores){
		for(CanalTexto c : s.getCanaisTexto()){
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