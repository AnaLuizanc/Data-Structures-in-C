#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

No* novo_no(int x){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = x;
    novo->dir = NULL;
    novo->esq = NULL;
    return novo;
}

/** Insere valor x na árvore de busca binária */
bool insere(Arvore* ap_arv, int x){
    if(*ap_arv == NULL){
        No* novo = novo_no(x);
        (*ap_arv) = novo;
        return true;
    }
    if(busca(*ap_arv, x) == true)
        return false;
    if(x > (*ap_arv)->valor){
        insere(&((*ap_arv)->dir), x);
        return true;
    }else if(x < (*ap_arv)->valor){
        insere(&((*ap_arv)->esq), x);
        return true;
    }
    return false;
}

No* antecessor(No* no){
    No* atual = no->esq;
    while(atual->dir != NULL)
        atual = atual->dir;
    return atual;
}

No* remove_no(No* no, int x){
    if(no == NULL)return NULL;
    if(x < no->valor)
        no->esq = remove_no(no->esq, x);
    else if(x > no->valor)
        no->dir = remove_no(no->dir, x);
    else{
        if(no->esq == NULL){
            No* aux = no->dir;
            free(no);
            return aux;
        }else if(no->dir == NULL){
            No* aux = no->esq;
            free(no);
            return aux;
        }
        No* no_antec = antecessor(no);
        no->valor = no_antec->valor;
        no->esq = remove_no(no->esq, no_antec->valor);
    }
    return no;
}

/** Remove valor x da árvore de busca binária. Em caso de nó com dois filhos, deve-se trocar de posição com o antecessor do nó removido e o remover então.  */
bool remove_(Arvore* ap_arv, int x){
    if(*ap_arv == NULL)return false;
    if(busca(*ap_arv, x) == true){
        (*ap_arv) = remove_no((*ap_arv), x);
        return true;
    }
    return false;
}
/** Busca valor x na árvore de busca binária */
bool busca(Arvore arv, int x){
    if(arv == NULL)return false;
    if(x == arv->valor)return true;
    if(x < arv->valor)
        return busca(arv->esq, x);
    else
        return busca(arv->dir, x);
    return false;
}
/** Imprime a árvore de busca binária */
void imprime_rec(Arvore arv) {
  if (arv == NULL) {
    printf(".");
    return;
  }
  printf("[%d:e=", arv->valor);
  imprime_rec(arv->esq);
  printf(",d=");
  imprime_rec(arv->dir);
  printf("]");
}
/** Imprime a árvore de busca binária */
void imprime(Arvore arv) {
  imprime_rec(arv);
  printf("\n");
}