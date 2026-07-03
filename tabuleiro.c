#include <stdio.h>
//cores do tabuleiro
#define BG_BRANCO "\x1b[47m"
#define BG_PRETO  "\x1b[40m" 
#define RESET     "\x1b[0m"
//struct para colocar as pecas
typedef struct {
    char cor;
} Casa;
//preencher o tabuleiro com cores
void inicializarTabuleiro(Casa tabuleiro[8][8]) {
    for (int linha = 0; linha < 8; linha++) {
        for (int coluna = 0; coluna < 8; coluna++) {
            if ((linha + coluna) % 2 == 0) {
                tabuleiro[linha][coluna].cor = 'B';
            } else {
                tabuleiro[linha][coluna].cor = 'P';
            }
        }
    }
}
//imprime o tabuleiro no console
void imprimirTabuleiro(Casa tabuleiro[8][8]) {
    printf("\n   A  B  C  D  E  F  G  H\n");

    for (int linha = 0; linha < 8; linha++) {
        printf("%d ", 8 - linha);//imprime a cordenada das linhas 
        for (int coluna = 0; coluna < 8; coluna++) {
            // Verifica a cor da casa para aplicar a cor certa
            if (tabuleiro[linha][coluna].cor == 'B') {
                printf("%s   %s", BG_BRANCO, RESET);//imprime as casas brancas 
            } else {
                printf("%s   %s", BG_PRETO, RESET);//imprime as casas pretas 
            }
        }
        
        printf("\n"); 
    }
    printf("\n");
}

int main() {
    Casa tabuleiro[8][8];// cria a matriz do tabuleiro

    inicializarTabuleiro(tabuleiro);
    imprimirTabuleiro(tabuleiro);

    return 0;
}