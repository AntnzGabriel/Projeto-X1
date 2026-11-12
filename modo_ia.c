#include <stdio.h>
#include "modo_ia.h"

static void limpar_buffer_ia(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

static void exibir_cabecalho_ia(int nivel_min, int nivel_max, int limite_max) {
    printf("\n");
    printf("+======================================================+\n");
    printf("|       CIPHER TERMINAL -- MODO IA                    |\n");
    printf("+======================================================+\n");
    printf("|  Pense em um numero entre %5d e %5d.             |\n",
           nivel_min, nivel_max);
    printf("|  Cipher vai adivinhar em ate %2d tentativas.         |\n",
           limite_max);
    printf("|  Responda com honestidade -- o terminal ve tudo.    |\n");
    printf("+======================================================+\n\n");
}

static char le_resposta_ia(void) {
    char resp;
    int valido = 0;

    while (!valido) {
        printf("  > O numero que voce pensou e [>] maior, [<] menor ou [=] igual? ");
        if (scanf(" %c", &resp) != 1) {
            limpar_buffer_ia();
            continue;
        }
        limpar_buffer_ia();

        if (resp == '>' || resp == '<' || resp == '=') {
            valido = 1;
        } else {
            printf("  [!] Entrada invalida. Digite apenas >, < ou =.\n");
        }
    }

    return resp;
}

static void exibir_resultado_ia(int palpite, int tentativas, int limite_max) {
    printf("\n");
    printf("+======================================================+\n");
    printf("|  CIPHER ACERTOU: %-5d                               |\n", palpite);
    printf("|  Tentativas usadas : %2d / %2d                        |\n",
           tentativas, limite_max);

    if (tentativas <= limite_max / 2) {
        printf("|  Avaliacao : DOMINACAO TOTAL -- busca otima.        |\n");
    } else if (tentativas < limite_max) {
        printf("|  Avaliacao : EFICIENTE -- dentro do esperado.       |\n");
    } else {
        printf("|  Avaliacao : NO LIMITE -- exatamente %2d tentativas.|\n",
               limite_max);
    }

    printf("+======================================================+\n\n");
}

static int executar_busca_binaria(int low, int high, int limite_max) {
    int tentativas = 0;
    int palpite;
    char resposta;

    do {
        palpite = low + (high - low) / 2;
        tentativas++;

        printf("\n  [Tentativa %2d | intervalo atual: %d - %d]\n",
               tentativas, low, high);
        printf("  Cipher diz: o numero e %d?\n", palpite);

        resposta = le_resposta_ia();

        if (resposta == '>') {
            low = palpite + 1;
        } else if (resposta == '<') {
            high = palpite - 1;
        }

        if (low > high && resposta != '=') {
            printf("\n  [!] ALERTA: Cipher detectou inconsistencia nas respostas.\n");
            printf("      Nenhum numero satisfaz as pistas fornecidas.\n");
            printf("      Registrando tentativa de trapaca no terminal.\n\n");
            return -1;
        }

        if (tentativas == limite_max && resposta != '=') {
            printf("\n  [!] ALERTA: Limite de %d tentativas atingido.\n", limite_max);
            printf("      Se a busca binaria esta correta, isso indica\n");
            printf("      que suas respostas foram inconsistentes.\n\n");
            return -1;
        }

    } while (resposta != '=');

    return tentativas;
}

void modo_ia(int limite_max, int nivel_min, int nivel_max) {
    int tentativas;

    exibir_cabecalho_ia(nivel_min, nivel_max, limite_max);

    printf("  Pensou no numero? Pressione ENTER para comecar.\n");
    limpar_buffer_ia();

    tentativas = executar_busca_binaria(nivel_min, nivel_max, limite_max);

    if (tentativas > 0) {
        exibir_resultado_ia(nivel_min + (nivel_max - nivel_min) / 2,
                            tentativas, limite_max);
    }
}