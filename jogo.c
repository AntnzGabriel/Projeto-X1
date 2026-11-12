#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "jogo.h"

int jogarHumano(char nome[], int tamanhoNome) {

    int numeroSecreto;
    int palpite;
    int tentativas = 0;

    srand(time(NULL));
    numeroSecreto = rand() % 1000 + 1;

    printf("\n===== MODO HUMANO =====\n");
    printf("Descubra o numero secreto entre 1 e 1000!\n");

    while (tentativas < 10) {

        printf("\nTentativa %d de 10\n", tentativas + 1);
        printf("Digite seu palpite: ");

        if (scanf("%d", &palpite) != 1) {
            printf("Entrada invalida! Digite um numero.\n");

            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        if (palpite < 1 || palpite > 1000) {
            printf("Digite um numero entre 1 e 1000!\n");
            continue;
        }

        tentativas++;

        if (palpite == numeroSecreto) {

            printf("\nPARABENS! Voce acertou!\n");
            printf("Numero de tentativas: %d\n", tentativas);

            printf("Digite seu nome: ");
            if (fgets(nome, tamanhoNome, stdin) != NULL) {
                nome[strcspn(nome, "\n")] = '\0';
            }

            return tentativas;

        } else if (palpite < numeroSecreto) {

            printf("O numero secreto e MAIOR!\n");

        } else {

            printf("O numero secreto e MENOR!\n");
        }
    }

    printf("\nVoce perdeu! Suas tentativas acabaram.\n");
    printf("O numero secreto era: %d\n", numeroSecreto);

    nome[0] = '\0';

    return 0;
}