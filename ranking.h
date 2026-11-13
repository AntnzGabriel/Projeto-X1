

#ifndef RANKING_H
#define RANKING_H

#define MAX_JOGADORES 100

typedef struct {
    char nome[50];
    int tentativas;
} Jogador;

void adicionarJogador(const char nome[], int tentativas);

void carregarRanking();

void salvarRanking();

void ordenarRanking();

void exibirRanking();

#endif
