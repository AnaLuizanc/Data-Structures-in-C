#include<stdio.h>
#define MAX 15

void le_subconjuntos(int qtd, int vetorW[]){
    int mask=0;
    int qtd_elem=0;
    int elemento;
    for(int i=0; i<qtd; i++){
        scanf("%d", &qtd_elem);
        for(int j=0; j<qtd_elem; j++){
            scanf("%d", &elemento);
            mask = mask | (1<<elemento);
        }
        vetorW[i] = mask;
        mask = 0;
    }
}

int interseccao(int a, int b){
    if((a & b) == 0)
        return 0;
    else
        return -1;
}

int faz_cobertura(int vetorW[], int objetivo, int qtd_sub, int conjuntoR[]){
    int resultado, contador = 0;
    for(int i=0; i<(1<<qtd_sub); i++){
        resultado = 0;
        for(int j=0; j<qtd_sub; j++){
            if((interseccao(i, (1<<j)) == 0) && (interseccao(resultado, vetorW[j]) == 0)){
                resultado = resultado | vetorW[j];
                conjuntoR[contador] = vetorW[j];
                contador++;
            }
        }
        if(resultado == objetivo)
            return contador;
        contador = 0;
    }
    return 0;
}

void imprime_solucao(int qtd_sub, int conjunto[]){
    int contador = 0; 
    printf("%d\n", qtd_sub);
    for(int i = 0; i < qtd_sub; i++){
        for(int k = 0; k < MAX; k++){
            if(interseccao(conjunto[i], (1 << k)))
                contador++; 
        }
        printf("%d ", contador);
        for(int j = 0; j < MAX; j++){
            if(interseccao(conjunto[i], (1 << j)))
                printf("%d ", j);
        }
        printf("\n");
        contador = 0;
    }
}

int main(){
    int qtd_subconj, intervalo;
    int conjuntoR[MAX];
    scanf("%d %d", &intervalo, &qtd_subconj);
    int objetivo = 0;
    int vetorW[qtd_subconj];
    for(int i=0; i<intervalo; i++)
        objetivo = objetivo | (1<<i);
    le_subconjuntos(qtd_subconj, vetorW);
    int res = faz_cobertura(vetorW, objetivo, qtd_subconj, conjuntoR);
    if(res > 0)
        imprime_solucao(res, conjuntoR);
    else
        printf("Insoluvel\n");
    return 0;
}