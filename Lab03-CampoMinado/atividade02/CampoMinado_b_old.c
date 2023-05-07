#include <stdlib.h>
#include <stdio.h>

typedef struct _bomb{
  int x, y, raio;

} bomb;

typedef struct _tank{
    int x, y, res;

} tank;

bomb *CriaBomba(int n){
    bomb *bomba = (bomb *)calloc(n,sizeof(bomb));

    return bomba;
}

int ChecaSeTemBomba(int n, tank tanque, bomb *bomba){
    
    int i;
    
    for(i=0;i<n;i++){
        if((-bomba[i].raio <= (tanque.x - bomba[i].x)) && ((tanque.x - bomba[i].x) <= bomba[i].raio)){
            if((-bomba[i].raio <= (tanque.y - bomba[i].y)) && ((tanque.y - bomba[i].y) <= bomba[i].raio)){
                tanque.res -= 1;
                if(tanque.res <0){
                    return 1;
                }
            }
        }
    }
    return 0;
    
}

void LiberaBomba(bomb **bomba){
    free(*bomba);
    *bomba=NULL;
    
}


int main (){
    
    int dimx, dimy;		/*dimensoes do tabuleiro */
    int n, checa;		    	/*numero de bombas */
    int i;
    bomb *bomba;
    tank tanque;
 


    /*
    1 - le tamanho do tabuleiro
    2 - le numero de bombas
    3 - le caracteristicas da bomba
    4 - le caracteristicas do tanque
    */

    scanf("%ix%i",&dimx,&dimy);
    if(dimx <= 0 || dimy <= 0){
        printf("-1");
        exit(0);
    }

    scanf("\n%i",&n);
    if(n < 0){
        printf("-1");
        exit(0);
    }
    
    bomba = CriaBomba(n);
    
    for (i=0;i<n;i++){
        scanf("\n%i %i %i",&bomba[i].x, &bomba[i].y, &bomba[i].raio);
        if((bomba[i].x < 0 || bomba[i].x>= dimx) || (bomba[i].y < 0 || bomba[i].y>= dimy) || (bomba[i].raio <0)){
            printf("-1");
            exit(0);
        }
    }
    
    scanf("\n%i %i %i", &tanque.x, &tanque.y, &tanque.res);
    if((tanque.x<0 || tanque.x>=dimx) || (tanque.y<0 || tanque.y >= dimy) || (tanque.res <=0)){
        printf("-1");
        exit(0);
    }
    
    /*
    5 - funcao que avalia se |x - bomba.x| <= bomba.raio e |y - bomba.y| <= bomba.raio
    6 - desconta 1 de tanque.res
    7 - libera memoria
    
    */
    
    checa = ChecaSeTemBomba(n, tanque, bomba);

    if(checa == 1){
        printf("Boom");
    }
    else{
        printf("Ufa");
    }
    
    LiberaBomba(&bomba);
    
    return 0;
}





