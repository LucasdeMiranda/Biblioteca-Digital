#ifndef OPERACOES_H
#define OPERACOES_H
#include "arvore.h"
void buscarporautor(char *autor, apont no);
void buscarportitulo(char *titulo, apont no);
void buscarporano(int ano, apont no);
int excluirano(int id, int ano, apont *no,  Livro **livro);
int excluirtitulo(int id, char *titulo, apont *no);
int excluirautor(int id, char *autor, apont *no);
void excluilivro(Livro **livro);
int emprestimo(char *titulo, int id, apont no);
int devolucao(char *titulo, int id, apont no);
void disponivel(apont no, int nivel); // nivel = nivel na árvore avl
void emprestados(apont no, int nivel);
void lerarquivo(const char *nome, apont *arvoreano, apont *arvoreautor, apont *arvoretitulo);
#endif  