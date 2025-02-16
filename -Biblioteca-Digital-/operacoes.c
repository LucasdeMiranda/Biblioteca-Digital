#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "operacoes.h"
void buscarporautor(char *autor, apont no)
{
    if (no == NULL)
    {
        printf("Nenhum livro encontrado\n");
    }
    else
    {
        if (strcmp(autor, no->livros[0]->autor) == 0)
        {
            for (int i = 0; i < no->numlivros; i++)
            {
                if (no->livros[i]->isbn > 0)
                {
                    printf("\tTítulo: %s, Autor: %s, Gênero: %s,Ano: %d ISBN:%d \n,", no->livros[i]->titulo, no->livros[i]->autor, no->livros[i]->genero, no->livros[i]->ano, no->livros[i]->isbn);
                }
            }
        }
        else if (strcmp(autor, no->livros[0]->autor) > 0)
        {
            buscarporautor(autor, no->dir);
        }
        else if (strcmp(autor, no->livros[0]->autor) < 0)
        {
            buscarporautor(autor, no->esq);
        }
    }
}

void buscarportitulo(char *titulo, apont no)
{
    if (no == NULL)
    {
        printf("Nenhum livro encontrado\n");
    }
    else
    {
        if (strcmp(titulo, no->livros[0]->titulo) == 0)
        {
            for (int i = 0; i < no->numlivros; i++)
            {
                if (no->livros[i]->isbn > 0)
                {
                    printf("\tTítulo: %s, Autor: %s, Gênero: %s, Ano: %d,ISBN:%d\n", no->livros[i]->titulo, no->livros[i]->autor, no->livros[i]->genero, no->livros[i]->ano, no->livros[i]->isbn);
                }
                else
                {
                    printf("livro não encontrado\n");
                }
            }
        }
        else if (strcmp(titulo, no->livros[0]->titulo) > 0)
        {
            buscarportitulo(titulo, no->dir);
        }
        else if (strcmp(titulo, no->livros[0]->titulo) < 0)
        {
            buscarportitulo(titulo, no->esq);
        }
    }
}

void buscarporano(int ano, apont no)
{
    if (no == NULL)
    {
        printf("Nenhum livro encontrado\n");
    }
    else
    {
        if (ano == (no)->livros[0]->ano)
        {
            for (int i = 0; i < (no)->numlivros; i++)
            {
                if (no->livros[i]->isbn > 0)
                {
                    printf("\tTítulo: %s, Autor: %s, Gênero: %s,Ano: %d ISBN:%d \n,", no->livros[i]->titulo, no->livros[i]->autor, no->livros[i]->genero, no->livros[i]->ano, no->livros[i]->isbn);
                }
            }
        }
        else if (ano < (no)->livros[0]->ano)
        {
            buscarporano(ano, (no)->esq);
        }
        else
        {
            buscarporano(ano, (no)->dir);
        }
    }
}
int excluirano(int id, int ano, apont *no,  Livro **livro)
{
    int k = -1;
    apont aux;

    if (*no == NULL)
    {//não encontrado 
        return -1;  
    }
    else
    {

        if ((*no)->livros[0]->ano == ano)
        {
          
            for (int i = 0; i < (*no)->numlivros; i++)
            {
                if ((*no)->livros[i]->isbn == id)
                {

                    k = i;
                    *livro = (*no)->livros[i];

                    break;
                }
            }
            if (k == -1)
            {
                printf("Livro não encontrado no ano especificado.\n");//achou o ano mas não o id
                return -1;
            }

            for (int j = k; j < (*no)->numlivros - 1; j++)
            {
                (*no)->livros[j] = (*no)->livros[j + 1];
            }
            (*no)->numlivros--;

            if ((*no)->numlivros == 0)
            {
                if ((*no)->esq == NULL && (*no)->dir == NULL)
                {
                    free((*no)->livros);
                    free(*no);
                    *no = NULL;
                }
                else if ((*no)->esq != NULL && (*no)->dir == NULL)
                {
                    aux = (*no)->esq;
                    free((*no)->livros);
                    free(*no);
                    *no = aux;
                }
                else if ((*no)->dir != NULL && (*no)->esq == NULL)
                {
                    aux = (*no)->dir;
                    free((*no)->livros);
                    free(*no);
                    *no = aux;
                }
                else
                {
    
                    aux = (*no)->dir;
                    while (aux->esq != NULL) //percorre os nós a esquerda da sub árvore direita
                    {
                        aux = aux->esq; //encontra o nó mais a esquerda da sub arvore direita
                    }
                    //copia o numero de livros de aux->numlivros
                    (*no)->numlivros = aux->numlivros;
                    for (int i = 0; i < aux->numlivros; i++)
                    {
                        (*no)->livros[i] = aux->livros[i];
                    }
                    //livro[0] é chave de busca para busca de um livro pelo ano por isso é passado assim  
                    excluirano(id, aux->livros[0]->ano, &(*no)->dir, livro);//chama para excluir o nó pra não ficar dois nós iguais porque ja foi copiado 
                }
            }
        }
        else if (ano > (*no)->livros[0]->ano)
        {
            return excluirano(id, ano, &(*no)->dir, livro); 
        }
        else if (ano < (*no)->livros[0]->ano)
        {
            return excluirano(id, ano, &(*no)->esq, livro);  
        }
    }

    balancear(no);
    return 0; //sucesso
}

