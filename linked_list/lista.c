#include<stdlib.h>
#include "lista.h"

/* Inicializa a lista como lista vazia. */
void inicializa_lista(Lista * ap_lista){
    (*ap_lista) = NULL;
}

/* Insere valor no fim da lista apontada por ap_lista. ap_lista aponta para o inicio da lista. */
void insere_fim(Lista * ap_lista, int valor){
    if(*ap_lista == NULL)
        insere_inicio(&(*ap_lista), valor);
    else{
        No* novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->proximo = NULL;
        No* ap_atual = *ap_lista;
        while(ap_atual->proximo != NULL)
            ap_atual = ap_atual->proximo;
        ap_atual->proximo = novo;
    }
}

/* Insere valor no inicio da lista apontada por ap_lista. */
void insere_inicio(Lista * ap_lista, int valor){
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = (*ap_lista);
    (*ap_lista) = novo;  
}

/* Remove valor do fim da lista apontada por ap_lista e retorna este valor.*/
int remove_fim(Lista* ap_lista){
    if(*ap_lista == NULL)return -1;
    No* ap_atual = *ap_lista;
    No* ap_antecessor = NULL;
    No* ap_segundo  = (*ap_lista)->proximo;
    int valor_removido;
    if(ap_atual->proximo == NULL){
        valor_removido = remove_inicio(&(*ap_lista));
        return valor_removido;
    }else if(ap_segundo->proximo == NULL){
        ap_antecessor = ap_atual;
        valor_removido = ap_segundo->valor;
        free(ap_segundo);
        ap_antecessor->proximo = NULL;
        return valor_removido;
    }else{
        while(ap_atual->proximo != NULL){
            ap_antecessor = ap_atual;
            ap_atual = ap_atual->proximo;
        }
        valor_removido = ap_atual->valor;
        free(ap_atual);
        ap_antecessor->proximo = NULL;
        return valor_removido;
    }
}

/* Remove valor do inicio da lista apontada por ap_lista e retorna este valor. */
int remove_inicio(Lista* ap_lista){
    if(*ap_lista == NULL)return -1;
    No* ap_removido = *ap_lista;
    *ap_lista = (*ap_lista)->proximo;
    int valor_removido = ap_removido->valor;
    free(ap_removido);
    return valor_removido;
}

/* Remove o i-ésimo elemento da lista, caso ele exista. Retorna se o elemento 
foi removido. As posições são contadas a partir de 1, sendo 1 a primeira posição. */
bool remove_i_esimo(Lista * ap_lista, int i){
    if(*ap_lista == NULL)return false;
    No** ap_atual = ap_lista;
    int posicao=1;
    while(*ap_atual != NULL){
        if(i == posicao){
            No* ap_remove = (*ap_atual);
            (*ap_atual) = (*ap_atual)->proximo;
            free(ap_remove);
            return true;
        }else{
            posicao++;
            ap_atual = &((*ap_atual)->proximo);
        }
    }
    return false;
}

/* Retorna o valor do i-ésimo elemento da lista, caso ele exista. 
Retorna -1 caso contrário. As posições são contadas a partir de 1, sendo 1 a primeira posição. */
int recupera_i_esimo(Lista lista, int i){
    if(lista == NULL)return -1;
    int posicao=1;
    while(lista != NULL){
        if(i == posicao)
            return lista->valor;
        lista = lista->proximo;
        posicao++;
    }
    return -1;
}
/* Retorna o tamanho da lista. */
int tamanho(Lista lista){
    int contador=0;
    if(lista == NULL)return 0;
    while(lista != NULL){
        contador++;
        lista = lista->proximo;
    }
    return contador;
}

/* Remove todas as ocorrencias de valor da lista apontada por ap_lista. 
 * Retorna o numero de ocorrencias removidas.
 */
int remove_ocorrencias(Lista* ap_lista, int valor){
    if(*ap_lista == NULL)return -1;
    int ocorrencias=0;
    Lista* ap_atual = ap_lista;
    while(*ap_atual != NULL){
        if((*ap_atual)->valor == valor){
            No* ap_remove = (*ap_atual);
            (*ap_atual) = (*ap_atual)->proximo;
            free(ap_remove);
            ocorrencias++;
        }else
            ap_atual = &((*ap_atual)->proximo);
    }
    return ocorrencias;
}

/* Busca elemento valor na lista. 
   Retorna a posição na lista, comecando de 0=primeira posicao.
   Retorna -1 caso nao encontrado.
*/
int busca(Lista lista, int valor){
    if(lista == NULL)return -1;
    int posicao=0;
    while(lista != NULL && lista->valor != valor){
        posicao++;
        if(lista->proximo == NULL)break;
        lista = lista->proximo;
    }
    if(lista->valor == valor)return posicao;
    return -1;
}

/* Imprime a lista na saida padrao, no formato:
   (1,3,2,3,4,2,3,1,4)
   em uma linha separada.
 */
void imprime(Lista lista){
    if(lista == NULL){
        printf("()\n");
        return;
    }
    printf("(");
    while(lista != NULL){
        printf("%d", lista->valor);
        if(lista->proximo != NULL)
            printf(",");
        lista = lista->proximo;
    }
    printf(")\n");    
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_lista(Lista *ap_lista){
    No* remove;
    while((*ap_lista) != NULL){
        remove = *ap_lista;
        (*ap_lista) = (*ap_lista)->proximo;
        free(remove);
    }
    (*ap_lista) = NULL;
    remove = NULL;
}