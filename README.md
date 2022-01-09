# Base para a atividade 02 de LP1

Use esse esqueleto de classes para iniciar a terceira atividade.

Existe um executor que faz a interpretação dos comandos e executa o método correto do sistema.

## Para compilar

Com makefiles:
```console
mkdir build
make
```

Com cmake:
```console
mkdir build
cd build
cmake ..
cmake --build .
```

Escolha uma das duas formas de build e ignore a outra.

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


## Testes

teste1.txt - parte de login, conexão, desconexão e tratamento de comandos errados.

teste2.txt - criação de servidores, tratamento de erros na criação, modificação e listagem de servidores.

teste3.txt - criação, entrada e 
