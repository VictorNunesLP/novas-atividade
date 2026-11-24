#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL 12
#define MAX_PRODUTOS 144

typedef struct {
    char nome[50];
    float preco;
} Item;

typedef struct {
    int valor;
    int vezes;
} Contagem;

static int cmpDecrescente(const void *x, const void *y) {
    int a = *(const int *)x;
    int b = *(const int *)y;
    return (b > a) - (b < a);
}

static int cmpNome(const void *x, const void *y) {
    return strcmp(((const Item *)x)->nome, ((const Item *)y)->nome);
}

static int buscarContagem(const Contagem c[], int total, int valor) {
    int k;

    for (k = 0; k < total; k++) {
        if (c[k].valor == valor) {
            return k;
        }
    }

    return -1;
}

static int contarDistintos(const int v[], int n, Contagem c[]) {
    int total = 0, i, pos;

    for (i = 0; i < n; i++) {
        pos = buscarContagem(c, total, v[i]);

        if (pos < 0) {
            c[total].valor = v[i];
            c[total].vezes = 1;
            total++;
        } else {
            c[pos].vezes++;
        }
    }

    return total;
}

static void cadastrarProdutos(Item lista[], int *qtd, int pedidos) {
    int k;

    for (k = 0; k < pedidos; k++) {
        if (*qtd >= MAX_PRODUTOS) {
            continue;
        }

        printf("Nome do produto %d: ", k + 1);
        scanf(" %49[^\n]", lista[*qtd].nome);

        printf("Preco unitario: ");
        scanf("%f", &lista[*qtd].preco);

        (*qtd)++;
    }
}

int main(void) {
    int numeros[TOTAL], pares[TOTAL];
    Contagem cont[TOTAL];
    Item produtos[MAX_PRODUTOS];
    int qtdPares = 0, qtdProdutos = 0, distintos, i;

    for (i = 0; i < TOTAL; i++) {
        printf("Digite o %d numero: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    distintos = contarDistintos(numeros, TOTAL, cont);

    for (i = 0; i < distintos; i++) {
        if (cont[i].vezes % 2 == 0) {
            pares[qtdPares++] = cont[i].valor;
        } else if (cont[i].valor > 0) {
            cadastrarProdutos(produtos, &qtdProdutos, cont[i].valor);
        }
    }

    qsort(pares, qtdPares, sizeof(int), cmpDecrescente);
    qsort(produtos, qtdProdutos, sizeof(Item), cmpNome);

    printf("\nNumeros informados:\n");
    for (i = 0; i < TOTAL; i++) {
        printf("%d ", numeros[i]);
    }

    printf("\n\nOcorrencias:\n");
    for (i = 0; i < distintos; i++) {
        printf("%d aparece %d vez(es)\n", cont[i].valor, cont[i].vezes);
    }

    printf("\nProdutos cadastrados:\n");
    for (i = 0; i < qtdProdutos; i++) {
        printf("%s - R$ %.2f\n", produtos[i].nome, produtos[i].preco);
    }

    printf("\nNumeros com quantidade par, em ordem decrescente:\n");
    for (i = 0; i < qtdPares; i++) {
        printf("%d ", pares[i]);
    }

    printf("\n");
    return 0;
}
