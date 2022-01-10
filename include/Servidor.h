#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "Usuario.h"
#include <string>
#include <vector>
#include "CanalTexto.h"
class Servidor {
	private:
		unsigned int id;
		Usuario* dono;
		std::string nome;
		std::string descricao;
		std::string codigoConvite = "";
		std::vector<CanalTexto> canaisTexto;
		std::vector<Usuario*> participantes;

	public:
		Servidor(unsigned int id, Usuario* dono, std::string nome);

		unsigned int getId();
		void setId(unsigned int id);

		Usuario* getDono();
		void setDono(Usuario* dono);

		std::string getNome();
		void setNome(std::string nome);

		std::string getDescricao();
		void setDescricao(std::string descricao);

		std::string getCodigoConvite();
		void setCodigoConvite(std::string codigoConvite);

		std::vector<CanalTexto> getCanaisTexto();
		void setCanalTexto(CanalTexto canalTexto);
		void setCanaisTexto(std::vector<CanalTexto> canaisTexto);
		
		std::vector<Usuario*> getParticipantes();
		void setParticipante(Usuario* participante);
		void setParticipantes(std::vector<Usuario*> participantes);

		bool operator==(const Servidor& s);


};
#endif // !SERVIDOR_H
