

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <time.h>

#include "jogo.h"
#include "modo_ia.h"
#include "ranking.h"

#define LIMITE_TENTATIVAS 10

static void exibir_menu(void) {
    printf("\n============================\n");
    printf("     ADIVINHE O NUMERO\n");
    printf("        VILAO CIPHER\n");
    printf("============================\n");
    printf("1 - Jogar\n");
    printf("2 - Modo IA\n");
    printf("3 - Ver ranking\n");
    printf("0 - Sair\n");
    printf("============================\n");
    printf("Escolha uma opcao: ");
}

static int ler_opcao(void) {
    char entrada[100];
    char *fim;
    long opcao;

    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    errno = 0;
    opcao = strtol(entrada, &fim, 10);

    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (entrada == fim || *fim != '\0' || errno == ERANGE ||
        opcao < 0 || opcao > 3) {
        return -1;
    }

    return (int)opcao;
}

static void jogar_humano(Jogador ranking[], int *total) {
    char nome[50];
    int tentativas;

    tentativas = jogarHumano(nome, sizeof(nome));

    if (tentativas > 0 && nome[0] != '\0') {
        adicionarJogador(ranking, total, nome, tentativas);
        salvarRanking(ranking, *total);
    }
}

int main(void) {
    int opcao;
    Jogador ranking[MAX_JOGADORES];
    int total = 0;

    srand((unsigned int)time(NULL));

    carregarRanking(ranking, &total);

    do {
        exibir_menu();
        opcao = ler_opcao();

        switch (opcao) {
            case 1:
                jogar_humano(ranking, &total);
                break;

            case 2:
                modo_ia(LIMITE_TENTATIVAS, 1, 1000);
                break;

            case 3:
                exibirRanking(ranking, total);
                break;

            case 0:
                printf("\nEncerrando o jogo...\n");
                break;

            default:
                printf("\nOpcao invalida! Escolha entre 0 e 3.\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
