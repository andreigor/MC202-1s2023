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

#define MAX_FILAS 100
#define MAX_CLIENTES 100

int *intercalaFilas(int filaA[], int filaB[], int tamanhoFilaA, int tamanhoFilaB){
    int *vetorIntercalado = (int *)calloc(tamanhoFilaA + tamanhoFilaB, sizeof(int));
    int vetorAuxiliar[tamanhoFilaA + tamanhoFilaB];

    // Preenchendo o vetor auxiliar com os elementos da filaA
    for (int i = 0; i < tamanhoFilaA; i++){
        vetorAuxiliar[i] = filaA[i];
    }

    // Preenchendo a segunda parte do vetor auxiliar com os elementos invertidos da filaB
    for (int j = tamanhoFilaA; j < tamanhoFilaA + tamanhoFilaB; j++){
        vetorAuxiliar[j] = filaB[tamanhoFilaA - (j - tamanhoFilaB + 1)];
    }

    int i = 0;
    int j = tamanhoFilaA + tamanhoFilaB - 1;

    // Intercalando os vetores
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

int **LeEntrada(){
    int n, k, **filas;

    // Lendo a quantidade de linhas (filas)
    scanf("%d", &n);

    // Alocando a quantidade de linhas adequadamente no vetor
    filas = (int **)calloc(n + 1, sizeof(int *));

    filas[0] = (int *)calloc(1, sizeof(int *));
    *(filas[0]) = n; // primeira linha possui apenas a quantidade de linhas total

    for (int i = 1; i <= n; i++){
        // Lendo a quantidade de elementos na linha
        scanf("%d", &k);

        // Alocando e preenchendo cada linha
        filas[i] = (int *)calloc(k + 1, sizeof(int));
        filas[i][0] = k; // o primeiro elemento de cada linha é a quantidade de elementos da linha
        for (int j = 1; j <= k; j++){
            scanf("%d", &filas[i][j]);
        }
    }

    return filas;
}

void DestroiVetor(int **vetor){
    if ((*vetor) != NULL){
        free(*vetor);
        *vetor = NULL;
    }
}

void DestroiMatriz(int ***matriz, int nlin){
    if ((*matriz) != NULL){
        for (int l = 0; l < nlin; l++){
            free((*matriz)[l]);
        }
        free(*matriz);
        *matriz = NULL;
    }
}

int *FilasBanco(int **filasOriginais){
    // Quantidade de filas
    int n = *(filasOriginais[0]);

    // Criando variáveis
    int *filaIntercalada, *aux; // aux é utilizada para que não percamos referência dos vetores alocados
    int tamanhoFilaA, tamanhoFilaB;
    
    filaIntercalada = NULL;
    tamanhoFilaA = 0;
    
    // Intercalando as filas
    for (int i = 1; i <= n; i++){
        tamanhoFilaB = filasOriginais[i][0]; // Tamanho da próxima linha da matriz (próxima fila)
        aux = filaIntercalada; // Guardando a referência da fila intercalada atual em aux
        
        // Intercalando a fila - obtendo novo vetor alocado na memória
        filaIntercalada = intercalaFilas(filaIntercalada, (filasOriginais[i] + 1), tamanhoFilaA, tamanhoFilaB);

        tamanhoFilaA = tamanhoFilaA + tamanhoFilaB; // Tamanho atualizado da fila intercalada
    
        // Destruindo fila intercalada antiga
        DestroiVetor(&aux);

    }
    return filaIntercalada;
}

int main(void){
    // Lendo entrada
    int **filas = LeEntrada();
    int n = *(filas[0]);

    // Intercalando a matriz
    int *filaIntercalada = FilasBanco(filas);


    // Calculando o tamanho do vetor final
    int tamanhoTotalFila = 0;
    for (int i = 1; i <= n; i++){
        tamanhoTotalFila += filas[i][0];
    }

    // Produzindo a saída
    for (int j = 0; j < tamanhoTotalFila; j++){
        if (j == 0) printf("%d", filaIntercalada[j]); // Formatando o primeiro print
        else printf(" %d", filaIntercalada[j]); // Demais prints possuem um espaço
    }

    // Liberando memória
    DestroiVetor(&filaIntercalada);
    DestroiMatriz(&filas, *(filas[0]) + 1); 

    return 0;

}
