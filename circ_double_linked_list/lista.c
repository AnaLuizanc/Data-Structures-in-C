#include<stdio.h>
#include<stdlib.h>
#include "lista.h"

/* Inicializa a lista como lista vazia. */
void inicializa_lista(Lista * ap_lista){
   Lista cabeca = (Lista)malloc(sizeof(No));
   cabeca->valor.grau = -1;
   cabeca->valor.coef = -1;
   cabeca->prox = cabeca;
   cabeca->antec = cabeca;
   (*ap_lista) = cabeca;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o no cabeca da lista. */
void insere_fim(Lista cabeca, TipoDado valor){
   Lista novo = (Lista)malloc(sizeof(No));
   novo->valor = valor;
   Lista ultimo = cabeca->antec;
   ultimo->prox = novo;
   novo->antec = ultimo;
   novo->prox = cabeca;
   cabeca->antec = novo;
}

/* Insere valor no inicio da lista apontada por ap_lista. ap_lista aponta para o no cabeca da lista. */
void insere_inicio(Lista cabeca, TipoDado valor){
   Lista novo = (Lista)malloc(sizeof(No));
   novo->valor = valor;
   novo->prox = cabeca->prox;
   cabeca->prox->antec = novo;
   novo->antec = cabeca;
   cabeca->prox = novo;
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_fim(Lista cabeca){
   Lista remove = cabeca->antec;
   TipoDado valor_removido = remove->valor;
   Lista antecessor = remove->antec;
   antecessor->prox = cabeca;
   cabeca->antec = antecessor;
   free(remove);
   return valor_removido;
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
TipoDado remove_inicio(Lista cabeca){
   Lista remove = cabeca->prox;
   TipoDado valor_removido = remove->valor;
   cabeca->prox = remove->prox;
   remove->prox->antec = cabeca;
   free(remove);
   return valor_removido;
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrencias removidas. */
int remove_ocorrencias(Lista cabeca, TipoDado valor){
    int contador=0;
    Lista atual = cabeca->prox;
    while(atual != cabeca){
        if(atual->valor.coef == valor.coef && atual->valor.grau == valor.grau){
            Lista remove = atual;
            Lista antecessor = atual->antec;
            antecessor->prox = remove->prox;
            remove->prox->antec = antecessor;
            atual = atual->prox;
            free(remove);
            contador++;
        }else
            atual = atual->prox;
    }
    return contador;
}

/* Busca elemento valor na lista. 
   Retorna a posição da primeira ocorrencia de valor na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado. */
int busca(Lista cabeca, TipoDado valor){
    Lista atual = cabeca->prox;
    int posicao=0;
    while(atual != cabeca){
        if(atual->valor.coef == valor.coef && atual->valor.grau == valor.grau)
            return posicao;
        else{
            posicao++;
            atual = atual->prox;
        }
    }
    return -1;
}

/* Retorna o campo coef do primeiro no que contenha grau igual ao parametro grau, 
   e 0 (zero) caso nao encontre um tal no.  */
int coeficiente_do_grau(Lista cabeca, int grau){
    Lista atual = cabeca->prox;
    while(atual != cabeca){
        if(atual->valor.grau == grau)
            return atual->valor.coef;
        else
            atual = atual->prox;
    }
    return 0;
}

/* Imprime a lista na saida padrao, no formato:
   [(1,3),(2,3),(4,2),(3,1),(4,17)]
   em uma linha separada. */
void imprime(Lista lista){
    printf("[");
    Lista atual = lista->prox;
    while(atual != lista){
        printf("(%d,%d)", atual->valor.grau, atual->valor.coef);
        if(atual->prox != lista)
            printf(",");
        atual = atual->prox;
    }
    printf("]\n");
}

/* Desaloca toda a memória alocada da lista.*/
void desaloca_lista(Lista *ap_lista){
    Lista atual = (*ap_lista)->prox;
    while(atual != (*ap_lista)){
        Lista remove = atual;
        remove->antec->prox = remove->prox;
        remove->prox->antec = remove->antec;
        atual = atual->prox;
        free(remove);
    }
    free(*ap_lista);
}