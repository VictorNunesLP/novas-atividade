#include <stdio.h>

#define TOTAL 15
#define TAM_NOME 50

static int primo(int n) {
    long long d;

    if (n < 2) {
        return 0;
    }
    if (n < 4) {
        return 1;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return 0;
    }

    for (d = 5; d * d <= n; d += 6) {
        if (n % d == 0 || n % (d + 2) == 0) {
            return 0;
        }
    }

    return 1;
}

static int aparecidoAntes(const int v[], int limite, int valor) {
    int k;

    for (k = 0; k < limite; k++) {
        if (v[k] == valor) {
            return 1;
        }
    }

    return 0;
}

static int contarIguais(const int v[], int n, int valor) {
    int k, qtd = 0;

    for (k = 0; k < n; k++) {
        if (v[k] == valor) {
            qtd++;
        }
    }

    return qtd;
}

static void mostrarPosicoes(const int v[], int n, int valor,
                            char nomes[][TAM_NOME]) {
    int k;

    printf("Animais relacionados pelas posicoes:\n");

    for (k = 0; k < n; k++) {
        if (v[k] == valor) {
            printf("Posicao %d: %s\n", k + 1, nomes[k]);
        }
    }
}

static void recadastrar(char nomes[][TAM_NOME], int *usados, int pedidos) {
    int k;

    printf("Cadastre %d nome(s) de animal:\n", pedidos);

    for (k = 0; k < pedidos && *usados < TOTAL; k++) {
        printf("Nome do animal: ");
        scanf(" %49[^\n]", nomes[*usados]);
        printf("Animal cadastrado: %s\n", nomes[*usados]);
        (*usados)++;
    }
}

int main(void) {
    int numeros[TOTAL];
    char animais[TOTAL][TAM_NOME];
    int i, vezes, usados = 0;

    for (i = 0; i < TOTAL; i++) {
        printf("Digite o numero %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    printf("\nCadastre 15 nomes de animais:\n");
    for (i = 0; i < TOTAL; i++) {
        printf("Animal %d: ", i + 1);
        scanf(" %49[^\n]", animais[i]);
    }

    printf("\nAnimais relacionados aos numeros:\n");

    for (i = 0; i < TOTAL; i++) {
        if (aparecidoAntes(numeros, i, numeros[i])) {
            continue;
        }

        vezes = contarIguais(numeros, TOTAL, numeros[i]);

        if (vezes <= 1) {
            continue;
        }

        printf("\nNumero %d aparece %d vezes.\n", numeros[i], vezes);

        if (primo(numeros[i]) && vezes % 2 != 0) {
            recadastrar(animais, &usados, vezes * numeros[i]);
        } else if (vezes % 2 == 0) {
            mostrarPosicoes(numeros, TOTAL, numeros[i], animais);
        }
    }

    return 0;
}
