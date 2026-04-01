#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct User {
    int id;
    char nome[100];
    int idade;
    struct User *prox;
} User;

typedef struct Livro {
    int id;
    char titulo[100];
    char autor[100];
    int quantidade_total;
    int quantidade_disponivel;
    int ano;
    struct Livro *prox;
} Livro;

typedef struct Emprestimo {
    int id;
    int userId;
    int livroId;
    struct Emprestimo *prox;
} Emprestimo;

// ==== ARQUIVOS ====

void salvarDados(User *listaU, Livro *listaL, Emprestimo *listaE) {

    // 1. Salva Usuários
    FILE *fUsers = fopen("banco_de_dados/usuarios.txt", "wb");
    if (fUsers) {
        User *aux = listaU;
        while (aux != NULL) {
            User temp = *aux;
            temp.prox = NULL;
            fwrite(&temp, sizeof(User), 1, fUsers);
            aux = aux->prox;
        }
        fclose(fUsers);
    }

    // 2. Salva Livros
    FILE *fLivros = fopen("banco_de_dados/livros.txt", "wb");
    if (fLivros) {
        Livro *aux = listaL;
        while (aux != NULL) {
            Livro temp = *aux;
            temp.prox = NULL;
            fwrite(&temp, sizeof(Livro), 1, fLivros);
            aux = aux->prox;
        }
        fclose(fLivros);
    }

    // 3. Salva Empréstimos
    FILE *fEmprestimos = fopen("banco_de_dados/emprestimos.txt", "wb");
    if (fEmprestimos) {
        Emprestimo *aux = listaE;
        while (aux != NULL) {
            Emprestimo temp = *aux;
            temp.prox = NULL;
            fwrite(&temp, sizeof(Emprestimo), 1, fEmprestimos);
            aux = aux->prox;
        }
        fclose(fEmprestimos);
    }

    printf("\n>>> Todos os dados foram guardados com sucesso!\n");
}

// ==== USERS ====

