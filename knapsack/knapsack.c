#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int peso;
    int valor;
}Item;

int maximo(int a, int b){
    return (a>b) ? a : b;
}

int mochila(Item* conjuntoS, int quantidade, int pesoMax, int*** indices){
    int** resultAux = (int**)malloc((quantidade+1)*sizeof(int*));
    for(int i=0; i<=quantidade; i++)
        resultAux[i] = (int*)malloc((pesoMax+1)*sizeof(int));

    for(int i=0; i<=quantidade; i++){
        for(int j=0; j<=pesoMax; j++){
            if(i==0 || j==0)
                resultAux[i][j] = 0;
            else{
                int peso = conjuntoS[i-1].peso;
                int valor = conjuntoS[i-1].valor;
                if(peso>j)
                    resultAux[i][j] = resultAux[i-1][j];
                else
                    resultAux[i][j] = maximo(resultAux[i-1][j], resultAux[i-1][j-peso]+valor);
            }
        }
    }
    int valorMax = resultAux[quantidade][pesoMax];

    *indices = (int**)malloc((quantidade+1)*sizeof(int*));
    for(int i=0; i<=quantidade; i++){
        (*indices)[i] = (int*)malloc((pesoMax+1)*sizeof(int));
        for(int j=0; j<=pesoMax; j++)
            (*indices)[i][j] = -1;
    }

    int i=quantidade, j=pesoMax;
    while(i>0 && j>0){
        if(resultAux[i][j] != resultAux[i-1][j]){
            (*indices)[i][j] = i-1;
            j = j-conjuntoS[i-1].peso;
        }
        i--;
    }

    for(int i=0; i<=quantidade; i++)
        free(resultAux[i]);
    free(resultAux);

    return valorMax;
}

void imprimeIndices(Item* conjuntoS, int** indicesSubconj, int quantidade, int pesoMax){
    int i=quantidade, j=pesoMax;
    int somaPesos=0, somaValores=0;
    while(i>0 && j>0){
        int index = indicesSubconj[i][j];
        if(index != -1){
            somaPesos += conjuntoS[index].peso;
            somaValores += conjuntoS[index].valor;            
            j = j-conjuntoS[i-1].peso;
        }
        i--;
    }
    printf("%d %d\n", somaPesos, somaValores);

    int *indices = (int*)malloc(quantidade*sizeof(int));
    int k=0;
    i=quantidade;
    j=pesoMax;
    while(i>0 && j>0){
        int index = indicesSubconj[i][j];
        if(index != -1){
            indices[k++] = index;
            j -= conjuntoS[index].peso;
        }
        i--;
    }

    printf("%d", k);
    for(int i=k-1; i>=0; i--)
        printf(" %d", indices[i]);
    printf("\n");
    free(indices);
}

int main() {
    int quantidade, pesoMax;
    scanf("%d %d", &quantidade, &pesoMax);

    Item *conjuntoS = (Item*)malloc(quantidade*sizeof(Item));
    for (int i=0; i<quantidade; i++)
        scanf("%d %d", &conjuntoS[i].peso, &conjuntoS[i].valor);

    int **indicesSubconjuntos;
    int resultado = mochila(conjuntoS, quantidade, pesoMax, &indicesSubconjuntos);

    imprimeIndices(conjuntoS, indicesSubconjuntos, quantidade, pesoMax);

    for (int i=0; i<=quantidade; i++)
        free(indicesSubconjuntos[i]);
    free(indicesSubconjuntos);
    free(conjuntoS);

    return 0;
}