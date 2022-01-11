#ifndef CANALTEXTO_H
#define CANALTEXTO_H
#include "Mensagem.h"
#include "Usuario.h"
#include <string>
#include <vector>

class CanalTexto {
	private:
		unsigned int id;
		std::string nome;
		Usuario* dono;
		std::vector<Mensagem> mensagens;
	public:

		CanalTexto(unsigned int id, std::string nome, Usuario* dono){
			this->id = id;
			this->nome = nome;
			this->dono = dono;
		}

		unsigned int getId();
		void setId(unsigned int id);

		std::string getNome();
		void setNome(std::string nome);

		Usuario* getDono();
		void setDono(Usuario* dono);
		
		std::vector<Mensagem> getMensagens();
		void setMensagens(std::vector<Mensagem> mensagens);
		void addMensagem(Mensagem mensagem);
		

		bool operator==(const CanalTexto &c){
			return this->id == c.id;
		}
};

#endif // !CANALTEXTO