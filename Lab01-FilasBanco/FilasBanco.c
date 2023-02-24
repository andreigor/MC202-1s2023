/*
Caos nas Filas do Banco
Aluno: André Igor Nóbrega da Silva
Curso: MC202 - 1s2023 - Unicamp
Turma: A

Descrição: Dada uma quantidade n de filas em um banco, cada uma com uma quantidade k_i de clientes que possuem um tempo esperado
(em minutos) para atendimento, retornamos um vetor único com uma intercalação ordenada dos clientes.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_FILAS 10
#define MAX_CLIENTES 20

int *intercalaFilas(int filaA[], int filaB[], int tamanhoFilaA, int tamanhoFilaB){
    int *vetorIntercalado = (int *)calloc(tamanhoFilaA + tamanhoFilaB, sizeof(int));
    int vetorAuxiliar[tamanhoFilaA + tamanhoFilaB];

    for (int i = 0; i < tamanhoFilaA; i++){
        vetorAuxiliar[i] = filaA[i];
    }

    for (int j = tamanhoFilaA; j < tamanhoFilaA + tamanhoFilaB; j++){
        // printf("indice j: %d\tindice k: %d\n", j, tamanhoFilaA - (j - tamanhoFilaB + 1));
        vetorAuxiliar[j] = filaB[tamanhoFilaA - (j - tamanhoFilaB + 1)];
    }

    // printf("Vetor auxiliar: \n");
    // for (int a = 0; a < tamanhoFilaA + tamanhoFilaB; a++){
    //     printf("%d ", vetorAuxiliar[a]);
    // }

    // printf("\n-----------------------\n");

    int i = 0;
    int j = tamanhoFilaA + tamanhoFilaB - 1;

    for (int k = 0; k < (tamanhoFilaA + tamanhoFilaB); k++){
        if (vetorAuxiliar[i] <= vetorAuxiliar[j]){
            vetorIntercalado[k] = vetorAuxiliar[i];
            i++;
        }
        else {
            vetorIntercalado[k] = vetorAuxiliar[j];
            j--;
        }
    }

    return vetorIntercalado;
}

int *FilasBanco(int *filasOriginais[]){

}

int main(void){
    int filaA[7] = {1, 2, 3, 7, 10, 12, 13};
    int filaB[5] = {1, 3, 3, 5, 8};

    int *intercala;

    intercala = intercalaFilas(filaA, filaB, 7, 5);

    // printf("Resposta: \n");
    // for (int i = 0; i < 12; i++){
    //     printf("%d ", intercala[i]);
    // }

    free(intercala);

    return 0;

}