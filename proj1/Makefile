# Variáveis
CC = gcc
CC_FLAGS = -ggdb -Wall


# Dependências gerais
all: client server relatorio

# Cliente
client: data_access.o internet.o client.o
	$(CC) $(CC_FLAGS) data_access.o internet.o client.o -o client

client.o: client.c data_access.h internet.h defines.h
	$(CC) $(CC_FLAGS) -c client.c

# Servidor
server: data_access.o internet.o server.o
	$(CC) $(CC_FLAGS) -pthread data_access.o internet.o server.o -o server

server.o: server.c data_access.h internet.h defines.h
	$(CC) $(CC_FLAGS) -pthread -c server.c

# Bibliotecas
data_access.o: data_access.c data_access.h defines.h
	$(CC) $(CC_FLAGS) -c data_access.c

internet.o: internet.c internet.h defines.h
	$(CC) $(CC_FLAGS) -c internet.c


# Relatório (LaTeX)
relatorio:
	pdflatex relatorio.tex

# Clean
clean:
	rm *.o client server
	rm *.aux *.toc *.pdf *.log
