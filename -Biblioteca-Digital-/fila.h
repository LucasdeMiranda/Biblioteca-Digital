#ifndef FILA_H
#define FILA_H
typedef struct tm *data;
typedef struct
{
    char nomepessoa[300];
    data dataregistro;
    char titulolivro[300];
} Registro;

typedef struct Registroencadeado *apontador;
typedef struct Registroencadeado
{
    Registro registro;
    apontador prox;
} Registroencadeado;

typedef struct
{
    apontador frente, tras;
} Fila;
void inicializarfila(Fila *fila);
void enfileirar(Fila *fila, Registro novoregistro);
void desenfileirar(Fila *fila, Registro *registro);
void imprimirfila(Fila *fila);

#endif  