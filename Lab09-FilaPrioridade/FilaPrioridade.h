#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include <stdbool.h>
#define Pai(i) ((i-1)/2)
#define FilhoEsquerdo(i) (2*i+1)
#define FilhoDireito(i) (2*i+2)

typedef struct _cliente{
    char sobrenome[20];
    int prioridade;
    int idx_max, idx_min;
} Cliente;

typedef struct _heap{
    Cliente **elems;
    int tam_max, nelems;
} MaxHeap, MinHeap, Heap;

typedef struct _fila_prioridade{
    MaxHeap *max_heap;
    MinHeap *min_heap;
} FilaPrioridade;

void Troca(Cliente **x, Cliente **y);

Cliente *CriaCliente(char *sobrenome, int prioridade, int posicao);
MaxHeap *CriaMaxHeap(int nelems);
MinHeap *CriaMinHeap(int nelems);
FilaPrioridade *CriaFilaPrioridade(int nelems);

bool HeapCheio(Heap *H);
bool HeapVazio(Heap *H);

bool FilaCheia(FilaPrioridade *F);
bool FilaVazia(FilaPrioridade *F);

void SobeMaxHeap(MaxHeap *H, int i);
void SobeMinHeap(MinHeap *H, int i);

void DesceMaxHeap(MaxHeap *H, int i);
void DesceMinHeap(MinHeap *H, int i);

void InsereMinHeap(MaxHeap *H, Cliente *cliente);
void InsereMaxHeap(MinHeap *H, Cliente *cliente);
void InsereFilaPrioridade(FilaPrioridade *F, char sobrenome[], int prioridade);

void ImprimePrimeiroFila(FilaPrioridade *F);
void ImprimeUltimoFila(FilaPrioridade *F);
void ImprimeFilaPrioridade(FilaPrioridade *F);

Cliente *RemoveMaxHeap(MinHeap *H, int i, int *id_min);
Cliente *RemoveMinHeap(MinHeap *H, int i, int *id_max);
Cliente *RemoveMaiorFilaPrioridade(FilaPrioridade *F);
Cliente *RemoveMenorFilaPrioridade(FilaPrioridade *F);
void MudaPrioridade(FilaPrioridade *F, char sobrenome[], int prioridade);

void DestroiFilaPrioridade(FilaPrioridade **F);




#endif