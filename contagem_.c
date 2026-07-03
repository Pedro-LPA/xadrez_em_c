#include <stdio.h>
#include <string.h>

#define LINHAS 8
#define COLUNAS 8


typedef struct {
    int brancas;
    int pretas;
} Placar;

Placar contarPecas(const char tabuleiro[LINHAS][COLUNAS][4]) {
    Placar jogo = {0, 0}; 

    for (int l = 0; l < LINHAS; l++) {
        for (int c = 0; c < COLUNAS; c++) {
            char primeiraLetra = tabuleiro[l][c][0];

            
            if (primeiraLetra == 'B' || primeiraLetra == 'b') {
                jogo.brancas++;
            } 
            else if (primeiraLetra == 'P' || primeiraLetra == 'p') {
                jogo.pretas++;
            }
        }
    }
    return jogo;
}

Placar capturarPeca(char tabuleiro[LINHAS][COLUNAS][4],
                    int origemL, int origemC,
                    int destinoL, int destinoC)
{
    
    if (strcmp(tabuleiro[destinoL][destinoC], " . ") != 0)
    {
        printf("\n=====================================\n");
        printf("        PEÇA CAPTURADA!\n");
        printf("A peca %s foi removida do jogo.\n", tabuleiro[destinoL][destinoC]);
        printf("=====================================\n");
    }

     
    strcpy(tabuleiro[destinoL][destinoC], tabuleiro[origemL][origemC]);

    
    strcpy(tabuleiro[origemL][origemC], " . ");

    Placar placarAtual = contarPecas(tabuleiro);
    
    printf("Peças restantes -> Brancas: %d | Pretas: %d\n", placarAtual.brancas, placarAtual.pretas);
    printf("=====================================\n");

    return placarAtual;
}