#ifndef SERVIDOR_H
#define SERVIDOR_H
#include "Usuario.h"
#include <string>
#include <vector>
#include "CanaisTexto.h"
class Servidor {
	public:
		unsigned int id;
		Usuario* dono;
		std::string nome;
		std::string descricao;
		std::string codigoConvite = "";
		std::vector<CanalTexto> canaisTexto;
		std::vector<Usuario*> participantes;

		Servidor(unsigned int id, Usuario* dono, std::string nome);

		bool operator==(const Servidor& s);


};
#endif // !SERVIDOR_H
