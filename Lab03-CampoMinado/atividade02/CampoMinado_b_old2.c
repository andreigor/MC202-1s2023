#include <stdio.h>
#include <malloc.h> // biblioteca para alocação de memória
#include <stdlib.h> // biblioteca para separar o que tem dentro da matriz

typedef struct Bomba {
    int x;
    int y;
    int raio;
} Bomba; // Definir a bomba com os seus parametros

typedef struct Tanque {
    int xtanque;
    int ytanque;
    int res;
} Tanque; // Definir o tanque e os seus parametros

int main(){

    int nlin;
    int ncol;
    int numbomba;
    int x;
    int y;
    int raio;
    int contador = 0;
    int xtanque;
    int ytanque;
    int res;

    scanf("%dx%d", &nlin, &ncol);

    scanf("%d", &numbomba);

    if ((nlin < 0) || (ncol < 0) || (numbomba < 0)){
        printf("-1");
        exit (0);
    }// para ve se ele esta fora do tabuleiro 

    Bomba *bombas = calloc(numbomba,sizeof(Bomba));

    while (numbomba != contador) { 
        scanf(" %d %d %d", &x, &y, &raio);
        bombas[contador].x = x;
        bombas[contador].y = y;
        bombas[contador].raio = raio;
        if ((bombas[contador].x < 0) || (bombas[contador].y < 0) || (bombas[contador].raio < 0)){
            printf("-1");
            exit (0);
        }// para ve se ele esta fora do tabuleiro o x, y e o raio
        contador++;
    }// vetor de bombas para ir contando uma a uma 

    scanf("%d %d %d", &xtanque, &ytanque, &res);

    if ((xtanque < 0) || (ytanque < 0) || (xtanque >= nlin) || (ytanque >= ncol) || (res < 0)){
        printf("-1");
        exit (0);
    }// para ve se ele esta fora do tabuleiro os valores de x e y do tanque e sua resistencia ser negativa

    Tanque *armadura = calloc(res,sizeof(Tanque));

    // PARA o numero de bombar e o laco.. enquanto bombas > armadura/res = Boom else Ufa

    for(int i = 0; i < numbomba; i ++){
        if ((xtanque > bombas[i].x - bombas[i].raio) && (xtanque < bombas[i].x + bombas[i].raio) && (ytanque < bombas[i].y + bombas[i].raio) && (ytanque > bombas[i].y - bombas[i].raio)){
            if ((xtanque > res) && (ytanque > res)) {
                printf("Boom");
                exit (0); // as bombas explodem o tanque
            } 
        }

    }

    printf("Ufa"); // caso nenhuma bomba esteja no raio do tanque

    free(bombas); // desalocou a memoria do vetor bombas

    free(armadura); // desalocou a memoria do vetor armadura

    return (0);
}