int excluirtitulo(int id, char *titulo, apont *no)
{
    int k = -1;
    apont aux;

    if (*no == NULL)
    {
        return -1;
    }
    else
    {
        if (strcmp(titulo, (*no)->livros[0]->titulo) == 0)
        {
            for (int i = 0; i < (*no)->numlivros; i++)
            {
                if ((*no)->livros[i]->isbn == id)
                {
                    k = i;
                    break;
                }
            }
            if (k == -1)
            {
                printf("Livro não encontrado no título.\n");
                return -1;
            }
            for (int j = k; j < (*no)->numlivros - 1; j++)
            {
                (*no)->livros[j] = (*no)->livros[j + 1];
            }
            (*no)->numlivros--;
          
            if ((*no)->numlivros == 0)
            {
                if ((*no)->esq == NULL && (*no)->dir == NULL)
                {
                    free((*no)->livros);
                    free(*no);
                    *no = NULL;
                }
                else if ((*no)->esq != NULL && (*no)->dir == NULL)
                {
                    aux = (*no)->esq;
                    free((*no)->livros);
                    free(*no);
                    *no = aux;
                }
                else if ((*no)->dir != NULL && (*no)->esq == NULL)
                {
                    aux = (*no)->dir;
                    free((*no)->livros);
                    free(*no);
                    *no = aux;
                }
                else
                {
                    aux = (*no)->dir;
                    while (aux->esq != NULL)
                    {
                        aux = aux->esq;
                    }
                    (*no)->numlivros = aux->numlivros;
                    for (int i = 0; i < aux->numlivros; i++)
                    {
                        (*no)->livros[i] = aux->livros[i];
                    }
                    excluirtitulo(id, aux->livros[0]->titulo, &(*no)->dir);
                }
            }
        }
        else if (strcmp(titulo, (*no)->livros[0]->titulo) > 0)
        {
            return excluirtitulo(id, titulo, &(*no)->dir);
        }
        else if (strcmp(titulo, (*no)->livros[0]->titulo) < 0)
        {
            return excluirtitulo(id, titulo, &(*no)->esq);
        }
    }
    balancear(no);
    return 0;
}

int excluirautor(int id, char *autor, apont *no)
{
    int k = -1;
    apont aux;
    if (*no == NULL)
    {
        return -1;
    }
    else
    {
        if (strcmp(autor, (*no)->livros[0]->autor) == 0)
        {
            for (int i = 0; i < (*no)->numlivros; i++)
            {
                if ((*no)->livros[i]->isbn == id)
                {
                    k = i;
                    break;
                }
            }
            if (k == -1)
            {
                printf("Livro não encontrado para o autor.\n");
                return -1;
            }
            for (int j = k; j < (*no)->numlivros - 1; j++)
            {
                (*no)->livros[j] = (*no)->livros[j + 1];
            }
            (*no)->numlivros--;
            if ((*no)->numlivros == 0)
            {
                if ((*no)->esq == NULL && (*no)->dir == NULL)
                {
                    free((*no)->livros);
                    free(*no);
                    *no = NULL;
                }
                else if ((*no)->esq != NULL && (*no)->dir == NULL)
                {
                    aux = (*no)->esq;
                    free((*no)->livros);
                    free(*no);
                    *no = aux;
                }
                else if ((*no)->dir != NULL && (*no)->esq == NULL)
                {
                    aux = (*no)->dir;
                    free((*no)->livros);
                    free(*no);
                    *no = aux;
                }
                else
                {
                    aux = (*no)->dir;
                    while (aux->esq != NULL)
                    {
                        aux = aux->esq;
                    }
                    (*no)->numlivros = aux->numlivros;
                    for (int i = 0; i < aux->numlivros; i++)
                    {
                        (*no)->livros[i] = aux->livros[i];
                    }
                    excluirautor(id, aux->livros[0]->autor, &(*no)->dir);
                }
            }
        }
        else if (strcmp(autor, (*no)->livros[0]->autor) > 0)
        {
            return excluirautor(id, autor, &(*no)->dir);  
        }
        else if (strcmp(autor, (*no)->livros[0]->autor) < 0)
        {
            return excluirautor(id, autor, &(*no)->esq);  
        }
    }
    balancear(no);
    return 0; 
}
void excluilivro(Livro **livro)
{
    free(*livro);
    *livro = NULL;
}

