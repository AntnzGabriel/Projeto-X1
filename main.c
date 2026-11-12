#include <modo_ia.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>

static void limpar_buffer_main(void) {
    int c;
    while ((c = getchar()) != 'n\' && c ! EOF);

}


int main() {
    int opcao;
    int limite = (int)ceil(log2(1000));

    do {
        printf("\n============================\n");
        printf("   ADIVINHE O NUMERO\n");
        printf("       VILAO CIPHER\n");
        printf("============================\n");

        printf("1 - Jogar\n");
        printf("2 - Modo IA\n");
        printf("3 - Ver ranking\n");
        printf("0 - Sair\n");


        printf(" opcao: ")

        if (scanf("%d", &opcao) != 1) {
        limpar_buffer_main();
        opcao = -1;
        continue;
        }

        limpar_buffer_main();

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Modo humano selecionado!\n");
                break;

            case 2:
                printf("Modo IA selecionado!\n");
                modo_ia(limite, 1, 1000)
                break;

            case 3:
                printf("Ranking selecionado!\n");
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
