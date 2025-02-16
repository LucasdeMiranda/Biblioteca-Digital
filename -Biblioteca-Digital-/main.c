#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "fila.h"
#include "arvore.h"
#include "operacoes.h"
int main()
{
    Fila fila1, fila2;
    inicializarfila(&fila1), inicializarfila(&fila2);
    apont arvoreano, arvoreautor, arvoretitulo;
    Registro nregistro;
    inicializaarvore(&arvoreano, &arvoreautor, &arvoretitulo);
    int op1, op2, ano, id, r1, r2, r3, r4, r5;
    char autor[300], titulo[300], npessoa[300];
    const char *nome = "livros.txt";

    lerarquivo(nome, &arvoreano, &arvoreautor, &arvoretitulo);

    do
    {
        Livro *livro = NULL;
         r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0;
        id = 0;
         

        printf("1:Pesquisar\n");
        printf("2:Inserir\n");
        printf("3:Remover\n");
        printf("4:Emprestimo\n");
        printf("5:Devolução\n");
        printf("6:Relatorios\n");
        printf("7:Histórico\n");
        printf("8:Sair\n");
        scanf("%d", &op1);

        if (op1 == 1)
        {
            printf(" 1: busca pelo ano\n");
            printf(" 2: busca pelo autor\n");
            printf(" 3: busca pelo titulo\n");
            scanf("%d", &op2);
            getchar();
            if (op2 == 1)
            {
                printf("digite o ano:");
                scanf("%d", &ano);
                buscarporano(ano, arvoreano);
            }
            else if (op2 == 2)
            {
                printf("digite o autor:");
                scanf("%[^\n]", autor);
                buscarporautor(autor, arvoreautor);
            }
            else if (op2 == 3)
            {
                printf("digite o titulo do livro:");
                scanf("%[^\n]", titulo);
                buscarportitulo(titulo, arvoretitulo);
            }
        }
        if (op1 == 2)
        {
            Livro *novo = (Livro *)malloc(sizeof(Livro));
            printf("Digite o título do livro: ");
            getchar();
            scanf("%[^\n]", novo->titulo);

            printf("Digite o autor: ");
            getchar();
            scanf("%[^\n]", novo->autor);

            printf("Digite o gênero do livro: ");
            getchar();
            scanf("%[^\n]", novo->genero);

            printf("Digite o ano de publicação: ");
            scanf("%d", &novo->ano);

            printf("Digite o ISBN: ");
            scanf("%d", &novo->isbn);
            // Insere o ponteiro para o novo livro manualmente nas três árvores
            inserirporano(novo, &arvoreano);
            inserirporautor(novo, &arvoreautor);
            inserirportitulo(novo, &arvoretitulo);
        }
        if (op1 == 3)
        {
            printf("Digite o ISBN do livro: ");
            scanf("%d", &id);
            printf("Digite o ano de publicação: ");
            scanf("%d", &ano);
            printf("Digite o autor: ");
            getchar(); // Para capturar o '\n' do scanf anterior
            scanf("%[^\n]", autor);
            printf("Digite o título do livro: ");
            getchar();
            scanf("%[^\n]", titulo);

            r1 = excluirano(id, ano, &arvoreano,&livro);
            r2 = excluirautor(id, autor, &arvoreautor);
            r3 = excluirtitulo(id, titulo, &arvoretitulo);

            if (r1 < 0)
            {
                printf("Erro ao excluir pelo ano. Dados incorretos.\n");
                while (r1 < 0)
                {
                    printf("Digite novamente o ISBN e o ano de publicação:\n");
                    printf("Digite o ISBN do livro: ");
                    scanf("%d", &id);
                    printf("Digite o ano de publicação: ");
                    scanf("%d", &ano);
                    r1 = excluirano(id, ano, &arvoreano, &livro);
                }
            }

            if (r2 < 0)
            {
                printf("Erro ao excluir pelo autor. Dados incorretos.\n");
                while (r2 < 0)
                {
                    printf("Digite novamente o ISBN e o autor:\n");
                    printf("Digite o ISBN do livro: ");
                    scanf("%d", &id);
                    printf("Digite o autor: ");
                    getchar();
                    scanf("%[^\n]", autor);
                    r2 = excluirautor(id, autor, &arvoreautor);
                }
            }
            if (r3 < 0)
            {
                printf("Erro ao excluir pelo título. Dados incorretos.\n");
                while (r3 < 0)
                {
                    printf("Digite novamente o ISBN e o título do livro:\n");
                    printf("Digite o ISBN do livro: ");
                    scanf("%d", &id);
                    printf("Digite o título do livro: ");
                    getchar(); 
                    scanf("%[^\n]", titulo);
                    r3 = excluirtitulo(id, titulo, &arvoretitulo); //chama r3 denovo

                }
            }
            if (r1 == 0 && r2 == 0 && r3 == 0 && livro != NULL)
            {
                printf("Livro excluído: %s (ISBN: %d)\n", livro->titulo, livro->isbn);

                excluilivro(&livro);
            }
        }

        if (op1 == 4)
        {
            printf("digite seu nome:");
            getchar();
            scanf("%[^\n]", npessoa);
            printf("Digite o título do livro: ");
            getchar();
            scanf("%[^\n]", titulo);
            printf("digite o isbn do livro:");
            scanf("%d", &id);
            r4 = emprestimo(titulo, id, arvoretitulo);
            if (r4 < 0)
            {
                printf("livro não encontrado\n");
            }
            else if (r4 > 0)
            {
                printf("livro já foi emprestado\n");
            }
            else if (r4 == 0)
            {

                strcpy(nregistro.nomepessoa, npessoa);
                strcpy(nregistro.titulolivro, titulo);
                time_t t = time(NULL);
                nregistro.dataregistro = localtime(&t); // preenchendo com a data atual
                enfileirar(&fila1, nregistro);
                printf("livro emprestado com sucesso\n");
            }
        }
        if (op1 == 5)
        {
            printf("digite seu nome:");
            getchar();
            scanf("%[^\n]", npessoa);
            printf("Digite o título do livro: ");
            getchar();
            scanf("%[^\n]", titulo);
            printf("digite o isbn do livro:");
            scanf("%d", &id);
            id = id * -1; // o id foi modificado para negativo então deve ser passado negativo
            r5 = devolucao(titulo, id, arvoretitulo);
            if (r5 < 0)
            {
                printf("livro não encontrado\n");
            }
            else if (r5 > 0)
            {
                printf("livro está disponivel e não foi emprestado\n");
            }
            else if (r5 == 0)
            {
                strcpy(nregistro.nomepessoa, npessoa);
                strcpy(nregistro.titulolivro, titulo);
                time_t t = time(NULL);
                nregistro.dataregistro = localtime(&t);
                enfileirar(&fila2, nregistro);
                printf("livro devolvido com sucesso\n");
            }
        }
        if (op1 == 6)
        {
            printf("livros disponiveis (Agrupados por ano de publicação):\n");
            disponivel(arvoreano, 0);
            printf("\n");
            printf("livros emprestados (Agrupados por ano de publicação):\n");
            emprestados(arvoreano, 0);
        }
        if (op1 == 7)
        {
            printf("Emprestimos realizados\n");
            imprimirfila(&fila1);
            printf("Devoluções realizadas\n");
            imprimirfila(&fila2);
        }

    } while (op1 != 8);

    return 0;
}