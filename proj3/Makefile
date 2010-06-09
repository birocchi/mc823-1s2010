# Variáveis
CC = gcc
CC_FLAGS = -ggdb -Wall


# Dependências gerais
all: classpath bd servidor

# concatena :./sqlitejdbc.jar ao Classpath
classpath:
	CLASSPATH=$(CLASSPATH):./sqlitejdbc-v056.jar:./bin/:./bin/bd

# Compila as classes do banco de dados
bd:
	javac src/bd/*.java -d bin/

servidor:
	javac src/Servidor.java -d bin/

# Clean
clean:
	rm -rf bin/*.class
