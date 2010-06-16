# Variáveis
CC = gcc
CC_FLAGS = -ggdb -Wall


# Dependências gerais
all: classpath bd geral

# concatena :./sqlitejdbc.jar ao Classpath
classpath:
	CLASSPATH=$(CLASSPATH):./sqlitejdbc-v056.jar

# Compila as classes do banco de dados
bd:
	javac src/bd/*.java -d bin/

geral:
	cd bin;	javac ../src/*.java -d ./

# Clean
# remove os arquivos compilados silenciosamente
clean:
	rm -rf bin/*.class bin/bd/*.class > /dev/null 2> /dev/null
