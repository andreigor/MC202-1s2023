/*
Aluno: André Igor Nóbrega da Silva
Curso: MC202 - 1s2023 - Unicamp
Turma: A


Descrição: Dada um conjunto de n lesmas, cada uma com sua respectiva velocidade, retornamos a lesma que ganharia uma maratona com uma 
certa quantidade de horas. Quanto mais rápido uma lesma, menos horas ela é capaz de correr.

*/

#include <stdio.h>
#define MAX_LESMAS 100

int MaratonaLesmas(int n, int *velocidades, int horas){
    int limite;

    if (horas == 1) limite = 100;
    else if (horas == 2) limite = 20;
    else if (horas == 3) limite = 10;
    else return -1;

    // Maior velocidade das lesmas qualificadas

    int maxima = -1; // inicializando com a velocidade de erro

    for (int i = 0; i < n; i++){
        if ((velocidades[i] > 0) && (velocidades[i] > maxima) && (velocidades[i] <= limite)) maxima = velocidades[i];
    }

    return maxima;
}

int main(void){
    int n, horas;
    int velocidades[MAX_LESMAS];

    // Obtendo a quantidade de lesmas
    scanf("%d", &n);

    // Obtendo as velociadades
    for (int i = 0; i < n; i++){
        scanf("%d", &velocidades[i]);
    }

    // Obtendo a duração da maratona
    scanf("%d", &horas);

    int lesmaGanhadora = MaratonaLesmas(n, velocidades, horas);

    printf("%d", lesmaGanhadora);

    return 0;

}