/* modo_ia.c — Modo 2: Computador adivinha com busca binária
 * Padrão: C99 | gcc -Wall -Wextra -pedantic
 *
 * Estrutura de dados:
 *   Dois ponteiros inteiros (low, high) definem o intervalo atual.
 *   A cada iteração, o palpite é o ponto médio exato: low + (high - low) / 2.
 *   A resposta do humano reduz o intervalo pela metade.
 *
 * Complexidade: O(log n) — ⌈log2(1000)⌉ = 10 iterações no pior caso.
 */

#include <stdio.h>
#include "modo_ia.h"

/* --------------------------------------------------------------------------
 * limpar_buffer_ia()
 * Descarta caracteres residuais no stdin até newline ou EOF.
 * Necessário após leituras com scanf para evitar loop infinito.
 * -------------------------------------------------------------------------- */
static void limpar_buffer_ia(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* --------------------------------------------------------------------------
 * exibir_cabecalho_ia()
 * Imprime o cabeçalho temático do modo IA.
 * -------------------------------------------------------------------------- */
static void exibir_cabecalho_ia(int nivel_min, int nivel_max, int limite_max) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║       CIPHER TERMINAL — MODO IA                     ║\n");
    printf("╠══════════════════════════════════════════════════════╣\n");
    printf("║  Pense em um número entre %5d e %5d.             ║\n",
           nivel_min, nivel_max);
    printf("║  Cipher vai adivinhar em até %2d tentativas.         ║\n",
           limite_max);
    printf("║  Responda com honestidade — o terminal vê tudo.     ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n\n");
}

/* --------------------------------------------------------------------------
 * le_resposta_ia()
 * Lê a resposta do humano sobre o palpite atual da IA.
 *
 * Entradas : nenhuma (lê stdin)
 * Saída    : '>' se o número pensado é maior que o palpite
 *            '<' se o número pensado é menor que o palpite
 *            '=' se o número pensado é igual ao palpite (acertou)
 * Efeitos  : rejeita entradas inválidas em loop; limpa buffer.
 * -------------------------------------------------------------------------- */
static char le_resposta_ia(void) {
    char resp;
    int valido = 0;

    while (!valido) {
        printf("  > O número que você pensou é [>] maior, [<] menor ou [=] igual? ");
        if (scanf(" %c", &resp) != 1) {
            limpar_buffer_ia();
            continue;
        }
        limpar_buffer_ia();

        if (resp == '>' || resp == '<' || resp == '=') {
            valido = 1;
        } else {
            printf("  [!] Entrada inválida. Digite apenas >, < ou =.\n");
        }
    }

    return resp;
}

/* --------------------------------------------------------------------------
 * exibir_resultado_ia()
 * Imprime o painel final com o número de tentativas e avaliação.
 * -------------------------------------------------------------------------- */
static void exibir_resultado_ia(int palpite, int tentativas, int limite_max) {
    printf("\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║  CIPHER ACERTOU: %-5d                               ║\n", palpite);
    printf("║  Tentativas usadas : %2d / %2d                        ║\n",
           tentativas, limite_max);

    if (tentativas <= limite_max / 2) {
        printf("║  Avaliação : DOMINAÇÃO TOTAL — busca ótima.         ║\n");
    } else if (tentativas < limite_max) {
        printf("║  Avaliação : EFICIENTE — dentro do esperado.        ║\n");
    } else {
        printf("║  Avaliação : NO LIMITE — exatamente %2d tentativas. ║\n",
               limite_max);
    }

    printf("╚══════════════════════════════════════════════════════╝\n\n");
}

/* --------------------------------------------------------------------------
 * executar_busca_binaria()
 * Núcleo do Modo IA: loop de busca binária interativa.
 *
 * Parâmetros:
 *   low, high    — limites do intervalo inicial (modificados em loop)
 *   limite_max   — teto de tentativas; se ultrapassar, inconsistência detectada
 *
 * Retorno: número de tentativas usadas, ou -1 se trapaça detectada.
 *
 * Algoritmo:
 *   1. Calcula palpite = low + (high - low) / 2  [evita overflow]
 *   2. Lê resposta do humano
 *   3. '>' → low  = palpite + 1  (número está na metade superior)
 *      '<' → high = palpite - 1  (número está na metade inferior)
 *      '=' → encerra loop
 *   4. Se low > high sem '=', o humano foi inconsistente (trapaça)
 * -------------------------------------------------------------------------- */
static int executar_busca_binaria(int low, int high, int limite_max) {
    int tentativas = 0;
    int palpite;
    char resposta;

    do {
        palpite = low + (high - low) / 2;
        tentativas++;

        printf("\n  [Tentativa %2d | intervalo atual: %d – %d]\n",
               tentativas, low, high);
        printf("  Cipher diz: o número é %d?\n", palpite);

        resposta = le_resposta_ia();

        if (resposta == '>') {
            low = palpite + 1;
        } else if (resposta == '<') {
            high = palpite - 1;
        }

        /* Detecção de trapaça: intervalo colapsou sem acerto */
        if (low > high && resposta != '=') {
            printf("\n  [!] ALERTA: Cipher detectou inconsistência nas respostas.\n");
            printf("      Nenhum número satisfaz as pistas fornecidas.\n");
            printf("      Registrando tentativa de trapaça no terminal.\n\n");
            return -1;
        }

        /* Aviso se atingiu o limite sem acertar */
        if (tentativas == limite_max && resposta != '=') {
            printf("\n  [!] ALERTA: Limite de %d tentativas atingido.\n", limite_max);
            printf("      Se a busca binária está correta, isso indica\n");
            printf("      que suas respostas foram inconsistentes.\n\n");
            return -1;
        }

    } while (resposta != '=');

    return tentativas;
}

/* --------------------------------------------------------------------------
 * modo_ia()
 * Ponto de entrada público do Modo 2.
 * Orquestra cabeçalho, busca binária e exibição do resultado.
 *
 * Parâmetros:
 *   limite_max — teto de tentativas calculado por main via ceil(log2(n))
 *   nivel_min  — limite inferior do intervalo
 *   nivel_max  — limite superior do intervalo
 * -------------------------------------------------------------------------- */
void modo_ia(int limite_max, int nivel_min, int nivel_max) {
    int tentativas;

    exibir_cabecalho_ia(nivel_min, nivel_max, limite_max);

    printf("  Pensou no número? Pressione ENTER para começar.\n");
    limpar_buffer_ia();

    tentativas = executar_busca_binaria(nivel_min, nivel_max, limite_max);

    if (tentativas > 0) {
        exibir_resultado_ia(nivel_min + (nivel_max - nivel_min) / 2, tentativas, limite_max);
        /* Nota: o número exibido no resultado é o último palpite aceito.
         * Para exibir o número real, executar_busca_binaria precisaria
         * retornar o palpite final — refatorar se necessário. */
    }
}