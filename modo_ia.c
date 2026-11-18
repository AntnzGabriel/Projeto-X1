
#include <stdio.h>
#include "modo_ia.h"

static void limpar_buffer_ia(void) {
    int c;

    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static void exibir_cabecalho_ia(int nivel_min, int nivel_max,
                                int limite_max) {
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

    while (1) {
        printf("  > O numero que voce pensou e [>] maior, [<] menor ou [=] igual? ");

        if (scanf(" %c", &resp) != 1) {
            if (feof(stdin)) {
                return '\0';
            }

            limpar_buffer_ia();
            continue;
        }

        limpar_buffer_ia();

        if (resp == '>' || resp == '<' || resp == '=') {
            return resp;
        }

        printf("  [!] Entrada invalida. Digite apenas >, < ou =.\n");
    }
}

static void exibir_resultado_ia(int palpite, int tentativas,
                                int limite_max) {
    printf("\n");
    printf("+======================================================+\n");
    printf("|  CIPHER ACERTOU: %-5d                               |\n", palpite);
    printf("|  Tentativas usadas : %2d / %2d                        |\n",
           tentativas, limite_max);

    if (tentativas <= limite_max / 2) {
        printf("|  Avaliacao : DOMINACAO TOTAL -- busca eficiente.    |\n");
    } else if (tentativas < limite_max) {
        printf("|  Avaliacao : EFICIENTE -- dentro do esperado.       |\n");
    } else {
        printf("|  Avaliacao : NO LIMITE -- exatamente %2d tentativas.|\n",
               limite_max);
    }

    printf("+======================================================+\n\n");
}

static int executar_busca_binaria(int low, int high,
                                  int limite_max, int *tentativas) {
    int palpite;
    char resposta;

    *tentativas = 0;

    while (*tentativas < limite_max && low <= high) {
        palpite = low + (high - low) / 2;
        (*tentativas)++;

        printf("\n  [Tentativa %2d | intervalo atual: %d - %d]\n",
               *tentativas, low, high);
        printf("  Cipher diz: o numero e %d?\n", palpite);

        resposta = le_resposta_ia();

        if (resposta == '\0') {
            printf("\n  [!] Entrada encerrada.\n");
            return -1;
        }

        if (resposta == '=') {
            return palpite;
        }

        if (resposta == '>') {
            low = palpite + 1;
        } else {
            high = palpite - 1;
        }

        if (low > high) {
            printf("\n  [!] Respostas inconsistentes!\n");
            printf("      Nenhum numero corresponde as suas respostas.\n");
            return -1;
        }
    }

    printf("\n  [!] Limite de tentativas atingido.\n");
    return -1;
}

void modo_ia(int limite_max, int nivel_min, int nivel_max) {
    int tentativas;
    int resultado;

    if (nivel_min > nivel_max || limite_max <= 0) {
        printf("Configuracao invalida para o modo IA.\n");
        return;
    }

    exibir_cabecalho_ia(nivel_min, nivel_max, limite_max);

    printf("  Pensou no numero? Pressione ENTER para comecar.\n");

    limpar_buffer_ia();

    resultado = executar_busca_binaria(nivel_min, nivel_max,
                                       limite_max, &tentativas);

    if (resultado >= 0) {
        exibir_resultado_ia(resultado, tentativas, limite_max);
    }
}
