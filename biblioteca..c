#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct User
{
    int id;
    char nome[100];
    int idade;
    struct User *prox; 
} User;

typedef struct Livro
{
    int id;
    char titulo[50];
    char autor[50];
    int quantidade_total;
    int quantidade_disponivel;
    int ano;
    struct Livro *prox;  
} Livro;

typedef struct Emprestimo
{
    int userId;
    int livrosId;
    struct Emprestimo *prox; 
} Emprestimo;

int totalLivros = 0;
int totalUsers = 0;
int totalEmprestimos = 0;

// ==== ARQUIVOS ====

void salvarDados(User *listaU, Livro *listaL, Emprestimo *listaE) {

    // 1. Salva Usuários
    FILE *fUsers = fopen("banco_de_dados/usuarios.txt", "wb");
    if (fUsers) {
        User *aux = listaU;
        while (aux != NULL) {
            fwrite(aux, sizeof(User), 1, fUsers);
            aux = aux->prox;
        }
        fclose(fUsers);
    }

    // 2. Salva Livros
    FILE *fLivros = fopen("banco_de_dados/livros.txt", "wb");
    if (fLivros) {
        Livro *aux = listaL;
        while (aux != NULL) {
            fwrite(aux, sizeof(Livro), 1, fLivros); 
            aux = aux->prox;
        }
        fclose(fLivros);
    }

    // 3. Salva Empréstimos
    FILE *fEmprestimos = fopen("banco_de_dados/emprestimos.txt", "wb");
    if (fEmprestimos) {
        Emprestimo *aux = listaE;
        while (aux != NULL) {
            fwrite(aux, sizeof(Emprestimo), 1, fEmprestimos);
            aux = aux->prox;
        }
        fclose(fEmprestimos);
    }

    printf("\n>>> Todos os dados foram guardados com sucesso!\n");
}

// ==== FUNÇÕES DO SISTEMA ====

User* cadastrarUsuario(User *inicio) {
    User *novo = (User*) malloc(sizeof(User));
    if (novo == NULL) {
        printf("\nERRO: Falha na alocação de memória.\n");
        return inicio;
    }

    // ==== Gerar ID único ====
    int novoId, duplicado;
    do {
        duplicado = 0;
        novoId = (rand() % 900000) + 1000;
        User *temp = inicio;
        while (temp != NULL) {
            if (temp->id == novoId) {
                duplicado = 1;
                break;
            }
            temp = temp->prox;
        }
    } while (duplicado);
    // ========================

    novo->id = novoId;
    printf("\nID gerado: %d", novo->id);
    printf("\nQual seu nome? ");

    scanf(" %99s", novo->nome);

    printf("Qual sua idade? ");
    scanf("%d", &novo->idade);

    novo->prox = inicio;
    printf("\nUsuário cadastrado com sucesso!\n");
    return novo;
}

User* carregarUsers() {
    FILE *f = fopen("banco_de_dados/usuarios.txt", "rb");
    if (!f) return NULL;

    User buffer;
    User *lista = NULL;
    User *ultimo = NULL; 

    while (fread(&buffer, sizeof(User), 1, f) == 1) {
        User *novo = (User*) malloc(sizeof(User));
        if (novo == NULL) {
            printf("ERRO: Falha na alocação de memória ao carregar usuários.\n");
            break;
        }
        *novo = buffer;
        novo->prox = NULL;

        if (lista == NULL) {
            lista = novo;
            ultimo = novo;
        } else {
            ultimo->prox = novo;
            ultimo = novo;
        }
    }

    fclose(f);
    return lista;
}

User* removerUsuario(User *inicio) {
    if (inicio == NULL) {
        printf("\nNenhum usuário cadastrado.\n");
        return NULL;
    }

    int idBusca;
    printf("\nDigite o ID do usuário a remover: ");
    scanf("%d", &idBusca);

    User *atual = inicio;
    User *anterior = NULL;

    // Percorre a lista procurando o ID
    while (atual != NULL && atual->id != idBusca) {
        anterior = atual;
        atual = atual->prox;
    }

    // ID não encontrado
    if (atual == NULL) {
        printf("\nUsuário com ID %d não encontrado.\n", idBusca);
        return inicio;
    }

    if (anterior == NULL) {
        inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("\nUsuário '%s' removido com sucesso!\n", atual->nome);
    free(atual);

    return inicio;
}

// ==== LIBERAR MEMÓRIA ====

void liberarUsuarios(User *inicio) {
    User *atual = inicio;
    while (atual != NULL) {
        User *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

void liberarLivros(Livro *inicio) {
    Livro *atual = inicio;
    while (atual != NULL) {
        Livro *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

void liberarEmprestimos(Emprestimo *inicio) {
    Emprestimo *atual = inicio;
    while (atual != NULL) {
        Emprestimo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

// ==== MENU PRINCIPAL ====

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    User *listaUsuarios = carregarUsers();
    Livro *listaLivros = NULL;
    Emprestimo *listaEmprestimos = NULL;

    int opcao;
    do {
        printf("\n===== Menu Principal =====\n");
        printf("1 - Cadastrar Usuario\n");
        printf("2 - Remover Usuario\n");
        printf("3 - Listar Usuarios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listaUsuarios = cadastrarUsuario(listaUsuarios);
                break;

            case 2:
                User *t = listaUsuarios;
                if (t == NULL) {
                    printf("Nenhum usuário cadastrado.\n");
                }
                while (t) {
                    printf("| ID: %d | Nome: %s | Idade: %d |\n", t->id, t->nome, t->idade);
                    t = t->prox;
                }
                listaUsuarios = removerUsuario(listaUsuarios);
                break;

            case 3: { 
                User *t = listaUsuarios;
                if (t == NULL) {
                    printf("Nenhum usuário cadastrado.\n");
                }
                while (t) {
                    printf("| ID: %d | Nome: %s | Idade: %d |\n", t->id, t->nome, t->idade);
                    t = t->prox;
                }
                break;
            }

            case 0:
                salvarDados(listaUsuarios, listaLivros, listaEmprestimos);
                liberarUsuarios(listaUsuarios);
                liberarLivros(listaLivros);
                liberarEmprestimos(listaEmprestimos);
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}