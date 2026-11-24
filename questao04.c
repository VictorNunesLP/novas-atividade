#include <stdio.h>

#define TOTAL 5

typedef struct {
    char nome[50];
    int numero;
    long long resultado;
    int premiado;
} Apostador;

static long long somaFibonacci(int termos) {
    long long atual = 0, seguinte = 1, tmp, soma = 0;

    while (termos-- > 0) {
        soma += atual;
        tmp = atual + seguinte;
        atual = seguinte;
        seguinte = tmp;
    }

    return soma;
}

static int primo(long long n) {
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

static int regraPrimo(const Apostador *a, double ref) {
    (void)ref;
    return primo(a->resultado);
}

static int regraPar(const Apostador *a, double ref) {
    (void)ref;
    return !a->premiado && a->resultado % 2 == 0;
}

static int regraAcimaDaMedia(const Apostador *a, double ref) {
    return !a->premiado && a->resultado > ref;
}

static int melhorPor(const Apostador v[], int n,
                     int (*regra)(const Apostador *, double), double ref) {
    int k, escolhido = -1;

    for (k = 0; k < n; k++) {
        if (!regra(&v[k], ref)) {
            continue;
        }
        if (escolhido == -1 || v[k].resultado > v[escolhido].resultado) {
            escolhido = k;
        }
    }

    return escolhido;
}

static void mostrarLugar(int lugar, const Apostador v[], int indice) {
    if (indice != -1) {
        printf("%dº lugar: %s\n", lugar, v[indice].nome);
    } else {
        printf("%dº lugar: Sem vencedor\n", lugar);
    }
}

int main(void) {
    Apostador lista[TOTAL];
    int i, primeiro, segundo, terceiro;
    long long total = 0;
    double media;

    for (i = 0; i < TOTAL; i++) {
        lista[i].premiado = 0;

        printf("Nome do apostador: ");
        scanf(" %49[^\n]", lista[i].nome);

        do {
            printf("Digite um numero inteiro positivo: ");
            scanf("%d", &lista[i].numero);
        } while (lista[i].numero <= 0);

        lista[i].resultado = somaFibonacci(lista[i].numero);
        total += lista[i].resultado;
    }

    media = total / (double)TOTAL;

    primeiro = melhorPor(lista, TOTAL, regraPrimo, media);
    if (primeiro != -1) {
        lista[primeiro].premiado = 1;
    }

    segundo = melhorPor(lista, TOTAL, regraPar, media);
    if (segundo != -1) {
        lista[segundo].premiado = 1;
    }

    terceiro = melhorPor(lista, TOTAL, regraAcimaDaMedia, media);

    printf("\nVencedores:\n");
    mostrarLugar(1, lista, primeiro);
    mostrarLugar(2, lista, segundo);
    mostrarLugar(3, lista, terceiro);

    return 0;
}
