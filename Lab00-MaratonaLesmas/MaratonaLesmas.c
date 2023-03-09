#include <stdio.h>

int main(){
    /* entradas */
    /* numero de lesmas:*/
    int n;
    scanf("%d",&n);

    /* velocidade das lesmas */
    int velocidade[100];
    int i = 0;
    for(i; i < n; i++){
    	// printf("i: %d\n", i);
        scanf("%d",&velocidade[i]);
    }

    /* duracao da maratona */
    int tempo;
    scanf("%d",&tempo);
    
    int limite= -1;
    
    if (tempo == 3){
        limite = 10;
    }
    else if (tempo == 2){
        limite = 20;
    }
    else if (tempo == 1){
        limite == 100;
    }
    
    int ganhadora = -1;
    

    
    for(i; i < n; i++){
    	
        if (velocidade[i] <= limite){
            if (velocidade[i] > ganhadora){
                ganhadora = velocidade[i];
            }
        }
    }
    
    printf("%d", ganhadora);
    return 0;
}

