 #include <stdio.h>
#include <locale.h> 


typedef enum {
    PEAO,
    CAVALO,
    BISPO,
    TORRE,
    RAINHA,  
    REI
} TipoPeca;


const char* obterEmoji(TipoPeca peca) {
    switch (peca) {
        case REI:    return " 🤴 ";   // Rei :prince:
        case RAINHA: return " 👑 ";   // Rainha :crown: 
        case PEAO:   return " ♟️ ";   // Peão :chess_pawn:
        case CAVALO: return " 🐴 ";   // Cavalo :horse:
        case TORRE:  return " 🗼 ";   // Torre :tokyo_tower:
        case BISPO:  return " ✝️ ";   // Bispo :cross:
        default:     return " ❓ ";   // Caso ocorra erro
    }
}


int main() {
   
    setlocale(LC_ALL, "");

    printf("\n=== Design das Peças (Apenas Emojis) ===\n\n");

    
    TipoPeca todas[] = {REI, RAINHA, BISPO, CAVALO, TORRE, PEAO};
    const char* nomes[] = {"Rei", "Rainha/Dama", "Bispo", "Cavalo", "Torre", "Peão"};

    for (int i = 0; i < 6; i++) 
        printf("  %-12s -> %s\n", nomes[i], obterEmoji(todas[i]));
  

    return 0;
}