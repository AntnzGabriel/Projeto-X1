
#ifndef RANKING_H
#define RANKING_H

#define MAX_JOGADORES 10

/*
 * Estrutura que representa um jogador.
 * Armazena seu nome e a quantidade de tentativas
 * necessárias para vencer o jogo.
 */
typedef struct {
    char nome[50];
    int tentativas;
} Jogador;

/* Adiciona um jogador ao vetor e atualiza a quantidade. */
void adicionarJogador(Jogador ranking[], int *total,
                      const char nome[], int tentativas);

/* Carrega os resultados salvos no arquivo. */
void carregarRanking(Jogador ranking[], int *total);

/* Salva os resultados no arquivo. */
void salvarRanking(const Jogador ranking[], int total);

/* Ordena os jogadores pela menor quantidade de tentativas. */
void ordenarRanking(Jogador ranking[], int total);

/* Exibe os resultados ordenados. */
void exibirRanking(Jogador ranking[], int total);

#endif
