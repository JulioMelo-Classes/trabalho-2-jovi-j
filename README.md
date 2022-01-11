
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
