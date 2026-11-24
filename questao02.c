#include <stdio.h>
#include <stdlib.h>

#define TOTAL 10

static int cmpCrescente(const void *x, const void *y) {
    int a = *(const int *)x;
    int b = *(const int *)y;
    return (a > b) - (a < b);
}

static int positivoPar(int x) {
    return x > 0 && x % 2 == 0;
}

static int negativoImpar(int x) {
    return x < 0 && x % 2 != 0;
}

static int filtrar(const int origem[], int n, int (*regra)(int), int destino[]) {
    int k, achados = 0;

    for (k = 0; k < n; k++) {
        if (regra(origem[k])) {
            destino[achados++] = origem[k];
        }
    }

    qsort(destino, achados, sizeof(int), cmpCrescente);
    return achados;
}

static void exibir(const char *titulo, const int v[], int n) {
    int k;

    printf("\n%s\n", titulo);
    for (k = 0; k < n; k++) {
        printf("%d ", v[k]);
    }
}

int main(void) {
    int numeros[TOTAL], pos[TOTAL], neg[TOTAL];
    int qtdPos, qtdNeg, i;

    for (i = 0; i < TOTAL; i++) {
        printf("Digite um numero: ");
        scanf("%d", &numeros[i]);
    }

    qtdPos = filtrar(numeros, TOTAL, positivoPar, pos);
    qtdNeg = filtrar(numeros, TOTAL, negativoImpar, neg);

    exibir("Positivos e pares:", pos, qtdPos);
    exibir("Negativos e impares:", neg, qtdNeg);

    printf("\n");
    return 0;
}
