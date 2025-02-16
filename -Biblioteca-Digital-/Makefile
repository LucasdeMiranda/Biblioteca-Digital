 # Nome do compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -pedantic -std=c99

# Arquivos fonte
SRC = main.c arvore.c fila.c operacoes.c
OBJ = $(SRC:.c=.o)
EXEC = gerenciador

# Regra padrão para compilar tudo
all: $(EXEC)

# Como construir o executável
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Regras para compilar arquivos .c em .o com dependências explícitas
main.o: main.c arvore.h fila.h operacoes.h
	$(CC) $(CFLAGS) -c main.c -o main.o

arvore.o: arvore.c arvore.h
	$(CC) $(CFLAGS) -c arvore.c -o arvore.o

fila.o: fila.c fila.h
	$(CC) $(CFLAGS) -c fila.c -o fila.o

operacoes.o: operacoes.c operacoes.h arvore.h
	$(CC) $(CFLAGS) -c operacoes.c -o operacoes.o

# Limpeza dos arquivos gerados
clean:
	rm -f $(OBJ) $(EXEC)

# Regra para executar o programa
run: $(EXEC)
	./$(EXEC)
