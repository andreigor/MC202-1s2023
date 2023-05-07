#include <stdlib.h>
#include <stdio.h>

typedef struct _bomb{
  int x, y, raio;

} bomb;

bomb *CriaBomba(int n){
    bomb *bomba = (bomb *)calloc(n,sizeof(bomb));

    return bomba;
}

int ChecaSeTemBomba(int n, int x, int y, bomb *bomba){
    
    int i;
    
    for(i=0;i<n;i++){
        if((-bomba[i].raio <= (x - bomba[i].x)) && ((x - bomba[i].x) <= bomba[i].raio)){
            if((-bomba[i].raio <= (y - bomba[i].y)) && ((y - bomba[i].y) <= bomba[i].raio)){
                return 1;
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
    int i, x, y;
    bomb *bomba;
 


    /*
    1 - le tamanho do tabuleiro
    2 - le numero de bombas
    3 - le caracteristicas da bomba
    4 - le coord para verificar se eh segura ou nao
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
        if((bomba[i].x < 0 || bomba[i].x> dimx) || (bomba[i].y < 0 || bomba[i].y> dimy) || (bomba[i].raio <0)){
            printf("-1");
            exit(0);
        }
    }
    
    scanf("\n%i %i", &x,&y);
    if((x<0 || x>dimx) || (y<0 || y > dimy)){
        printf("-1");
        exit(0);
    }
    
    /*
    5 - funcao que avalia se |x - bomba.x| <= bomba.raio e |y - bomba.y| <= bomba.raio
    6 - libera memoria
    
    */
    
    checa = ChecaSeTemBomba(n,x,y,bomba);

    if(checa ==1){
        printf("Perigoso");
    }
    else{
        printf("Seguro");
    }
    
    LiberaBomba(&bomba);
    
    
  return 0;
}



