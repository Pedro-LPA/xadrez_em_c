#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

#define LINHAS 8
#define COLUNAS 8

#define BG_BRANCO "\x1b[47m"
#define BG_PRETO  "\x1b[1;30m" 
#define RESET     "\x1b[0m"

typedef struct {
    int brancas;
    int pretas;
} Placar;


const char* obterEmoji(char tipo) {
    switch (tipo) {
        case 'R': return "🤴"; 
        case 'D': return "👑"; 
        case 'P': return "♟️"; 
        case 'C': return "🐴"; 
        case 'T': return "🗼"; 
        case 'B': return "✝️"; 
        default:  return "  "; 
    }
}

// Valores das peças do xadrez

int obterValorPeca(char tipo) {
    switch (tipo) {
        case 'P': return 1; 
        case 'C': return 3; 
        case 'B': return 3; 
        case 'T': return 5; 
        case 'D': return 9; 
        case 'R': return 0; 
        default:  return 0;
    }
}

// Funçao para contagem das peças

Placar contarPecas(char tabuleiro[LINHAS][COLUNAS][4]) {
    Placar jogo = {0, 0};
    for (int l = 0; l < LINHAS; l++) { 
        for (int c = 0; c < COLUNAS; c++) {
            char tipoDaPeca = tabuleiro[l][c][0];
            char corDaPeca = tabuleiro[l][c][1]; 
            
            int valor = obterValorPeca(tipoDaPeca);
            
            if (corDaPeca == 'B') {
                jogo.brancas += valor; 
            } else if (corDaPeca == 'P') {
                jogo.pretas += valor; 
            }
        }
    }
    return jogo; 
}


// Impressão do tabuleiro

void imprimirTabuleiro(char tab[LINHAS][COLUNAS][4], int turno) {
    #ifdef _WIN32
        system("cls"); 
    #else
        system("clear"); 
    #endif
    
    printf("=== XADREZ COMPLETO ===\n");
    printf("Turno: Jogam as %s!\n\n", (turno == 1) ? "BRANCAS (B)" : "PRETAS (P)"); 
    
    printf("     0    1    2    3    4    5    6    7\n"); 
    
    for (int l = 0; l < LINHAS; l++) { 
        printf(" %d ", l); 
        for (int c = 0; c < COLUNAS; c++) {
            const char* corFundo = ((l + c) % 2 == 0) ? BG_BRANCO : BG_PRETO; 
            
            char tipo = tab[l][c][0];
            char cor = tab[l][c][1];

            if (strcmp(tab[l][c], " . ") == 0) {
                printf("%s    %s", corFundo, RESET); 
            } else {
                printf("%s %s%c %s", corFundo, obterEmoji(tipo), cor, RESET); 
            }
        }
        printf("\n"); 
    }
    printf("\n");
}

// Função comer peças

Placar capturarPeca(char tabuleiro[LINHAS][COLUNAS][4], int origemL, int origemC, int destinoL, int destinoC) {
    if (strcmp(tabuleiro[destinoL][destinoC], " . ") != 0) { 
        printf("\n=====================================\n");
        printf("        PECA CAPTURADA!\n"); 
        printf("A peca %s foi removida do jogo.\n", tabuleiro[destinoL][destinoC]); 
        printf("=====================================\n"); 
    }

    strcpy(tabuleiro[destinoL][destinoC], tabuleiro[origemL][origemC]); 
    strcpy(tabuleiro[origemL][origemC], " . "); 

    Placar placarAtual = contarPecas(tabuleiro);
    printf("Pontuacao Total -> Brancas: %d | Pretas: %d\n", placarAtual.brancas, placarAtual.pretas); 
    
    if (placarAtual.brancas > placarAtual.pretas) {
        printf("VANTAGEM: Brancas (+%d)\n", placarAtual.brancas - placarAtual.pretas);
    } else if (placarAtual.pretas > placarAtual.brancas) {
        printf("VANTAGEM: Pretas (+%d)\n", placarAtual.pretas - placarAtual.brancas);
    } else {
        printf("VANTAGEM: Jogo Empatado (0)\n");
    }
    
    printf("=====================================\n"); 

    return placarAtual;
}

// Verificação de movimentos válidos

