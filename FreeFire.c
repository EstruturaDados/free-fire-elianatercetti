#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  




typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;




void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);




int main() {
    Item mochila[MAX_ITENS];
    int qtd = 0; 
    int opcao;

    do {
        printf("\n========== MOCHILA DE LOOT ==========\n");
        printf("1. Cadastrar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                inserirItem(mochila, &qtd);
                break;
            case 2:
                removerItem(mochila, &qtd);
                break;
            case 3:
                listarItens(mochila, qtd);
                break;
            case 4:
                buscarItem(mochila, qtd);
                break;
            case 0:
                printf("\nSaindo do sistema... Ate a proxima batalha!\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente!\n");
        }

    } while (opcao != 0);

    return 0;
}




void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nA mochila esta cheia! Remova um item antes de adicionar outro.\n");
        return;
    }

    Item novo;
    printf("\n=== Cadastro de Item ===\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; 

    printf("Tipo do item (arma, municao, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*qtd] = novo;
    (*qtd)++;

    printf("\nItem adicionado com sucesso!\n");
    listarItens(mochila, *qtd);
}




void removerItem(Item mochila[], int *qtd) {
    if (*qtd == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado == -1) {
        printf("\nItem nao encontrado!\n");
        return;
    }

    
    for (int i = encontrado; i < *qtd - 1; i++) {
        mochila[i] = mochila[i + 1];
    }

    (*qtd)--;

    printf("\nItem removido com sucesso!\n");
    listarItens(mochila, *qtd);
}




void listarItens(Item mochila[], int qtd) {
    printf("\n=== Itens na Mochila ===\n");
    if (qtd == 0) {
        printf("Nenhum item cadastrado.\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        printf("%d. Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}




void buscarItem(Item mochila[], int qtd) {
    if (qtd == 0) {
        printf("\nA mochila esta vazia!\n");
        return;
    }

    char nomeBuscar[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBuscar, sizeof(nomeBuscar), stdin);
    nomeBuscar[strcspn(nomeBuscar, "\n")] = '\0';

    for (int i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nomeBuscar) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem nao encontrado!\n");
}
