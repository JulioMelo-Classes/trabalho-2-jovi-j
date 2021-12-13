#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <vector>

class Usuario{
public:
	unsigned int id;
	std::string nome;
	std::string email;
	std::string senha;
	
	Usuario(unsigned int id, std::string nome, std::string email, std::string senha);

	bool operator==(const Usuario &u1);

};


#endif // !USUARIO_H


