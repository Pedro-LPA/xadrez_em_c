#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINHAS 8
#define COLUNAS 8

// Função para desenhar o tabuleiro na tela de forma organizada
void imprimirTabuleiro(char tab[LINHAS][COLUNAS][4], int turno) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    printf("=== XADREZ SIMPLIFICADO ===\n");
    printf("Turno: Jogam as %s!\n\n", (turno == 1) ? "BRANCAS (B)" : "PRETAS (P)");
    
    // Imprime as coordenadas das colunas alinhadas
    printf("     0   1   2   3   4   5   6   7\n");
    printf("   ---------------------------------\n");
    for (int i = 0; i < LINHAS; i++) {
        printf("%d | ", i); // Imprime a coordenada da linha
        for (int j = 0; j < COLUNAS; j++) {
            printf("%s| ", tab[i][j]);
        }
        printf("\n   ---------------------------------\n");
    }
}

// Função que valida o movimento específico de cada peça de xadrez
int validarMovimento(char peca[4], int origL, int origC, int destL, int destC) {
    int difL = destL - origL;
    int difC = destC - origC;
    int absL = abs(difL);
    int absC = abs(difC);

    // Se não saiu do lugar, o movimento é inválido
    if (difL == 0 && difC == 0) return 0;

    char tipo = peca[0];
    char cor = peca[1];

    // REGRA DO PEÃO (P)
    if (tipo == 'P') {
        if (cor == 'B') {
            // Peão Branco: Avança 1 casa para cima (linha diminui). 
            // Se estiver na linha inicial (6), pode avançar 2 casas.
            if (origL == 6 && difL == -2 && difC == 0) return 1;
            return (difL == -1 && difC == 0);
        } else {
            // Peão Preto: Avança 1 casa para baixo (linha aumenta).
            // Se estiver na linha inicial (1), pode avançar 2 casas.
            if (origL == 1 && difL == 2 && difC == 0) return 1;
            return (difL == 1 && difC == 0);
        }
    }

    // REGRA DA TORRE (T)
    if (tipo == 'T') {
        // Move qualquer distância em linha reta (horizontal ou vertical)
        return (difL == 0 || difC == 0);
    }

    // REGRA DO CAVALO (C)
    if (tipo == 'C') {
        // Move em formato de "L" (2 em um sentido e 1 no outro)
        return ((absL == 2 && absC == 1) || (absL == 1 && absC == 2));
    }

    // REGRA DO BISPO (B)
    if (tipo == 'B') {
        // Move qualquer distância estritamente nas diagonais
        return (absL == absC);
    }

    // REGRA DA DAMA (D)
    if (tipo == 'D') {
        // Combina os movimentos da Torre e do Bispo
        return (difL == 0 || difC == 0 || absL == absC);
    }

    // REGRA DO REI (R)
    if (tipo == 'R') {
        // Move apenas 1 casa para qualquer direção
        return (absL <= 1 && absC <= 1);
    }

    return 0; 
}

