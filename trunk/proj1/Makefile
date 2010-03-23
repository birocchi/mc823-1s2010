# Dependências gerais
all: client server

# Cliente
client: data_access.o client.o
	gcc -ggdb -Wall data_access.o client.o -o client

client.o: client.c data_access.h
	gcc -ggdb -Wall -c client.c

# Servidor
server: data_access.o server.o
	gcc -ggdb -Wall data_access.o server.o -o server

server.o: server.c data_access.h
	gcc -ggdb -Wall -c server.c

# Biblioteca
data_access.o: data_access.c data_access.h
	gcc -ggdb -Wall -c data_access.c

# Clean
clean:
	rm *.o client server
