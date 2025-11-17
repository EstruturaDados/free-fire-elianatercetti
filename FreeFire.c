#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMP 20

// ======================
// STRUCT
// ======================
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// ======================
// VARIÁVEIS GLOBAIS
// ======================
int comparacoes = 0;

// ======================
// FUNÇÕES AUXILIARES
// ======================
void mostrarComponentes(Componente comp[], int n);
void copiarComponentes(Componente origem[], Componente destino[], int n);

// ======================
// ALGORITMOS DE ORDENAÇÃO
// ======================
void bubbleSortNome(Componente comp[], int n);
void insertionSortTipo(Componente comp[], int n);
void selectionSortPrioridade(Componente comp[], int n);

// ======================
// BUSCA BINÁRIA
// ======================
int buscaBinariaPorNome(Componente comp[], int n, char nome[]);

// ======================
// FUNÇÃO PRINCIPAL
// ======================
int main() {
    Componente componentes[MAX_COMP], copia[MAX_COMP];
    int n = 0, opcao;
    char nomeBusca[30];

    printf("\n=============== MISSÃO FINAL: TORRE DE RESGATE ===============\n");

    // Cadastro dos componentes
    printf("\nQuantos componentes deseja cadastrar (max %d)? ", MAX_COMP);
    scanf("%d", &n);
    getchar();

    if (n > MAX_COMP) n = MAX_COMP;

    for (int i = 0; i < n; i++) {
        printf("\n--- Componente %d ---\n", i + 1);
        printf("Nome: ");
        fgets(componentes[i].nome, sizeof(componentes[i].nome), stdin);
        componentes[i].nome[strcspn(componentes[i].nome, "\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo, sizeof(componentes[i].tipo), stdin);
        componentes[i].tipo[strcspn(componentes[i].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {
        printf("\n================ MENU DE ESTRATÉGIAS ================\n");
        printf("1. Ordenar por Nome (Bubble Sort)\n");
        printf("2. Ordenar por Tipo (Insertion Sort)\n");
        printf("3. Ordenar por Prioridade (Selection Sort)\n");
        printf("4. Buscar componente-chave (Busca Binária - requer ordenação por nome)\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        copiarComponentes(componentes, copia, n);
        comparacoes = 0;
        clock_t inicio, fim;
        double tempo;

        switch (opcao) {
            case 1:
                inicio = clock();
                bubbleSortNome(copia, n);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\n>>> Ordenação por NOME concluída! <<<\n");
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(copia, n);
                break;

            case 2:
                inicio = clock();
                insertionSortTipo(copia, n);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\n>>> Ordenação por TIPO concluída! <<<\n");
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(copia, n);
                break;

            case 3:
                inicio = clock();
                selectionSortPrioridade(copia, n);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\n>>> Ordenação por PRIORIDADE concluída! <<<\n");
                printf("Comparações: %d | Tempo: %.6f segundos\n", comparacoes, tempo);
                mostrarComponentes(copia, n);
                break;

            case 4:
                printf("\nDigite o nome do componente-chave: ");
                fgets(nomeBusca, sizeof(nomeBusca), stdin);
                nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

                // Busca binária exige vetor ordenado por nome
                bubbleSortNome(componentes, n);
                int pos = buscaBinariaPorNome(componentes, n, nomeBusca);
                if (pos != -1)
                    printf("\n✅ Componente encontrado: %s | Tipo: %s | Prioridade: %d\n",
                           componentes[pos].nome, componentes[pos].tipo, componentes[pos].prioridade);
                else
                    printf("\n❌ Componente não encontrado!\n");
                printf("Comparações na busca binária: %d\n", comparacoes);
                break;

            case 0:
                printf("\nEncerrando a missão... Boa sorte na fuga! 🚀\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

// ======================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ======================================================

// Exibe todos os componentes
void mostrarComponentes(Componente comp[], int n) {
    printf("\n--- Componentes ---\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. Nome: %-20s | Tipo: %-15s | Prioridade: %d\n",
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

// Copia os dados originais para teste de cada algoritmo
void copiarComponentes(Componente origem[], Componente destino[], int n) {
    for (int i = 0; i < n; i++) destino[i] = origem[i];
}

// ----------------------
// BUBBLE SORT - NOME
// ----------------------
void bubbleSortNome(Componente comp[], int n) {
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
}

// ----------------------
// INSERTION SORT - TIPO
// ----------------------
void insertionSortTipo(Componente comp[], int n) {
    for (int i = 1; i < n; i++) {
        Componente chave = comp[i];
        int j = i - 1;

        while (j >= 0 && strcmp(comp[j].tipo, chave.tipo) > 0) {
            comparacoes++;
            comp[j + 1] = comp[j];
            j--;
        }
        comparacoes++;
        comp[j + 1] = chave;
    }
}

// ----------------------
// SELECTION SORT - PRIORIDADE
// ----------------------
void selectionSortPrioridade(Componente comp[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (comp[j].prioridade < comp[min].prioridade)
                min = j;
        }
        if (min != i) {
            Componente temp = comp[i];
            comp[i] = comp[min];
            comp[min] = temp;
        }
    }
}

// ----------------------
// BUSCA BINÁRIA - NOME
// ----------------------
int buscaBinariaPorNome(Componente comp[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;
        int cmp = strcmp(comp[meio].nome, nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}
