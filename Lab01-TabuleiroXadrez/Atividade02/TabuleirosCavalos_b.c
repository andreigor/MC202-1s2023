#include <stdio.h>
#include <malloc.h>

int* criaVetorInteiro(int nlin) {
	
	int* v = (int*) calloc(nlin, sizeof(int));
	return v;
	
}

void destroiVetorInteiro(int** v) {

	if ( (*v) != NULL) {
		
		free(*v);
		*v = NULL;
	}
}

int** criaMatrizInteira(int nlin, int ncol) {
	
	int** m = (int**) calloc(nlin, sizeof(int*));
	for (int i = 0; i < nlin; i++) 
		m[i] = (int*) calloc(ncol, sizeof(int));
	return m;
	
}

void destroiMatrizInteira(int*** m, int nlin) {
	
	if ((*m) != NULL) {
		
		for (int i = 0; i < nlin; i++) 
			free((*m)[i]);
	}
	free(*m);
	*m = NULL;
}

int** criaListaPosicoes(int n) {

	int** lista = (int**) calloc(n, sizeof(int*));
	return lista;

}

int emConflito(int *posicao, int **tabuleiro) {

    int linha, coluna;

	/* Percorrendo o sentido em que o cavalo irá andar... */
    for (int s = 1; s > - 2; s = s - 2)
		
		/* Percorrendo o sentido em que o cavalo irá andar naquela direção... */
        for (int d = 0; d < 2; d++)
			
			/* Percorrendo as duas possibilidades para fechar o L... */
            for (int t = -1; t < 2; t = t + 2) {

                linha = posicao[0] + 2 * (1 - d) * s  - d * s * t;
                coluna = posicao[1] + 2 * d * s  + (1 - d) * s * t;

				/* Verificando se o movimento é válido... */
                if ( ( (0 <= linha) && (linha < 8) ) && ( (0 <= coluna) && (coluna < 8) ) ) {

					/* Verificando se há outro cavalo na posição... */
					if (tabuleiro[linha][coluna] == 1)
						return 1;
					
                }
            }
			
	return 0;
}

void estaEmPaz(int n, int** posicoes, int** tabuleiro) {

	/* Caso haja, apenas, um cavalo, o reino está em paz */
	if (n < 2) {
		printf("Paz no reino!");
		return;
	}
	
	for (int i = 0; i < n; i++) {
	
		/* Só faz sentido testar se há cavalos em conflito se há, pelo menos,
		um cavalo na tabuleiro... */
		if (i > 1) {
		
			/* Testando se o cavalo está em conflito com outro que já está no
			tabuleiro... */
			if (emConflito(posicoes[i], tabuleiro) == 1) {
				printf("Os cavalos estao em guerra!");
				return;
			}
		}
		
	/* Colocando o i-ésimo cavalo no tabuleiro */
	tabuleiro[posicoes[i][0]][posicoes[i][1]] = 1;
	}
	
	printf("Paz no reino!");
	
	return;
}


int* converteEntrada(char vertical, int horizontal) {

	int* posicao = criaVetorInteiro(2);
	
	/* Como à primeira linha de um tabuleiro é atribuída o número 1, basta deduzir 1 */
	posicao[0] = horizontal - 1;
	
	/* Para converter a letra que corresponde à coluna, pode-se atribuir a uma variável 
	inteira a diferença entre seu código ASCII e o código da letra A */
	posicao[1] = vertical - 'A';
	
	return posicao;
	

}

int main() {

  /* Lendo o número de cavalos... */
  int n;
  scanf("%d", &n);

  /* Criando uma lista para armazenar n posições... */
  int** posicoes = criaMatrizInteira(n, 2);
  
  for (int i = 0; i < n; i++) {
	  
	char vertical; int horizontal;
	
	/* Lendo a entrada do usuário... */ 
	scanf("\n%c %d", &vertical, &horizontal);
	
	posicoes[i] = converteEntrada(vertical, horizontal);
  }
  
  /* Criando o tabuleiro... */
  int** tabuleiro = criaMatrizInteira(8, 8);
  
  /* Imprimindo o estado do reino... */
  estaEmPaz(n, posicoes, tabuleiro);

  /* Destruindo o tabuleiro */
  destroiMatrizInteira(&tabuleiro, 8);
  
  /* Destruindo a lista de posições */
  destroiMatrizInteira(&posicoes, n);
  
  return 0;

}
