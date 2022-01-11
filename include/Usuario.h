#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include <vector>

class Usuario{
private:
	unsigned int id;
	std::string nome;
	std::string email;
	std::string senha;

public:
	Usuario(unsigned int id, std::string nome, std::string email, std::string senha);

	unsigned int getId();
	void setId(unsigned int id);

	std::string getNome();
	void setNome(std::string nome);

	std::string getEmail();
	void setEmail(std::string email);

	std::string getSenha();
	void setSenha(std::string senha);
	
	bool operator==(const Usuario &u1);

};


#endif // !USUARIO_H


