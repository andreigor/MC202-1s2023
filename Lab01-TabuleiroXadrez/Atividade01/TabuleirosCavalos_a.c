#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8 // tamanho do tabuleiro

void print_possible_moves(char *moves[]) {
    for (int i = 0; i < 8; i++) {
        printf("%s\n", moves[i]);
    }
}

int main()
{
    char col;
    int linha;
    scanf("%c %d", &col, &linha);

    // converte a letra para o número correspondente na matriz
    int y = col - 'A';
    int x = N - linha;

    // marca a posição inicial do cavalo na matriz

    // movimentos do cavalo na matriz
    int dlinhas[8] = {-2, -2, -1, 1, 2, 2, 1, -1}; // Orientação positiva é de cima para baixo
    int dcolunas[8] = {-1, 1, 2, 2, 1, -1, -2, -2}; // Orientação positiva é da esquerda para direita

    // vetor de strings para armazenar os movimentos do cavalo


    // verifica se o Cavalo foi inserido inicialmente no tabuleiro
    if (y < N && y >= 0 && x <= N && x >= 0) { 
        
        for (int i = 0; i < 8; i++) {
            int next_x = x + dlinhas[i];
            int next_y = y + dcolunas[i];

            // atualiza a matriz apenas para os movimentos possíveis do cavalo
            if (next_x >= 0 && next_x < N && next_y >= 0 && next_y < N) { // verifica se a próxima jogada está no tabuleiro
                // adiciona o movimento ao vetor de strings
                printf( "%c %d\n", 'A'+next_y, N-next_x);
            // } else {
            //     movimentos[i] = NULL;
            // }
        }
    // } else { // Limpa o lixo que seria impresso para o cavalo inicializado fora do tabuleiro
    //     for (int i = 0; i < 8; i++) 
    //         movimentos[i] = NULL;
    }
    // imprime a lista de movimentos em sentido horário
    // print_possible_moves(movimentos);

    // limpa o vetor movimentos
    // free(movimentos);
    // free(move);

    return 0;
}
}
