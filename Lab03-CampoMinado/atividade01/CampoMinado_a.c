#include <stdio.h>
#include <stdlib.h>

typedef struct _mina {
    int x, y, r;
} Mina;

typedef struct _tanque {
    int x, y, res;
} Tanque;

int **CriaMatrizInt(int nlin, int ncol)
{
    int **campo = (int **)calloc(nlin,sizeof(int *));
    
    for (int l=0; l<nlin; l++){
        campo[l] = (int *)calloc(ncol,sizeof(int));
    }
    return(campo);
}

void DestroiMatrizInt(int ***campo, int nlin){
    if ((*campo) != NULL){
        for (int l=0; l<nlin; l++){
            free((*campo)[l]);
        }
        free(*campo);
        *campo = NULL;
    }
}


Mina *VetorM(int nbombas){ /*Cria um Vetor de Minas*/
    Mina *VetorMina = (Mina *)calloc(nbombas,sizeof(Mina));
    return(VetorMina);
}


int main()
{
    int nlin, ncol, nbombas;
    
    scanf("%dx%d", &ncol, &nlin); /* leitor do tamanho de campo */
    
    if ((ncol < 0) || (nlin < 0)){
        printf("-1"); /*leitura inválida - dimensões erradas*/
        return(0);
    }    

    scanf("%d", &nbombas); /* número de bombas */

    if (nbombas < 0){
        printf("-1"); /*leitura inválida - número negativo de bombas*/
        return(0);
    }

    int **campo = CriaMatrizInt(nlin, ncol);
    Mina *VetorMina = VetorM(nbombas);
    
    for (int i=0; i<nbombas; i++){
        scanf("%d %d %d", &VetorMina[i].x, &VetorMina[i].y, &VetorMina[i].r); /* leitura das bombas*/
    }
    
    for (int i=0; i<nbombas; i++){
        if ((VetorMina[i].x >= ncol) || (VetorMina[i].x < 0) || (VetorMina[i].y >= nlin) || (VetorMina[i].y < 0) || (VetorMina[i].r < 0)){
            printf("-1"); /*leitura inválida - mina não está no campo ou seu raio é negativo*/
            // DestroiMatrizInt(&campo, nlin);
            return(0);
        }
    }
    
    for (int i=0; i<nlin; i++){
        for (int j=0; j<ncol; j++){
            campo[i][j] = 0; /*inicialização do campo minado*/
        }
    }
    int lin_i, lin_f, col_i, col_f;
    for (int n=0; n<nbombas; n++){
        /*"quadrado de verificação"*/
        if(VetorMina[n].x - VetorMina[n].r < 0){col_i = 0;} else {col_i = VetorMina[n].x - VetorMina[n].r;}
        if(nlin - VetorMina[n].y - 1 - VetorMina[n].r < 0){lin_i = 0;} else {lin_i = nlin - VetorMina[n].y - 1 - VetorMina[n].r;}
        if(VetorMina[n].x + VetorMina[n].r > ncol){col_f = ncol - 1;} else {col_f = VetorMina[n].x + VetorMina[n].r;}
        if(nlin - VetorMina[n].y - 1 + VetorMina[n].r > nlin){lin_f = nlin - 1;} else {lin_f = nlin - VetorMina[n].y - 1 + VetorMina[n].r;}
        
        for (int i=lin_i; i<=lin_f; i++){
            for (int j=col_i; j<=col_f; j++){
                campo[i][j] += 1; /*atualização do campo com as bombas*/
            }
        }
    }
    
    
    Tanque tank;
    
    scanf("%d %d %d", &tank.x, &tank.y, &tank.res); /*leitura do tanque*/

    if ((tank.x<0) || (tank.y<0) || (tank.x>=ncol) || (tank.y>=nlin) || (tank.res < 1)){
        printf("-1"); /*leitura inválida*/
        DestroiMatrizInt(&campo, nlin);
        return(0);
    }

    if (campo[tank.y][tank.x] > tank.res){
        printf("Boom");
    } else {printf("Ufa");}

    DestroiMatrizInt(&campo, nlin);
    return 0;
}


