#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "arvore.h"

int altura(apont no)
{
    if (no == NULL)
        return 0;
    int alturaesquerda = altura(no->esq);
    int alturadireita = altura(no->dir);
    //condição ? verdadeiro : falso;
    //retorna a maior sub árvore
    return (alturaesquerda > alturadireita ? alturaesquerda : alturadireita) + 1; //+1 é para contar o nó atual
}

int calculabalanceamento(apont no)
{
    if (no == NULL)
    {
        return 0;
    }
    return altura(no->esq) - altura(no->dir); // retorna a diferença das sub árvore esquerda do nó - a direita
}
void balancear(apont *no)
{
    int b = calculabalanceamento(*no);
    if (b > 1)
    {
         balanceioesquerdo(no); //mais pesado no lado esquerdo
    }
    else if (b < -1)
    {
        balanceiodireito(no);
    }
}
void balanceioesquerdo(apont *no)
{
    int esq = calculabalanceamento((*no)->esq); //calcula o sinal do filho esquerdo do nó se tiver positivo uma rotação simples funciona
    if (esq > 0)  //desbalanceada em linha reta 
    {
        rotacaodireita(no); 
    }
    else
    { // rotações dupla a direita
        rotacaoesquerda(&(*no)->esq); //tem sinal diferente do nó pai
        rotacaodireita(no);
    }
}

void balanceiodireito(apont *no)
{
    int dir = calculabalanceamento((*no)->dir);  //calcula o sinal do filho direito do nó se tiver negativo uma rotação simples funciona
    if (dir < 0)
    {
        rotacaoesquerda(no);
    }
    else
    {
         // rotações dupla a esquerda
        rotacaodireita(&(*no)->dir); 
        rotacaoesquerda(no);
    }
}

void rotacaodireita(apont *no)
{
    apont aux = (*no)->esq;
    (*no)->esq = aux->dir;
    aux->dir = *no;
    *no = aux;
}
void rotacaoesquerda(apont *no)
{
    apont aux = (*no)->dir;
    (*no)->dir = aux->esq;
    aux->esq = *no;
    *no = aux;
}

void inicializaarvore(apont *arvoreano, apont *arvoreautor, apont *arvoretitulo)
{
    *arvoreano = NULL; //como cada arvore organiza por um criterio diferente precisa de ponteiros diferentes
    *arvoreautor = NULL;
    *arvoretitulo = NULL;
}

void inserirporano(Livro *novo, apont *no)
{
    if (*no == NULL)
    {
        *no = (apont)malloc(sizeof(No));
        if (*no == NULL)
        {
            printf("Erro ao alocar memória para a árvore.\n");
            return;
        }
        (*no)->livros = (Livro **)malloc(sizeof(Livro *));
        if ((*no)->livros == NULL)
        {
            printf("Erro ao alocar memória para o vetor de livros.\n");
            free(*no);
            return;
        }
        (*no)->livros[0] = novo;
        (*no)->numlivros = 1;
        (*no)->esq = NULL;
        (*no)->dir = NULL;
        return;
    }

    // o ano do primeiro livro do vetor é que dita o ano do nó
    if (novo->ano > (*no)->livros[0]->ano)
    {
        inserirporano(novo, &(*no)->dir);
    }
    else if (novo->ano < (*no)->livros[0]->ano)
    {
        inserirporano(novo, &(*no)->esq);
    }

    else if (novo->ano == (*no)->livros[0]->ano && novo->isbn != (*no)->livros[0]->isbn) //para que o primeiro livro não seja inserido duas vezes
    {
        (*no)->livros = (Livro **)realloc((*no)->livros, ((*no)->numlivros + 1) * sizeof(Livro *));
        if ((*no)->livros == NULL)
        {
            printf("Erro.\n");
            return;
        }
        (*no)->livros[(*no)->numlivros] = novo;//começa no 1 porque posição 0 ja foi preenchida no inicio
        (*no)->numlivros++;
    }
    balancear(no);
}
void inserirporautor(Livro *novo, apont *no)
{
    if (*no == NULL)
    {
        *no = (apont)malloc(sizeof(No));
        if (*no == NULL)
        {
            printf("Erro ao alocar memória para a árvore.\n");
            return;
        }
        (*no)->livros = (Livro **)malloc(sizeof(Livro *));
        if ((*no)->livros == NULL)
        {
            printf("Erro ao alocar memória para o vetor de livros.\n");
            free(*no);
            return;
        }
        (*no)->livros[0] = novo;
        (*no)->numlivros = 1;
        (*no)->esq = NULL;
        (*no)->dir = NULL;
    }
    if (strcmp(novo->autor, (*no)->livros[0]->autor) < 0) //compara  a primeira string com a primeira 
    {
        inserirporautor(novo, &(*no)->esq);
    }
    else if (strcmp(novo->autor, (*no)->livros[0]->autor) > 0)
    {
        inserirporautor(novo, &(*no)->dir);
    }
    else if (strcmp(novo->autor, (*no)->livros[0]->autor) == 0 && (*no)->livros[0]->isbn != novo->isbn)
    {
        (*no)->livros = (Livro **)realloc((*no)->livros, ((*no)->numlivros + 1) * sizeof(Livro *));
        if ((*no)->livros == NULL)
        {
            printf("Erro.\n");
            return;
        }
        (*no)->livros[(*no)->numlivros] = novo;
        (*no)->numlivros++;
    }
    balancear(no);
}

void inserirportitulo(Livro *novo, apont *no)
{
    if (*no == NULL)
    {
        *no = (apont)malloc(sizeof(No));
        if (*no == NULL)
        {
            printf("Erro ao alocar memória para a árvore.\n");
            return;
        }
        (*no)->livros = (Livro **)malloc(sizeof(Livro *));
        if ((*no)->livros == NULL)
        {
            printf("Erro ao alocar memória para o vetor de livros.\n");
            free(*no);
            return;
        }
        (*no)->livros[0] = novo;
        (*no)->numlivros = 1;
        (*no)->esq = NULL;
        (*no)->dir = NULL;
    }
    if (strcmp(novo->titulo, (*no)->livros[0]->titulo) < 0)
    {
        inserirportitulo(novo, &(*no)->esq);
    }
    else if (strcmp(novo->titulo, (*no)->livros[0]->titulo) > 0)
    {
        inserirportitulo(novo, &(*no)->dir);
    }
    else if (strcmp(novo->titulo, (*no)->livros[0]->titulo) == 0 && (*no)->livros[0]->isbn != novo->isbn)
    {
        (*no)->livros = (Livro **)realloc((*no)->livros, ((*no)->numlivros + 1) * sizeof(Livro *));
        if ((*no)->livros == NULL)
        {
            printf("Erro.\n");
            return;
        }
        (*no)->livros[(*no)->numlivros] = novo;
        (*no)->numlivros++;
    }
    balancear(no);
}
