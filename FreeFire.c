#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ITENS 10

// =======================
// STRUCTS
// =======================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// =======================
// VARIÁVEIS GLOBAIS
// =======================
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// =======================
// FUNÇÕES - VERSÃO VETOR
// =======================
void inserirItemVetor(Item mochila[], int *qtd);
void removerItemVetor(Item mochila[], int *qtd);
void listarItensVetor(Item mochila[], int qtd);
void ordenarVetor(Item mochila[], int qtd);
int buscarSequencialVetor(Item mochila[], int qtd, char nome[]);
int buscarBinariaVetor(Item mochila[], int qtd, char nome[]);

// =======================
// FUNÇÕES - VERSÃO LISTA
// =======================
No* inserirItemLista(No *inicio);
No* removerItemLista(No *inicio);
void listarItensLista(No *inicio);
No* buscarSequencialLista(No *inicio, char nome[]);

// =======================
// FUNÇÃO PRINCIPAL
// =======================
int main() {
    Item mochilaVetor[MAX_ITENS];
    int qtd = 0;
    No *inicio = NULL;
    int opcao, estrutura;

    printf("\n=================== MOCHILA DE LOOT ===================\n");
    printf("Escolha a estrutura de dados:\n");
    printf("1 - Vetor (lista sequencial)\n");
    printf("2 - Lista Encadeada (estrutura dinâmica)\n");
    printf("Opcao: ");
    scanf("%d", &estrutura);
    getchar();

    do {
        printf("\n---------------- MENU ----------------\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item (sequencial)\n");
        if (estrutura == 1)
            printf("5. Ordenar e buscar (binaria)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        if (estrutura == 1) {
            // --- OPERAR COM VETOR ---
            switch (opcao) {
                case 1: inserirItemVetor(mochilaVetor, &qtd); break;
                case 2: removerItemVetor(mochilaVetor, &qtd); break;
                case 3: listarItensVetor(mochilaVetor, qtd); break;
                case 4: {
                    char nome[30];
                    printf("\nDigite o nome do item: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    comparacoesSequencial = 0;
                    int pos = buscarSequencialVetor(mochilaVetor, qtd, nome);
                    if (pos != -1)
                        printf("\nItem encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n", 
                            mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                    else
                        printf("\nItem nao encontrado!\n");
                    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
                    break;
                }
                case 5: {
                    ordenarVetor(mochilaVetor, qtd);
                    printf("\nItens ordenados!\n");
                    char nome[30];
                    printf("Digite o nome do item para busca binaria: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    comparacoesBinaria = 0;
                    int pos = buscarBinariaVetor(mochilaVetor, qtd, nome);
                    if (pos != -1)
                        printf("\nItem encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n", 
                            mochilaVetor[pos].nome, mochilaVetor[pos].tipo, mochilaVetor[pos].quantidade);
                    else
                        printf("\nItem nao encontrado!\n");
                    printf("Comparacoes realizadas (busca binaria): %d\n", comparacoesBinaria);
                    break;
                }
                case 0: printf("\nSaindo...\n"); break;
                default: printf("\nOpcao invalida!\n");
            }
        } else {
            // --- OPERAR COM LISTA ---
            switch (opcao) {
                case 1: inicio = inserirItemLista(inicio); break;
                case 2: inicio = removerItemLista(inicio); break;
                case 3: listarItensLista(inicio); break;
                case 4: {
                    char nome[30];
                    printf("\nDigite o nome do item: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0';
                    comparacoesSequencial = 0;
                    No *encontrado = buscarSequencialLista(inicio, nome);
                    if (encontrado)
                        printf("\nItem encontrado! Nome: %s | Tipo: %s | Quantidade: %d\n",
                            encontrado->dados.nome, encontrado->dados.tipo, encontrado->dados.quantidade);
                    else
                        printf("\nItem nao encontrado!\n");
                    printf("Comparacoes realizadas: %d\n", comparacoesSequencial);
                    break;
                }
                case 0: printf("\nSaindo...\n"); break;
                default: printf("\nOpcao invalida!\n");
            }
        }

    } while (opcao != 0);

    return 0;
}

// ===================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES (VETOR)
// ===================================================
void inserirItemVetor(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia!\n");
        return;
    }

    Item novo;
    printf("\nNome: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\nItem adicionado com sucesso!\n");
}

void removerItemVetor(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nMochila vazia!\n");
        return;
    }

    char nome[30];
    printf("\nNome do item para remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            for (int j = i; j < *qtd - 1; j++)
                mochila[j] = mochila[j + 1];
            (*qtd)--;
            printf("\nItem removido!\n");
            return;
        }
    }
    printf("\nItem nao encontrado!\n");
}

void listarItensVetor(Item mochila[], int qtd) {
    printf("\n=== Itens na mochila ===\n");
    if (qtd == 0) {
        printf("Nenhum item.\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n", 
            i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

void ordenarVetor(Item mochila[], int qtd) {
    Item temp;
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(mochila[i].nome, mochila[j].nome) > 0) {
                temp = mochila[i];
                mochila[i] = mochila[j];
                mochila[j] = temp;
            }
        }
    }
}

int buscarSequencialVetor(Item mochila[], int qtd, char nome[]) {
    for (int i = 0; i < qtd; i++) {
        comparacoesSequencial++;
        if (strcmp(mochila[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

int buscarBinariaVetor(Item mochila[], int qtd, char nome[]) {
    int inicio = 0, fim = qtd - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

// ===================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES (LISTA ENCADEADA)
// ===================================================
No* inserirItemLista(No *inicio) {
    No *novo = (No*) malloc(sizeof(No));
    if (!novo) {
        printf("Erro de alocacao!\n");
        return inicio;
    }

    printf("\nNome: ");
    fgets(novo->dados.nome, sizeof(novo->dados.nome), stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';
    printf("Tipo: ");
    fgets(novo->dados.tipo, sizeof(novo->dados.tipo), stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = inicio;
    printf("\nItem inserido na lista!\n");
    return novo;
}

No* removerItemLista(No *inicio) {
    if (!inicio) {
        printf("\nLista vazia!\n");
        return inicio;
    }

    char nome[30];
    printf("\nNome do item para remover: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    No *atual = inicio, *anterior = NULL;

    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                inicio = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("\nItem removido da lista!\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("\nItem nao encontrado!\n");
    return inicio;
}

void listarItensLista(No *inicio) {
    if (!inicio) {
        printf("\nLista vazia!\n");
        return;
    }

    printf("\n=== Itens na lista encadeada ===\n");
    No *atual = inicio;
    int i = 1;
    while (atual) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
            i++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(No *inicio, char nome[]) {
    No *atual = inicio;
    while (atual) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}
