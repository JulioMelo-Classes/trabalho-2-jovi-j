
# Atividade 02 de LP1

## Como compilar

*Necessário ter o cmake instalado.*

```console
mkdir build
cd build
cmake ..
cmake --build .
```

## Para executar
Você pode rodar o sistema e em logo depois digitar os comandos seguidos de ENTER
```console
cd build
./concordo
```

Ou pode criar um arquivo de texto com uma lista de comandos (um por linha) e executar o sistema redirecionando esse arquivo como entrada padrão:
```console
cd build
./concordo < ../data/script_comandos.txt
```

## Funcionalidades Implementadas
* Login/Logout/Criação de Usuário
* CRUD de Servidores
* Entrada/Saída de Servidores
* CRUD de canais
* Tratamento de Erros (Parcialmente)

## Funcionalidades Ausentes
* Entrada/Saída de Canais
* CRUD de mensagens

# Avaliação
## Funcionalidades
- A1.2 ok
- A1.3 25%
Aqui você precisava levar em conta as mensagens/sevidores/canais do usuário
- A1.4 ok
- A2.1 ok
- A2.2 ok
- A2.3 ok
- A2.4 ok
- A2.5 ok
- A2.6 ok
Boa ideia reusar o método leave!
- A2.7 30%
Nesse caso você não deveria ter chamado leave_server do usuário. No nosso formato, um usuário pode estar em vários servidores embora só possa visualizar um por vez. Logo um enter_server não implica em um leave_server.
- A2.8 10%
Nesse caso vou penalizar por você ter violado a restrição do trabalho embora esteja semanticamente correto.
- A2.9 10%
Nesse caso vou penalizar por você ter violado a restrição do trabalho embora esteja semanticamente correto.
- B1.1 10%
Nesse caso vou penalizar por você ter violado a restrição do trabalho embora esteja semanticamente correto.
- B1.2 ok
Embora não funcione, vou considerar
- B1.3 ok
- B1.4 ok
- B1.5 10%
Nesse caso você precisava considerar outros usuários que estivessem no canal removido, além disso você violou a restrição do trabalho.
- B2.1 10%
Nesse caso vou penalizar por você ter violado a restrição do trabalho
- B2.2 10%
Nesse caso vou penalizar por você ter violado a restrição do trabalho

## Classes
- Servidor 80%
Removi 20% por você não ter respeitado a restrição relativa ao retorno de containers 
- Canal 80%
Removi 20% por você não ter respeitado a restrição relativa ao retorno de containers
- Mensagem ok

## Boas Práticas
- Documentação nok
- Testes nok
Aqui a ideia era que você enviasse alguns arquivos de teste validando o que você fez
- Organização 80%
Mistura de implementação inline com implementação em .cpp

## Observações