#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Busca a saída de um labirinto a partir de uma posição inicial,
   andando com vizinhança-4. As posições são de três tipos: 'P' -
   válida, 'X' - inválida, 'T' - teletransporte (válido) e 'S' - saída. */

typedef struct _ponto
{
  int x, y;
} Ponto;

typedef struct _labirinto
{
  char **Posicao;
  int nx, ny, ngates;
  Ponto entrada, saida;
  Ponto *gates;
} Labirinto;

Labirinto *LeLabirinto(char *nomearq)
{
  FILE *fp = fopen(nomearq, "r");
  Labirinto *L = (Labirinto *)calloc(1, sizeof(Labirinto));

  fscanf(fp, "%d %d %d\n", &L->nx, &L->ny, &L->ngates);
  L->Posicao = (char **)calloc(L->ny, sizeof(char *));
  for (int y = 0; y < L->ny; y++)
    L->Posicao[y] = (char *)calloc(L->nx, sizeof(char));
  
  L->gates = (Ponto *)calloc(L->ngates, sizeof(Ponto));

  int gates_counter = 0;

  for (int y = 0; y < L->ny; y++)
  {
    for (int x = 0; x < L->nx; x++)
    {
      fscanf(fp, "%c", &L->Posicao[y][x]);
      if (L->Posicao[y][x] == 'E')
      {
        L->entrada.x = x;
        L->entrada.y = y;
        L->Posicao[y][x] = 'P';
      }
      else if (L->Posicao[y][x] == 'S')
      {
        L->saida.x = x;
        L->saida.y = y;
        L->Posicao[y][x] = 'P';
      }
      else{
        if (L->Posicao[y][x] == 'G'){
          L->gates[gates_counter].x = x;
          L->gates[gates_counter].y = y;
          L->Posicao[y][x] = 'P';
          gates_counter++;
        }
      }
    }
    fscanf(fp, "\n");
  }

  fclose(fp);
  return (L);
}

void DestroiLabirinto(Labirinto **L)
{
  if ((*L) != NULL)
  {
    free((*L)->gates);
    for (int y = 0; y < (*L)->ny; y++)
      free((*L)->Posicao[y]);
    free((*L)->Posicao);
    free((*L));
    (*L) = NULL;
  }
}

typedef struct _adj{
  int n;
  Ponto *adj;
} Adjacencia;

bool isGate(Labirinto *L, Ponto p){
    for (int i = 0; i < L->ngates; i++){
        if ((p.x == L->gates[i].x) && (p.y == L->gates[i].y)){
            return true;
        }
    }
    return false;
}

Adjacencia criaAdjacencia(Labirinto *L, Ponto p){
  /*Cria uma relação de adjacência a partir de um determinado ponto do labirinto
  Esse ponto pode ou não ser um ponto de teletransporte. Caso seja, inclui todos 
  os portais na relação de adjacência. Caso não seja, vira uma adjacência 4.
  */
  Adjacencia A;
  int ngates = 0;
  if (isGate(L, p)){
      ngates = L->ngates;
  } 
  int n = 4 + ngates;
  A.n   = n;

  A.adj = (Ponto *)calloc(n, sizeof(Ponto));
  A.adj[0].x = -1;
  A.adj[0].y = 0;
  A.adj[1].x = 1;
  A.adj[1].y = 0;
  A.adj[2].x = 0;
  A.adj[2].y = -1;
  A.adj[3].x = 0;
  A.adj[3].y = 1;

  for (int i = 0; i < ngates; i++){
    A.adj[i + 4].x = L->gates[i].x - p.x;
    A.adj[i + 4].y = L->gates[i].y - p.y;
  }

  return A;
}

bool pontoValido(Labirinto *L, Ponto P)
{

  if ((P.x >= 0) && (P.x < L->nx) && (P.y >= 0) && (P.y < L->ny) && (L->Posicao[P.y][P.x] != 'X'))
    return true;
  return false;
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
  /* Encontrou uma solução verdadeira */
  if ((P.x == L->saida.x) && (P.y == L->saida.y)){
    res = true;
  }
  Adjacencia A = criaAdjacencia(L, P);

  for (int i = 0; i < A.n && (res != true); i++)
  {
    Ponto passo;
    passo.x = P.x + A.adj[i].x;
    passo.y = P.y + A.adj[i].y;

    if (pontoValido(L, passo))
    {
      char valor_anterior = L->Posicao[passo.y][passo.x];
      L->Posicao[passo.y][passo.x] = 'X';
      // if   (Backtrack(L, passo)){
      //   return true;
      // }
      res = Backtrack(L,passo);
      // L->Posicao[passo.y][passo.x] = valor_anterior;
    }
  }
  free(A.adj);
  return res;
  // return (false);
}

void printaAdjacencia(Adjacencia A){
    for (int i = 0; i < A.n; i++){
        printf("%d %d\n", A.adj[i].x, A.adj[i].y);
    }
}

int main(int argc, char **argv)
{
  Labirinto *L = NULL;

  if (argc != 2)
  {
    printf("usage: <P1>\n");
    printf("P1: arquivo texto do labirinto\n");
    exit(0);
  }

  L = LeLabirinto(argv[1]);
  if (Backtrack(L, L->entrada))
    printf("Encontrou a saida em (%d,%d)\n", L->saida.x, L->saida.y);
  else
    printf("Labirinto sem saida\n");

  DestroiLabirinto(&L);
  return (0);
}
