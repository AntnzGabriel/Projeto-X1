
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>

#include "jogo.h"

int jogarHumano(char nome[], int tamanhoNome) {

    int numeroSecreto;
    int tentativas = 0;
    long palpite;

    if (nome == NULL || tamanhoNome <= 0) {
        return 0;
    }

    numeroSecreto = rand() % 1000 + 1;

    printf("\n===== MODO HUMANO =====\n");
    printf("Descubra o numero secreto entre 1 e 1000!\n");

    while (tentativas < 10) {

        char entrada[100];
        char *fim;

        printf("\nTentativa %d de 10\n", tentativas + 1);
        printf("Digite seu palpite: ");

        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf("\nEntrada encerrada.\n");
            nome[0] = '\0';
            return 0;
        }

        // Verifica se a entrada ultrapassou o tamanho do buffer.
        if (strchr(entrada, '\n') == NULL && !feof(stdin)) {
            int caractere;

            while ((caractere = getchar()) != '\n' &&
                   caractere != EOF) {
            }

            printf("Entrada muito longa! Tente novamente.\n");
            continue;
        }

        errno = 0;
        palpite = strtol(entrada, &fim, 10);

        // Ignora espaços depois do número.
        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (entrada == fim || *fim != '\0' || errno == ERANGE) {
            printf("Entrada invalida! Digite um numero inteiro.\n");
            continue;
        }

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
            } else {
                nome[0] = '\0';
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
