/* modo_ia.h — Declarações do Modo 2: IA adivinha por busca binária
 * Incluir em main.c e modo_ia.c
 */

#ifndef MODO_IA_H
#define MODO_IA_H

/* Limite máximo de tentativas calculado externamente via ceil(log2(n)).
 * Recebido por parâmetro — sem constante global hardcoded.
 * Para n=1000: ceil(log2(1000)) = 10
 * Para n=100:  ceil(log2(100))  = 7
 * Para n=10000: ceil(log2(10000)) = 14
 */

/* Executa o Modo IA completo.
 *
 * Parâmetros:
 *   limite_max — número máximo de tentativas permitidas (calculado por main)
 *   nivel_min  — limite inferior do intervalo (ex: 1)
 *   nivel_max  — limite superior do intervalo (ex: 1000)
 *
 * Retorno: void
 */
void modo_ia(int limite_max, int nivel_min, int nivel_max);

#endif /* MODO_IA_H */