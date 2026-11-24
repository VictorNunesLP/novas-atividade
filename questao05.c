#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TOTAL 4
#define MAX_VALORES 50

typedef struct {
    char nome[50];
    int idade;
    long long id;
    float valores[MAX_VALORES];
    int quantidade;
    double media;
} Participante;

typedef struct {
    double a;
    double b;
    int achados;
} Lados;

static long long fatorial(int n) {
    long long r = 1;

    while (n > 1) {
        r *= n--;
    }

    return r;
}

static long long potencia(long long base, int expoente) {
    long long r = 1;
    int k;

    for (k = 0; k < expoente; k++) {
        r *= base;
    }

    return r;
}

static int idRepetido(const Participante p[], int limite, long long id) {
    int k;

    for (k = 0; k < limite; k++) {
        if (p[k].id == id) {
            return 1;
        }
    }

    return 0;
}

static void definirId(Participante p[], int pos) {
    int expoente;

    p[pos].id = fatorial(p[pos].idade) / 2;

    if (!idRepetido(p, pos, p[pos].id)) {
        return;
    }

    printf("ID repetido. Calculando um novo ID.\n");
    expoente = p[pos].idade / 2;

    do {
        p[pos].id = potencia(fatorial(p[pos].idade / 2), expoente);
        expoente++;
    } while (idRepetido(p, pos, p[pos].id));
}

static double mediaPonderada(const float v[], int n) {
    double soma = 0, pesos = 0;
    int k;

    for (k = 0; k < n; k++) {
        soma += v[k] * (k + 1);
        pesos += k + 1;
    }

    return pesos == 0 ? 0 : soma / pesos;
}

static void lerValores(Participante *p, int n, Lados *lados) {
    int k;

    p->quantidade = n;

    printf("\nValores de %s:\n", p->nome);
    for (k = 0; k < n; k++) {
        printf("Digite o valor %d: ", k + 1);
        scanf("%f", &p->valores[k]);

        if (p->valores[k] >= 0 && lados->achados < 2) {
            if (lados->achados == 0) {
                lados->a = p->valores[k];
            } else {
                lados->b = p->valores[k];
            }
            lados->achados++;
        }
    }

    p->media = mediaPonderada(p->valores, n);
}

static int cmpNome(const void *x, const void *y) {
    return strcmp(((const Participante *)x)->nome,
                  ((const Participante *)y)->nome);
}

static const char *posicaoRelativa(double media, double diagonal) {
    if (media > diagonal) {
        return "Acima da diagonal";
    }
    if (media < diagonal) {
        return "Abaixo da diagonal";
    }
    return "Sobre a diagonal";
}

int main(void) {
    Participante grupo[TOTAL];
    Lados lados = {0, 0, 0};
    double diagonal = 0;
    int i, qtdValores;

    for (i = 0; i < TOTAL; i++) {
        printf("\nNome do participante: ");
        scanf(" %49[^\n]", grupo[i].nome);

        printf("Idade: ");
        scanf("%d", &grupo[i].idade);

        definirId(grupo, i);
        printf("ID: %lld\n", grupo[i].id);
    }

    printf("\nQuantidade de valores para cada participante (1 a %d): ", MAX_VALORES);
    scanf("%d", &qtdValores);

    if (qtdValores < 1 || qtdValores > MAX_VALORES) {
        printf("Quantidade invalida.\n");
        return 0;
    }

    for (i = 0; i < TOTAL; i++) {
        lerValores(&grupo[i], qtdValores, &lados);
    }

    qsort(grupo, TOTAL, sizeof(Participante), cmpNome);

    if (lados.achados == 2) {
        diagonal = sqrt(lados.a * lados.a + lados.b * lados.b);
    }

    printf("\nParticipantes em ordem alfabetica:\n");
    for (i = 0; i < TOTAL; i++) {
        if (lados.achados == 2) {
            printf("%s - ID: %lld - Media: %.2f - %s\n", grupo[i].nome,
                   grupo[i].id, grupo[i].media,
                   posicaoRelativa(grupo[i].media, diagonal));
        } else {
            printf("%s - ID: %lld - Media: %.2f\n", grupo[i].nome,
                   grupo[i].id, grupo[i].media);
        }
    }

    if (lados.achados == 2) {
        printf("\nDiagonal do retangulo: %.2f\n", diagonal);
    } else {
        printf("\nNao foi possivel calcular a diagonal.\n");
    }

    return 0;
}
