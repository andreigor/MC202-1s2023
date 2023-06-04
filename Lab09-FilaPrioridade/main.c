#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
#include "FilaPrioridade.h"

int main(int argc, char *argv[]){

    FilaPrioridade *F = CriaFilaPrioridade(MAX_SIZE);
    FILE *fp = fopen(argv[1], "r");
    int n, prioridade;
    char op, sobrenome[20];

    fscanf(fp, "%d\n", &n);

    for (int i = 0; i < n; i++){
        fscanf(fp, "%c ", &op);
        
        if (op == 'I'){
            fscanf(fp, "%s %d\n", sobrenome, &prioridade);
            InsereFilaPrioridade(F, sobrenome, prioridade);
        }
        else if (op == 'P'){
            ImprimeFilaPrioridade(F);
        }
        else if (op == 'L'){
            Cliente *aux = RemoveMaiorFilaPrioridade(F);
            if (aux != NULL){
                printf("Mesa liberada para Sr(a) %s.\n", aux->sobrenome);
                free(aux);
            }
        }
        else if (op == 'D'){
            Cliente *aux = RemoveMenorFilaPrioridade(F);
            if (aux != NULL){
                printf("Sr(a) %s desistiu de esperar e foi embora.\n", aux->sobrenome);
                free(aux);
            }
        }
        else if (op == 'M'){
            fscanf(fp, "%s %d\n", sobrenome, &prioridade);
            MudaPrioridade(F, sobrenome, prioridade);
        }
    }
    DestroiFilaPrioridade(&F);
    fclose(fp);

    return 0;
}