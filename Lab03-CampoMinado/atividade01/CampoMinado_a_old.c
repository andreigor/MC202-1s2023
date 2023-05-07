#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int **CriaMatriz(int nlin, int ncol)
{
    //Cria um ponteiro de ponteiro que recebe a estrutura das linhas
    int **m = (int **)calloc(nlin, sizeof(int *));

    //Para cada linha (que é um ponteiro) vamos a estrutura das colunas
    for (int i = 0; i < nlin; i++)
    {
        m[i] = (int *)calloc(ncol, sizeof(int));
    }
    return(m);  
}

void DestroiMatriz(int ***m, int nlin)
{
    if ((*m) != NULL)
    {
        for (int i = 0; i < nlin; i++)
        {
            free((*m)[i]);
        }
        free(*m);
        *m = NULL;
    }
    
}


void DisplayMatrix(int **Tabuleiro, int Linha, int Coluna)
{
    for (int i = 0; i < Linha; i++)
    {
        for (int j = 0; j < Coluna; j++)
        {
            printf("%d ", Tabuleiro[i][j]);
        }
        printf("\n");    
    }
}


// O struct vira como um tipo de variavel, como o int, char, float...
typedef struct{
    int x;
    int y;
    int r;
} PosicaoBomba;

int main()
{
    // char Dimensoes[3];
    int n, x_tank, y_tank;

    /*
    Lendo os inputs
    a) Lê as dimensões do tabuleiro
        strtok: Ao colocar NULL, ela varrerá o conteúdo da última variável 
        que atuou e irá limpando ela usando o delimitador como pivô, devolvendo 
        as strings divididas pelo delimitador

    b)Lê as posições das minas, seus raios de alcance.
    */
    // scanf("%s", Dimensoes);
    // int Linha = atoi(strtok(Dimensoes, "x"));
    // int Coluna = atoi(strtok(NULL, "x")); // strtok retorna (char *)
    int Linha, Coluna;

    scanf("%dx%d\n", &Linha, &Coluna);
    // printf("Linha: %d, Coluna: %d\n", Linha, Coluna);
    if (Linha < 0 || Coluna < 0)
    {
        printf("-1");
        return 0;   
    }
    

    scanf("%d", &n);

    // printf("n: %d\n", n);

    //Vamos criar um vetor de structs
    PosicaoBomba *bombas = (PosicaoBomba *)calloc(n, sizeof(PosicaoBomba));

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &bombas[i].x,&bombas[i].y,&bombas[i].r);

        // printf("x: %d, y: %d\n", bombas[i].x, bombas[i].y);
        //Confere validade de posição
        if (
            bombas[i].x >= Linha || bombas[i].x < 0||
            bombas[i].y >= Coluna || bombas[i].y < 0
            )
        {
            printf("-1");
            return 0;
        }
    };

    //Lendo as info do tank
    scanf("%d %d", &x_tank, &y_tank);
    
    //Criaremos o tabuleiro e colocaremos 0 (Seguro) em todas suas posições
    int **Tabuleiro = CriaMatriz(Linha, Coluna);
    for (int j = 0; j < Linha; j++)
    {
        for (int k = 0; k < Coluna; k++)
        {
            Tabuleiro[j][k] = 0;
        }
    }
    
    //Para cada posição de bomba, iremos mudar de 0 para 1 as casas atingidas
    for (int l = 0; l < n; l++) //Lacço para as bombas
    { 
        for (int m = 0; m < 2*(bombas[l].r)+1; m++) //Laço para as linhas do Tabuleiro
        {
            for (int p = 0; p < 2*(bombas[l].r)+1; p++) //Laço para as colunas do Tabuleiro
            {
                int x_increment = (bombas[l].x)-(bombas[l].r)+m;
                int y_increment = (bombas[l].y)-(bombas[l].r)+p;
                if (
                    x_increment <= Linha-1 && x_increment >= 0 &&
                    y_increment <= Coluna-1 && y_increment >= 0)
                {
                    // printf("x: %d, y: %d\n", x_increment, y_increment);
                    Tabuleiro[x_increment][y_increment] = 1;
                }
            }
        }  
    }

    // printf("Cheguei ate aqui\n");
    //DisplayMatrix(Tabuleiro, Linha, Coluna);
    //Vamos checar se o tank está em uma posição Segura 
    if (Tabuleiro[x_tank][y_tank] == 1)
    {
        printf("Perigoso");
    }
    else
        {printf("Seguro");}
    free(bombas);
    DestroiMatriz(&Tabuleiro, Linha);
    return 0;
}