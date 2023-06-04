#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "FilaPrioridade.h"

void Troca(Cliente **x, Cliente **y)
{ 
  Cliente *aux;

  aux = *x;  *x   = *y;  *y   = aux;

}

void TrocaIdMax(Cliente *x, Cliente *y){
    int aux_max;
    aux_max = x->idx_max;
    x->idx_max = y->idx_max;
    y->idx_max = aux_max;
}

void TrocaIdMin(Cliente *x, Cliente *y){
    int aux_min;
    aux_min = x->idx_min;
    x->idx_min = y->idx_min;
    y->idx_min = aux_min;
}

Cliente *CriaCliente(char *sobrenome, int prioridade, int posicao){
    Cliente *cliente    = (Cliente *)calloc(1, sizeof(Cliente));
    cliente->prioridade = prioridade;
    cliente->idx_max    = posicao;
    cliente->idx_min    = posicao;
    strcpy(cliente->sobrenome, sobrenome);

    return cliente;
}
MaxHeap *CriaMaxHeap(int tam_max){
    MaxHeap *max_heap = (MaxHeap *)calloc(1, sizeof(MaxHeap));
    max_heap->tam_max = tam_max;
    max_heap->nelems  = 0;
    max_heap->elems   = (Cliente **)calloc(max_heap->tam_max, sizeof(Cliente *));
    return max_heap;
}
MinHeap *CriaMinHeap(int tam_max){
    MinHeap *min_heap = (MinHeap *)calloc(1, sizeof(MinHeap));
    min_heap->tam_max = tam_max;
    min_heap->nelems  = 0;
    min_heap->elems   = (Cliente **)calloc(min_heap->tam_max, sizeof(Cliente *));
    return min_heap;
}

FilaPrioridade *CriaFilaPrioridade(int tam_max){
    FilaPrioridade *fila_prioridade = (FilaPrioridade *)calloc(1, sizeof(FilaPrioridade));
    fila_prioridade->max_heap = CriaMaxHeap(tam_max);
    fila_prioridade->min_heap = CriaMinHeap(tam_max);
    return fila_prioridade;
}


bool HeapCheio(Heap *H){
    if (H->nelems == H->tam_max) return true;
    return false;
}
bool HeapVazio(Heap *H){
    if (H->nelems == 0) return true;
    return false;
}

bool FilaCheia(FilaPrioridade *F){
    return HeapCheio(F->max_heap);
}

bool FilaVazia(FilaPrioridade *F){
    return HeapVazio(F->min_heap);
}

void SobeMaxHeap(MaxHeap *H, int i){
    int pai = Pai(i);

    while ((pai >= 0) && H->elems[pai]->prioridade < H->elems[i]->prioridade){
        TrocaIdMax(H->elems[i], H->elems[pai]);
        Troca(&H->elems[i],&H->elems[pai]);
        i = pai;
        pai = Pai(i);
    }
}
void SobeMinHeap(MinHeap *H, int i){
    int pai = Pai(i);

    while ((pai >= 0) && H->elems[pai]->prioridade > H->elems[i]->prioridade){
        TrocaIdMin(H->elems[i], H->elems[pai]);
        Troca(&H->elems[i],&H->elems[pai]);
        i = pai;
        pai = Pai(i);
    }
}

void DesceMaxHeap(MaxHeap *H, int i){
    int maior, esq, dir;
    esq = FilhoEsquerdo(i);
    dir = FilhoDireito(i);

    if ((esq < H->nelems) && (H->elems[esq]->prioridade > H->elems[i]->prioridade))
        maior = esq;
    else
        maior = i;
    
    if ((dir < H->nelems) && (H->elems[dir]->prioridade > H->elems[maior]->prioridade))
        maior = dir;
    
    if (maior != i){
        TrocaIdMax(H->elems[i], H->elems[maior]);
        Troca(&H->elems[i],&H->elems[maior]);
        DesceMaxHeap(H, maior);
    }
}   

void DesceMinHeap(MinHeap *H, int i){
    int menor, esq, dir;
    esq = FilhoEsquerdo(i);
    dir = FilhoDireito(i);

    if ((esq < H->nelems) && (H->elems[esq]->prioridade < H->elems[i]->prioridade))
        menor = esq;
    else
        menor = i;
    
    if ((dir < H->nelems) && (H->elems[dir]->prioridade < H->elems[menor]->prioridade))
        menor = dir;
    
    if (menor != i){
        TrocaIdMin(H->elems[i], H->elems[menor]);
        Troca(&H->elems[i],&H->elems[menor]);
        DesceMinHeap(H, menor);
    }
}

