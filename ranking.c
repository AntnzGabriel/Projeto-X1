#include <stdio.h>
#include <string.h>
#include "ranking.h"

static Jogador ranking[MAX_JOGADORES];
static int total = 0;

void adicionarJogador(const char nome[], int tentativas) {

    if (total >= MAX_JOGADORES) {
        printf("Ranking cheio!\n");
        return;
    }

    strcpy(ranking[total].nome, nome);

    ranking[total].tentativas = tentativas;

    total++;
}