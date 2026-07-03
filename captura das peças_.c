#include <stdio.h>
#include <string.h>

#define LINHAS 8
#define COLUNAS 8

//====================================================
// FUNCAO RESPONSAVEL PELA CAPTURA (MORTE) DAS PECAS
//====================================================
void capturarPeca(char tabuleiro[LINHAS][COLUNAS][4],
                  int origemL, int origemC,
                  int destinoL, int destinoC)
{
    // Verifica se existe uma peca na posicao de destino
    if (strcmp(tabuleiro[destinoL][destinoC], " . ") != 0)
    {
        printf("\n=====================================\n");
        printf("        PECA CAPTURADA!\n");
        printf("A peca %s foi removida do jogo.\n",
               tabuleiro[destinoL][destinoC]);
        printf("=====================================\n");
    }

    // Move a peca atacante para a casa de destino
    strcpy(tabuleiro[destinoL][destinoC],
           tabuleiro[origemL][origemC]);

    // Limpa a casa de origem, deixando-a vazia
    strcpy(tabuleiro[origemL][origemC], " . ");
}
