# Variáveis
CC = gcc
CC_FLAGS = -ggdb -Wall


# Dependências gerais
all: client server

# Cliente
client: data_access.o client.o
	$(CC) $(CC_FLAGS) data_access.o client.o -o client

client.o: client.c data_access.h
	$(CC) $(CC_FLAGS) -c client.c

# Servidor
server: data_access.o server.o
	$(CC) $(CC_FLAGS) -pthread data_access.o server.o -o server

server.o: server.c data_access.h
	$(CC) $(CC_FLAGS) -pthread -c server.c

# Biblioteca
data_access.o: data_access.c data_access.h
	$(CC) $(CC_FLAGS) -c data_access.c

# Clean
clean:
	rm *.o client server
