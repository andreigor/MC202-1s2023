#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

void AddOperation(Pilha *Q){
    int x, y, z;
    Desempilha(Q, &y);
    Desempilha(Q, &x);
    z = x + y;
    Empilha(Q, x);
    Empilha(Q, y);
    Empilha(Q, z);
}

void DoubleOperation(Pilha *Q){
    int x, z;
    Desempilha(Q, &x);
    z = 2 * x;
    Empilha(Q, x);
    Empilha(Q, z);
}

void InvertOperation(Pilha *Q){
    int x;
    Desempilha(Q, &x);
    Empilha(Q, -1 * x);
}

void RemoveOperation(Pilha *Q){
    int x;
    Desempilha(Q, &x);
}

int sumPilha(Pilha *Q){
    int sum = 0;
    int x;
    int n = Q->qtde;
    for (int i = 0; i < n; i++){
        Desempilha(Q, &x);
        sum += x;
    }

    return sum;
}


int main(int argc, char **argv){
    FILE *fp = fopen(argv[1], "r");
    int n;
    char c;

    fscanf(fp, "%d\n", &n);

    Pilha *Q = CriaPilha(n);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%c\n", &c);
        if (c == '+'){
            AddOperation(Q);
        }
        else if (c == 'D'){
            DoubleOperation(Q);
        }
        else if (c == 'I'){
            InvertOperation(Q);
        }
        else if (c == 'C'){
            RemoveOperation(Q);
        }
        else{
            Empilha(Q, (int)(c - '0'));
        }

    }
    fclose(fp);

    int sum = sumPilha(Q);

    printf("%d", sum);


    return 0;
}