int validarMovimento(char peca[4], int origL, int origC, int destL, int destC, char pecaDestino[4]) {
    int difL = destL - origL; 
    int difC = destC - origC; 
    int absL = abs(difL);
    int absC = abs(difC); 

    if (difL == 0 && difC == 0) return 0; 

    char tipo = peca[0]; 
    char cor = peca[1];
    
    int temInimigo = (strcmp(pecaDestino, " . ") != 0 && pecaDestino[1] != cor);

    if (tipo == 'P') { 
        if (cor == 'B') {
            if (difL == -1 && absC == 1 && temInimigo) return 1; 
            if (difC == 0 && !temInimigo) { 
                if (origL == 6 && difL == -2) return 1; 
                if (difL == -1) return 1; 
            }
            return 0; 
        } else {
            if (difL == 1 && absC == 1 && temInimigo) return 1; 
            if (difC == 0 && !temInimigo) { 
                if (origL == 1 && difL == 2) return 1; 
                if (difL == 1) return 1; 
            }
            return 0; 
        }
    }
    
    if (tipo == 'T') return (difL == 0 || difC == 0); 
    if (tipo == 'C') return ((absL == 2 && absC == 1) || (absL == 1 && absC == 2)); 
    if (tipo == 'B') return (absL == absC); 
    if (tipo == 'D') return (difL == 0 || difC == 0 || absL == absC); 
    if (tipo == 'R') return (absL <= 1 && absC <= 1); 

    return 0; 
}

int main() {
    setlocale(LC_ALL, ""); 
    char tabuleiro[LINHAS][COLUNAS][4]; 

    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            strcpy(tabuleiro[i][j], " . "); 
        }
    }

    strcpy(tabuleiro[0][0], "TP "); strcpy(tabuleiro[0][7], "TP "); 
    strcpy(tabuleiro[0][1], "CP "); strcpy(tabuleiro[0][6], "CP "); 
    strcpy(tabuleiro[0][2], "BP "); strcpy(tabuleiro[0][5], "BP "); 
    strcpy(tabuleiro[0][3], "DP "); 
    strcpy(tabuleiro[0][4], "RP "); 
    for(int j = 0; j < COLUNAS; j++) strcpy(tabuleiro[1][j], "PP "); 

    for(int j = 0; j < COLUNAS; j++) strcpy(tabuleiro[6][j], "PB "); 
    strcpy(tabuleiro[7][0], "TB "); strcpy(tabuleiro[7][7], "TB "); 
    strcpy(tabuleiro[7][1], "CB "); strcpy(tabuleiro[7][6], "CB "); 
    strcpy(tabuleiro[7][2], "BB "); strcpy(tabuleiro[7][5], "BB "); 
    strcpy(tabuleiro[7][3], "DB "); 
    strcpy(tabuleiro[7][4], "RB "); 

    int turno = 1; 
    int posL, posC, novaL, novaC; 

    while (1) {
        imprimirTabuleiro(tabuleiro, turno); 

        printf("\n[ORIGEM] Escolha a LINHA da peca (0-7) ou -1 para sair: "); 
        if (scanf("%d", &posL) && posL == -1) break; 
        
        printf("[ORIGEM] Escolha a COLUNA da peca (0-7): ");
        scanf("%d", &posC); 

        if (posL < 0 || posL >= LINHAS || posC < 0 || posC >= COLUNAS) { 
            printf("\n Coordenada fora do tabuleiro! Pressione Enter..."); 
            getchar(); getchar(); continue; 
        }

        char pecaSelecionada[4];
        strcpy(pecaSelecionada, tabuleiro[posL][posC]); 

        if (strcmp(pecaSelecionada, " . ") == 0) { 
            printf("\n⚠️ Nao ha nenhuma peca nessa casa! Pressione Enter...");
            getchar(); getchar(); continue; 
        }

        if ((turno == 1 && pecaSelecionada[1] != 'B') || (turno == 2 && pecaSelecionada[1] != 'P')) { 
            printf("\n Essa peca nao pertence ao seu turno! Pressione Enter..."); 
            getchar(); getchar(); continue; 
        }

        printf("\nPeca \"%s\" selecionada com sucesso!", pecaSelecionada); 
        printf("\n[DESTINO] Escolha a LINHA para mover (0-7): "); 
        scanf("%d", &novaL);
        printf("[DESTINO] Escolha a COLUNA para mover (0-7): ");
        scanf("%d", &novaC); 

        if (novaL < 0 || novaL >= LINHAS || novaC < 0 || novaC >= COLUNAS) { 
            printf("\n Destino fora do tabuleiro! Pressione Enter..."); 
            getchar(); getchar(); continue; 
        }

        char pecaDestino[4];
        strcpy(pecaDestino, tabuleiro[novaL][novaC]); 
        if (strcmp(pecaDestino, " . ") != 0 && pecaDestino[1] == pecaSelecionada[1]) { 
            printf("\n Movimento invalido! Voce nao pode capturar sua propria peca. Pressione Enter..."); 
            getchar(); getchar(); continue; 
        }

        if (validarMovimento(pecaSelecionada, posL, posC, novaL, novaC, pecaDestino)) { 
            capturarPeca(tabuleiro, posL, posC, novaL, novaC); 
            
            printf("\nPressione Enter para ir ao proximo turno...");
            getchar(); getchar();

            turno = (turno == 1) ? 2 : 1; 
        } else {
            printf("\n Esse nao e um movimento valido para esta peca! Pressione Enter..."); 
            getchar(); getchar(); 
        }
    }

    printf("\nPartida finalizada.\n"); 
    return 0;
}