int main() {
    char tabuleiro[LINHAS][COLUNAS][4];
    
    // 1. INICIALIZAÇÃO DO TABULEIRO COMPLETO DE XADREZ
    // Define espaços vazios
    for(int i = 0; i < LINHAS; i++) {
        for(int j = 0; j < COLUNAS; j++) {
            strcpy(tabuleiro[i][j], " . ");
        }
    }

    // Posiciona Peças Pretas (Linhas 0 e 1)
    strcpy(tabuleiro[0][0], "TP "); strcpy(tabuleiro[0][7], "TP "); // Torres
    strcpy(tabuleiro[0][1], "CP "); strcpy(tabuleiro[0][6], "CP "); // Cavalos
    strcpy(tabuleiro[0][2], "BP "); strcpy(tabuleiro[0][5], "BP "); // Bispos
    strcpy(tabuleiro[0][3], "DP "); // Dama Preta
    strcpy(tabuleiro[0][4], "RP "); // Rei Preto
    for(int j = 0; j < COLUNAS; j++) strcpy(tabuleiro[1][j], "PP "); // Peões

    // Posiciona Peças Brancas (Linhas 6 e 7)
    for(int j = 0; j < COLUNAS; j++) strcpy(tabuleiro[6][j], "PB "); // Peões
    strcpy(tabuleiro[7][0], "TB "); strcpy(tabuleiro[7][7], "TB "); // Torres
    strcpy(tabuleiro[7][1], "CB "); strcpy(tabuleiro[7][6], "CB "); // Cavalos
    strcpy(tabuleiro[7][2], "BB "); strcpy(tabuleiro[7][5], "BB "); // Bispos
    strcpy(tabuleiro[7][3], "DB "); // Dama Branca
    strcpy(tabuleiro[7][4], "RB "); // Rei Branco

    int turno = 1; // 1 = Brancas, 2 = Pretas
    int posL, posC;  // Origem
    int novaL, novaC; // Destino

    while (1) {
        imprimirTabuleiro(tabuleiro, turno);

        // 2. SELEÇÃO DA PEÇA (ORIGEM)
        printf("\n[ORIGEM] Escolha a LINHA da peca (0-7) ou -1 para sair: ");
        if (scanf("%d", &posL) && posL == -1) break;
        
        printf("[ORIGEM] Escolha a COLUNA da peca (0-7): ");
        scanf("%d", &posC);

        // Valida limites do tabuleiro
        if (posL < 0 || posL >= LINHAS || posC < 0 || posC >= COLUNAS) {
            printf("\n⚠️ Coordenada fora do tabuleiro! Pressione Enter...");
            getchar(); getchar(); continue;
        }

        char pecaSelecionada[4];
        strcpy(pecaSelecionada, tabuleiro[posL][posC]);

        // Valida se escolheu uma casa vazia
        if (strcmp(pecaSelecionada, " . ") == 0) {
            printf("\n⚠️ Nao ha nenhuma peca nessa casa! Pressione Enter...");
            getchar(); getchar(); continue;
        }

        // Valida a cor da peça com base no turno atual
        if ((turno == 1 && pecaSelecionada[1] != 'B') || (turno == 2 && pecaSelecionada[1] != 'P')) {
            printf("\n⚠️ Essa peca nao pertence ao seu turno! Pressione Enter...");
            getchar(); getchar(); continue;
        }

        // 3. DESTINO DA PEÇA
        printf("\nPeca \"%s\" selecionada com sucesso!", pecaSelecionada);
        printf("\n[DESTINO] Escolha a LINHA para mover (0-7): ");
        scanf("%d", &novaL);
        printf("[DESTINO] Escolha a COLUNA para mover (0-7): ");
        scanf("%d", &novaC);

        // Verifica limites do destino
        if (novaL < 0 || novaL >= LINHAS || novaC < 0 || novaC >= COLUNAS) {
            printf("\n⚠️ Destino fora do tabuleiro! Pressione Enter...");
            getchar(); getchar(); continue;
        }

        // Evita capturar uma peça da sua própria cor
        char pecaDestino[4];
        strcpy(pecaDestino, tabuleiro[novaL][novaC]);
        if (strcmp(pecaDestino, " . ") != 0 && pecaDestino[1] == pecaSelecionada[1]) {
            printf("\n⚠️ Movimento invalido! Voce nao pode capturar sua propria peca. Pressione Enter...");
            getchar(); getchar(); continue;
        }

        // 4. VALIDAÇÃO E MOVIMENTAÇÃO
        if (validarMovimento(pecaSelecionada, posL, posC, novaL, novaC)) {
            // Executa o movimento e limpa a casa anterior
            strcpy(tabuleiro[novaL][novaC], pecaSelecionada);
            strcpy(tabuleiro[posL][posC], " . ");

            // Alterna o turno do jogo
            turno = (turno == 1) ? 2 : 1;
        } else {
            printf("\n⚠️ Esse nao e um movimento valido para esta peca! Pressione Enter...");
            getchar(); getchar();
        }
    }

    printf("\nPartida finalizada. Obrigado por testar!\n");
    return 0;
}