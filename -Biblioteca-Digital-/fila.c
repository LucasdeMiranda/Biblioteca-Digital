#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "fila.h"

void inicializarfila(Fila *fila)
{
    fila->frente = NULL;
    fila->tras = NULL;
}
void enfileirar(Fila *fila, Registro novoregistro)
{
    apontador novoNo = (apontador)malloc(sizeof(Registroencadeado));
    if (novoNo == NULL)
    {
        printf("Erro ao alocar memória.\n");
        return;
    }
    novoNo->registro = novoregistro;
    novoNo->prox = NULL;

    if (fila->tras == NULL)
    {
        fila->frente = fila->tras = novoNo;
    }
    else
    {
        fila->tras->prox = novoNo;//antigo tras aponta para o novo no 
        fila->tras = novoNo; //novo passa a ser o ultimo
    }
}

void desenfileirar(Fila *fila, Registro *registro)
{
    if (fila->frente == NULL)
    {
        printf("Fila vazia.\n");
        return;
    }
    apontador temp = fila->frente;
    *registro = temp->registro;
    fila->frente = fila->frente->prox;//desenfileira um a a um 
    if (fila->frente == NULL)
    {
        fila->tras = NULL;
    }
    free(temp);
}
void imprimirfila(Fila *fila)
{
    apontador atual = fila->frente;
    while (atual != NULL)
    {
        printf("%s, %s %d/%d/%d  %d:%d\n",
               atual->registro.nomepessoa,
               atual->registro.titulolivro,
               atual->registro.dataregistro->tm_mday,
               atual->registro.dataregistro->tm_mon + 1,     // ajusta o mês para 1-12
               atual->registro.dataregistro->tm_year + 1900, // ajusta o ano para o formato correto
               atual->registro.dataregistro->tm_hour,
               atual->registro.dataregistro->tm_min);
        atual = atual->prox;
    }
}