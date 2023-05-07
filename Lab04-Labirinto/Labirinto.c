#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct _ponto {
  int x, y;
} Ponto;

typedef struct _labirinto {
  char **Posicao;
  int nx, ny;
  int n;
  int **Matriz;
  Ponto entrada, saida, portal;
} Labirinto;


Labirinto *LeLabirinto(char *nomearq)
{
  FILE *fp = fopen(nomearq,"r");
  Labirinto *L = (Labirinto *)calloc(1,sizeof(Labirinto));
  
  fscanf(fp,"%d %d %d\n",&L->nx,&L->ny,&L->n);
  
  L->Matriz = (int **)calloc(L->n,sizeof(int *));
  for (int y=0; y < L->n; y++) {
    L->Matriz[y] = (int *)calloc(2,sizeof(int ));
  }
  
  L->Posicao = (char **)calloc(L->ny,sizeof(char *));
  for (int y=0; y < L->ny; y++) {
    L->Posicao[y] = (char *)calloc(L->nx,sizeof(char ));
  }
  int s=0;
  for (int y=0; y < L->ny; y++){ 
    for (int x=0; x < L->nx; x++) {
      fscanf(fp,"%c",&L->Posicao[y][x]);
      if (L->Posicao[y][x]=='E'){
		    L->entrada.x= x; L->entrada.y= y;
		    L->Posicao[y][x]='P';
      } 
      if (L->Posicao[y][x]=='S'){
            L->saida.x= x; L->saida.y= y;
            L->Posicao[y][x]='P';
      }
      if (L->Posicao[y][x]=='G'){
          L->Posicao[y][x]='P';
          L->Matriz[s][0]=x;
          L->Matriz[s][1]=y;
          s +=1;
       }
    fscanf(fp,"\n");
    }
  }

  fclose(fp);
  return(L);
}

void DestroiLabirinto(Labirinto **L) {
  if ((*L)!=NULL){
    for (int y=0; y < (*L)->ny; y++)
      free((*L)->Posicao[y]); 
    free((*L)->Posicao);
    free((*L));
    (*L) = NULL;
  }
}

void printLabirinto(Labirinto *L){
  for (int y = 0; y < L->ny; y++)
  {
    for (int x = 0; x < L->nx; x++)
    {
      printf("%c", L->Posicao[y][x]);
    }
    printf("\n");
  }

  printf("#######################\n");
}

bool Backtrack(Labirinto *L, Ponto P)
{
  bool res = false;
  if ((P.y == L->saida.y)&&(P.x == L->saida.x)) { 
    res = true;
  } else {
    Ponto *C = (Ponto *)calloc(4+L->n,sizeof(Ponto));
    C[0].x = P.x - 1; C[0].y = P.y;
    C[1].x = P.x + 1; C[1].y = P.y;
    C[2].x = P.x;     C[2].y = P.y - 1;
    C[3].x = P.x;     C[3].y = P.y + 1;
    int r=4;
    for (int k=0;k<L->n;k++){
	    if( (P.y == L->Matriz[k][1])&&(P.x == L->Matriz[k][0])){
	      for (int i=4; i< (L->n + 4); i++){
	        C[i].x = L->Matriz[i-4][0]; C[i].y = L->Matriz[i-4][1];
	      }
	    r= 4+ L->n;
	    }
    }
    for (int i=0; (i < r) && (res != true); i++) {
      if ((C[i].x >= 0)&&(C[i].x < L->nx)&& 
	      (C[i].y >= 0)&&(C[i].y < L->ny)){
	        if (L->Posicao[C[i].y][C[i].x] != 'X'){ 
            char valor_correto = L->Posicao[C[i].y][C[i].x];
            L->Posicao[C[i].y][C[i].x] = 'X'; 	    
            res = Backtrack(L,C[i]);
            L->Posicao[C[i].y][C[i].x] = valor_correto; 
	        }
      }
    }
  free(C);
}
  return(res);
}

int main(int argc, char **argv)
{

  Labirinto *L = NULL;

  L = LeLabirinto(argv[1]);

  // printLabirinto(L);


  if (Backtrack(L,L->entrada)){
    printf("Encontrou a saida em (%d,%d)\n",L->saida.x,L->saida.y);
 }
  else{
    printf("Labirinto sem saida\n");
 }
  DestroiLabirinto(&L);

  return(0);
}