User* cadastrarUsuario(User *inicio) {
    User *novo = (User*) malloc(sizeof(User));
    if (novo == NULL) {
        printf("\nERRO: Falha na alocação de memória.\n");
        return inicio;
    }

    // Gerar ID único
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

    novo->id = novoId;
    printf("\nID gerado: %d", novo->id);
    printf("\nQual seu nome? ");

    scanf(" %99[^\n]", novo->nome);

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

    while (atual != NULL && atual->id != idBusca) {
        anterior = atual;
        atual = atual->prox;
    }

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

// ==== LIVROS ====

Livro* cadastrarLivro(Livro *inicio) {
    Livro *novo = (Livro*) malloc(sizeof(Livro));
    if (novo == NULL) {
        printf("\nERRO: Falha na alocação de memória.\n");
        return inicio;
    }

    // Gerar ID único
    int novoId, duplicado;
    do {
        duplicado = 0;
        novoId = (rand() % 900000) + 1000;
        Livro *temp = inicio;
        while (temp != NULL) {
            if (temp->id == novoId) {
                duplicado = 1;
                break;
            }
            temp = temp->prox;
        }
    } while (duplicado);

    novo->id = novoId;
    printf("\nID gerado: %d", novo->id);
    printf("\nQual o titulo do livro? ");

    scanf(" %99[^\n]", novo->titulo);

    printf("Qual o autor do livro? ");
    scanf(" %99[^\n]", novo->autor);

    printf("Qual o ano do livro? ");
    scanf("%d", &novo->ano);

    printf("Qual o total de livros? ");
    scanf("%d", &novo->quantidade_total);

    printf("Quantos livros disponiveis? ");
    scanf("%d", &novo->quantidade_disponivel);

    novo->prox = inicio;
    printf("\nLivro cadastrado com sucesso!\n");
    return novo;
}

Livro* carregarLivros() {
    FILE *f = fopen("banco_de_dados/livros.txt", "rb");
    if (!f) return NULL;

    Livro buffer;
    Livro *lista = NULL;
    Livro *ultimo = NULL;

    while (fread(&buffer, sizeof(Livro), 1, f) == 1) {
        Livro *novo = (Livro*) malloc(sizeof(Livro));
        if (novo == NULL) {
            printf("ERRO: Falha na alocação de memória ao carregar livros.\n");
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

Livro* removerLivro(Livro *inicio) {
    if (inicio == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return NULL;
    }

    int idBusca;
    printf("\nDigite o ID do livro a remover: ");
    scanf("%d", &idBusca);

    Livro *atual = inicio;
    Livro *anterior = NULL;

    while (atual != NULL && atual->id != idBusca) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nLivro com ID %d não encontrado.\n", idBusca);
        return inicio;
    }

    if (anterior == NULL) {
        inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("\nLivro '%s' removido com sucesso!\n", atual->titulo);
    free(atual);

    return inicio;
}

// ==== EMPRÉSTIMOS ====

Emprestimo* carregarEmprestimos() {
    FILE *f = fopen("banco_de_dados/emprestimos.txt", "rb");
    if (!f) return NULL;

    Emprestimo buffer;
    Emprestimo *lista = NULL;
    Emprestimo *ultimo = NULL;

    while (fread(&buffer, sizeof(Emprestimo), 1, f) == 1) {
        Emprestimo *novo = (Emprestimo*) malloc(sizeof(Emprestimo));
        if (novo == NULL) {
            printf("ERRO: Falha na alocação de memória ao carregar empréstimos.\n");
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

Emprestimo* realizarEmprestimo(Emprestimo *inicioE, User *inicioU, Livro *inicioL) {
    if (inicioU == NULL) {
        printf("\nNenhum usuário cadastrado.\n");
        return inicioE;
    }
    if (inicioL == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return inicioE;
    }

    int userId, livroId;

    printf("\nDigite o ID do usuário: ");
    scanf("%d", &userId);

    // Verifica se usuário existe
    User *u = inicioU;
    while (u != NULL && u->id != userId) u = u->prox;
    if (u == NULL) {
        printf("\nUsuário com ID %d não encontrado.\n", userId);
        return inicioE;
    }

    printf("Digite o ID do livro: ");
    scanf("%d", &livroId);

    // Verifica se livro existe e está disponível
    Livro *l = inicioL;
    while (l != NULL && l->id != livroId) l = l->prox;
    if (l == NULL) {
        printf("\nLivro com ID %d não encontrado.\n", livroId);
        return inicioE;
    }
    if (l->quantidade_disponivel <= 0) {
        printf("\nLivro '%s' sem exemplares disponíveis.\n", l->titulo);
        return inicioE;
    }

    // Gerar ID único para o empréstimo
    int novoId, duplicado;
    do {
        duplicado = 0;
        novoId = (rand() % 900000) + 1000;
        Emprestimo *temp = inicioE;
        while (temp != NULL) {
            if (temp->id == novoId) { duplicado = 1; break; }
            temp = temp->prox;
        }
    } while (duplicado);

    Emprestimo *novo = (Emprestimo*) malloc(sizeof(Emprestimo));
    if (novo == NULL) {
        printf("\nERRO: Falha na alocação de memória.\n");
        return inicioE;
    }

    novo->id = novoId;
    novo->userId = userId;
    novo->livroId = livroId;
    novo->prox = inicioE;

    l->quantidade_disponivel--;

    printf("\nEmpréstimo realizado com sucesso!\n");
    printf("Usuário: %s | Livro: %s\n", u->nome, l->titulo);

    return novo;
}

Emprestimo* devolverLivro(Emprestimo *inicioE, Livro *inicioL) {
    if (inicioE == NULL) {
        printf("\nNenhum empréstimo registrado.\n");
        return NULL;
    }

    int idBusca;
    printf("\nDigite o ID do empréstimo a devolver: ");
    scanf("%d", &idBusca);

    Emprestimo *atual = inicioE;
    Emprestimo *anterior = NULL;

    while (atual != NULL && atual->id != idBusca) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\nEmpréstimo com ID %d não encontrado.\n", idBusca);
        return inicioE;
    }

    // Devolve o exemplar ao estoque
    Livro *l = inicioL;
    while (l != NULL && l->id != atual->livroId) l = l->prox;
    if (l != NULL) l->quantidade_disponivel++;

    if (anterior == NULL) {
        inicioE = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    printf("\nDevolução registrada com sucesso! (Empréstimo ID: %d)\n", atual->id);
    free(atual);

    return inicioE;
}

// ==== FUNÇÃO OBRIGATÓRIA DO TRABALHO ====

void contarLivrosAntes2000(Livro *inicio) {
    if (inicio == NULL) {
        printf("\nNenhum livro cadastrado.\n");
        return;
    }

    int contador = 0;
    Livro *atual = inicio;
    while (atual != NULL) {
        if (atual->ano < 2000) {
            contador++;
        }
        atual = atual->prox;
    }

    printf("\nLivros publicados antes de 2000: %d\n", contador);
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
    Livro *listaLivros = carregarLivros();
    Emprestimo *listaEmprestimos = carregarEmprestimos();

    int opcao;
    do {
        printf("\n===== Menu Principal =====\n");
        printf("1 - Cadastrar Usuario\n");
        printf("2 - Remover Usuario\n");
        printf("3 - Listar Usuarios\n");
        printf("4 - Cadastrar Livro\n");
        printf("5 - Remover Livro\n"); 
        printf("6 - Listar Livros\n");
        printf("7 - Realizar Emprestimo\n");
        printf("8 - Devolver Livro\n");
        printf("9 - Listar Emprestimos\n");
        printf("10 - Contar livros publicados antes de 2000\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                listaUsuarios = cadastrarUsuario(listaUsuarios);
                break;

            case 2: {
                User *t = listaUsuarios;
                if (t == NULL) {
                    printf("Nenhum usuário cadastrado.\n");
                } else {
                    while (t) {
                        printf("| ID: %d | Nome: %s | Idade: %d |\n", t->id, t->nome, t->idade);
                        t = t->prox;
                    }
                }
                listaUsuarios = removerUsuario(listaUsuarios);
                break;
            }

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

            case 4:
                listaLivros = cadastrarLivro(listaLivros);
                break;

            // CORREÇÃO 5: case 5 implementado
            case 5: {
                Livro *t = listaLivros;
                if (t == NULL) {
                    printf("Nenhum livro cadastrado.\n");
                } else {
                    while (t) {
                        printf("| ID: %d | Titulo: %s | Autor: %s | Disponivel: %d/%d |\n",
                            t->id, t->titulo, t->autor, t->quantidade_disponivel, t->quantidade_total);
                        t = t->prox;
                    }
                }
                listaLivros = removerLivro(listaLivros);
                break;
            }

            case 6: {
                Livro *t = listaLivros;

                if (t == NULL) {
                    printf("Nenhum livro cadastrado.\n");
                }
                while (t) {
                    printf("| ID: %d | Titulo: %s | Autor: %s | Disponivel: %d/%d | Ano: %d |\n",
                        t->id, t->titulo, t->autor, t->quantidade_disponivel, t->quantidade_total, t->ano);
                    t = t->prox;
                }
                break;
            }

            case 7:
                listaEmprestimos = realizarEmprestimo(listaEmprestimos, listaUsuarios, listaLivros);
                break;

            case 8:
                listaEmprestimos = devolverLivro(listaEmprestimos, listaLivros);
                break;

            case 9: {
                Emprestimo *e = listaEmprestimos;
                if (e == NULL) {
                    printf("Nenhum empréstimo registrado.\n");
                }
                while (e) {
                    printf("| ID Emprestimo: %d | ID Usuario: %d | ID Livro: %d |\n",
                        e->id, e->userId, e->livroId);
                    e = e->prox;
                }
                break;
            }

            case 10:
                contarLivrosAntes2000(listaLivros);
                break;


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