Cliente *RemoveMaxHeap(MaxHeap *H,int i, int *id_min){
    Cliente *aux;
    if (!HeapVazio(H)){
        aux = H->elems[i];
        *id_min = H->elems[i]->idx_min;
        TrocaIdMax(H->elems[i], H->elems[H->nelems - 1]);
        Troca(&H->elems[i],&H->elems[H->nelems - 1]);
        H->nelems--;
        DesceMaxHeap(H, i);
    }
    return aux;

}

Cliente *RemoveMinHeap(MinHeap *H, int i, int *id_max){
    Cliente *aux;
    if (!HeapVazio(H)){
        aux = H->elems[i];
        *id_max = H->elems[i]->idx_max;
        TrocaIdMin(H->elems[i], H->elems[H->nelems - 1]);
        Troca(&H->elems[i],&H->elems[H->nelems - 1]);
        H->nelems--;
        DesceMinHeap(H, i);
    }
    return aux;
}


void InsereMaxHeap(MaxHeap *H, Cliente *cliente){
    if (!HeapCheio(H)){
        H->nelems++;
        H->elems[H->nelems - 1] = cliente;
        SobeMaxHeap(H, H->nelems - 1);
    }


}


void InsereMinHeap(MinHeap *H, Cliente *cliente){
    if (!HeapCheio(H)){
        H->nelems++;
        H->elems[H->nelems - 1] = cliente;
        SobeMinHeap(H, H->nelems - 1);
    }


}

void InsereFilaPrioridade(FilaPrioridade *F, char sobrenome[], int prioridade){
    if (!FilaCheia(F)){
        Cliente *cliente = CriaCliente(sobrenome, prioridade, F->max_heap->nelems);
        InsereMaxHeap(F->max_heap, cliente);
        InsereMinHeap(F->min_heap, cliente);
    }
}

void ImprimePrimeiroFila(FilaPrioridade *F){
    printf("%s %d", F->max_heap->elems[0]->sobrenome, F->max_heap->elems[0]->prioridade);
}

void ImprimeUltimoFila(FilaPrioridade *F){
    printf("%s %d", F->min_heap->elems[0]->sobrenome, F->min_heap->elems[0]->prioridade);
}


void ImprimeFilaPrioridade(FilaPrioridade *F){
    if (!FilaVazia(F)){
        printf("[");
        ImprimePrimeiroFila(F);
        printf(" ... ");
        ImprimeUltimoFila(F);
        printf("]\n");
    }
    else{
        printf("[ ]\n");
    }
}


Cliente *RemoveMaiorFilaPrioridade(FilaPrioridade *F){
    Cliente *aux = NULL;
    if (!FilaVazia(F)){
        int id_min, id_max;
        aux = RemoveMaxHeap(F->max_heap, 0, &id_min);
        RemoveMinHeap(F->min_heap, id_min, &id_max);
    }
    return aux;

}

Cliente *RemoveMenorFilaPrioridade(FilaPrioridade *F){
    Cliente *aux = NULL;
    if (!FilaVazia(F)){
        int id_min, id_max;
        aux = RemoveMinHeap(F->min_heap, 0, &id_max);
        RemoveMaxHeap(F->max_heap, id_max, &id_min);
    }
    return aux;
}

void MudaPrioridade(FilaPrioridade *F, char sobrenome[], int prioridade){
    int id_min;
    for (int i = 0; i < F->max_heap->nelems; i++){
        if (!strcmp(sobrenome, F->max_heap->elems[i]->sobrenome)){
            id_min = F->max_heap->elems[i]->idx_min;
            if (prioridade > F->max_heap->elems[i]->prioridade){
                F->max_heap->elems[i]->prioridade = prioridade;
                SobeMaxHeap(F->max_heap, i);
                DesceMinHeap(F->min_heap, id_min);
            }
            else{
                F->max_heap->elems[i]->prioridade = prioridade;
                DesceMaxHeap(F->max_heap, i);
                SobeMinHeap(F->min_heap, id_min);
            }
        break;
        }
    }
}

void DestroiFilaPrioridade(FilaPrioridade **F){
    if (*F != NULL){
        for (int i = 0; i < (*F)->max_heap->nelems; i++){
            free((*F)->max_heap->elems[i]);
        }
        free((*F)->max_heap->elems);
        free((*F)->min_heap->elems);
        free((*F)->max_heap);
        free((*F)->min_heap);
        free((*F));
        (*F) = NULL;
    }
}