int emprestimo(char *titulo, int id, apont no)
{
    if (no == NULL)
    {
        return -1;
    }
    else
    {
        if (strcmp(titulo, no->livros[0]->titulo) == 0)
        {

            for (int i = 0; i < no->numlivros; i++)
            {
                if (no->livros[i]->isbn == id && no->livros[i]->isbn > 0)
                {
                    no->livros[i]->isbn = no->livros[i]->isbn * -1;

                    return 0;
                }
                else if (no->livros[i]->isbn == (id * -1) && no->livros[i]->isbn < 0)
                {
                    return 1; // livro já emprestado
                }
            }
        }

        else if (strcmp(titulo, no->livros[0]->titulo) > 0)
        {
            return emprestimo(titulo, id, no->dir);
        }
        else if (strcmp(titulo, no->livros[0]->titulo) < 0)
        {
            return emprestimo(titulo, id, no->esq);
        }
    }
}
int devolucao(char *titulo, int id, apont no)
{
    if (no == NULL)
    {
        return -1; // não encontrado
    }
    else
    {
        if (strcmp(titulo, no->livros[0]->titulo) == 0)
        {

            for (int i = 0; i < no->numlivros; i++)
            {
                if (no->livros[i]->isbn == id && no->livros[i]->isbn < 0)
                {
                    no->livros[i]->isbn = no->livros[i]->isbn * -1; // encontrado
                    return 0;
                }
                else if (no->livros[i]->isbn == (id * -1) && no->livros[i]->isbn > 0)
                {
                    return 1; // livro disponivel
                }
            }
        }
        else if (strcmp(titulo, no->livros[0]->titulo) > 0)
        {
            return devolucao(titulo, id, no->dir);
        }
        else if (strcmp(titulo, no->livros[0]->titulo) < 0)
        {
            return devolucao(titulo, id, no->esq);
        }
    }
}
void disponivel(apont no, int nivel) // nivel = nivel na árvore avl
{
    if (no)//se não é null
    {
        printf(" Ano: %d\n", no->livros[0]->ano);
        for (int i = 0; i < no->numlivros; i++)
        {
            if (no->livros[i]->isbn > 0)
            {
                printf("\tLivro ISBN: %d, Título: %s, Autor: %s, Gênero: %s, Ano: %d\n",
                       no->livros[i]->isbn,
                       no->livros[i]->titulo,
                       no->livros[i]->autor,
                       no->livros[i]->genero,
                       no->livros[i]->ano);
            }
        }
        disponivel(no->esq, nivel + 1);//chama de forma recursiva adicionando 1 para poder percorrer todos os niveis 
        disponivel(no->dir, nivel + 1);
    }
}
void emprestados(apont no, int nivel)
{
    if (no)
    {
        printf(" Ano: %d\n", no->livros[0]->ano);
        for (int i = 0; i < no->numlivros; i++)
        {
            if (no->livros[i]->isbn < 0)
            {
                printf("\tLivro ISBN: %d, Título: %s, Autor: %s, Gênero: %s, Ano: %d\n",
                       no->livros[i]->isbn * -1,
                       no->livros[i]->titulo,
                       no->livros[i]->autor,
                       no->livros[i]->genero,
                       no->livros[i]->ano);
            }
        }
        emprestados(no->esq, nivel + 1);
        emprestados(no->dir, nivel + 1);
    }
}
void lerarquivo(const char *nome, apont *arvoreano, apont *arvoreautor, apont *arvoretitulo)
{
    FILE *arquivo = fopen(nome, "r");
    if (!arquivo)
    {
        perror("Erro ao abrir o arquivo");
        fprintf(stderr, "Erro ao abrir o arquivo %s: %s\n", nome, strerror(errno));
        return;
    }

    Livro *livro;
    while (1)
    {
        livro = (Livro *)malloc(sizeof(Livro));
        if (livro == NULL)
        {
            fprintf(stderr, "Erro ao alocar memória para um livro: %s\n", strerror(errno));
            break;
        }

        if (fscanf(arquivo, "%d,%299[^,],%299[^,],%299[^,],%d\n",
                   &livro->isbn, livro->autor, livro->titulo, livro->genero, &livro->ano) == EOF)
        {
            free(livro);
            break;
        }
        inserirporano(livro, arvoreano);//ponteiros diferentes porque são criterios de ordenaçao diferentes
        inserirporautor(livro, arvoreautor);
        inserirportitulo(livro, arvoretitulo);
    }

    fclose(arquivo);
}