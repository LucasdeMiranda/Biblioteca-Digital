#ifndef ARVORE_H
#define ARVORE_H

typedef struct
{
    char titulo[300], autor[300], genero[300];
    int ano, isbn;
} Livro;
typedef struct No *apont;

typedef struct No
{
    Livro **livros; //  ponteiro para vetor de ponteiros para os livros
    int numlivros;  //  numero de livros no vetor de ponteiros do nó
    apont esq, dir;
} No;
int altura(apont no);
int calculabalanceamento(apont no);
void rotacaodireita(apont *no);
void rotacaoesquerda(apont *no);
void balanceioesquerdo(apont *no);
void balanceiodireito(apont *no);
void balancear(apont *no);
void inicializaarvore(apont *arvoreano, apont *arvoreautor, apont *arvoretitulo);
void inserirporano(Livro *novo, apont *no);
void inserirporautor(Livro *novo, apont *no);
void inserirportitulo(Livro *novo, apont *no);
#endif  