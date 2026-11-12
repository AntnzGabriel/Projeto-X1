
#include <stdio.h>

int main() {
    int opcao;

    do {
        printf("\n============================\n");
        printf("   ADIVINHE O NUMERO\n");
        printf("       VILAO CIPHER\n");
        printf("============================\n");

        printf("1 - Jogar\n");
        printf("2 - Modo IA\n");
        printf("3 - Ver ranking\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Modo humano selecionado!\n");
                break;

            case 2:
                printf("Modo IA selecionado!\n");
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
