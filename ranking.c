
#include <stdio.h>
#include <string.h>

#include "ranking.h"

/*
 * Organiza os jogadores em ordem crescente de tentativas.
 * Quanto menor o número de tentativas, melhor a posição.
 */
void ordenarRanking(Jogador ranking[], int total) {
    int i, j;
    Jogador temp;

    for (i = 0; i < total - 1; i++) {
        for (j = 0; j < total - 1 - i; j++) {
            if (ranking[j].tentativas >
                ranking[j + 1].tentativas) {

                temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
}

/*
 * Adiciona um jogador ao ranking.
 * O vetor e a quantidade de jogadores são recebidos
 * por parâmetro, evitando variáveis globais.
 */
void adicionarJogador(Jogador ranking[], int *total,
                      const char nome[], int tentativas) {

    if (ranking == NULL || total == NULL ||
        nome == NULL || nome[0] == '\0' || tentativas <= 0) {
        return;
    }

    if (*total >= MAX_JOGADORES) {
        ordenarRanking(ranking, *total);

        if (tentativas >= ranking[*total - 1].tentativas) {
            printf("Ranking cheio! Resultado nao registrado.\n");
            return;
        }

        (*total)--;
    }

    snprintf(ranking[*total].nome,
             sizeof(ranking[*total].nome), "%s", nome);

    ranking[*total].tentativas = tentativas;
    (*total)++;

    ordenarRanking(ranking, *total);
}

/*
 * Recupera os resultados armazenados em ranking.txt.
 */
void carregarRanking(Jogador ranking[], int *total) {
    FILE *arquivo;

    if (ranking == NULL || total == NULL) {
        return;
    }

    *total = 0;

    arquivo = fopen("ranking.txt", "r");

    if (arquivo == NULL) {
        return;
    }

    while (*total < MAX_JOGADORES &&
           fscanf(arquivo, " %49[^;];%d",
                  ranking[*total].nome,
                  &ranking[*total].tentativas) == 2) {

        if (ranking[*total].tentativas > 0) {
            (*total)++;
        }
    }

    fclose(arquivo);

    ordenarRanking(ranking, *total);
}

/*
 * Salva os jogadores no arquivo ranking.txt.
 */
void salvarRanking(const Jogador ranking[], int total) {
    FILE *arquivo;
    int i;

    if (ranking == NULL || total < 0) {
        return;
    }

    arquivo = fopen("ranking.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao salvar o ranking!\n");
        return;
    }

    for (i = 0; i < total && i < MAX_JOGADORES; i++) {
        fprintf(arquivo, "%s;%d\n",
                ranking[i].nome,
                ranking[i].tentativas);
    }

    fclose(arquivo);
}

/*
 * Exibe os jogadores do melhor resultado para o pior.
 */
void exibirRanking(Jogador ranking[], int total) {
    int i;

    if (ranking == NULL || total < 0) {
        return;
    }

    ordenarRanking(ranking, total);

    printf("\n========== RANKING ==========\n");

    if (total == 0) {
        printf("Nenhum jogador registrado ainda.\n");
    } else {
        for (i = 0; i < total; i++) {
            printf("%2d. %-20s | %2d tentativas\n",
                   i + 1,
                   ranking[i].nome,
                   ranking[i].tentativas);
        }
    }

    printf("=============================\n");
}
