#include<stdio.h>
#include<stdlib.h>
#include "polinomio.h"
/*
 * Implemente as seguintes funcoes de um Tipo Abstrato de Dados de um 
 * Polinômio de coeficientes inteiros. Utilize uma lista circular
 * duplamente ligada com no cabeca, mantendo sempre os coeficientes 
 * ordenados por grau. Somente os coeficientes nao zero devem ser armazenados.
 */

/* Inicializa um polinômio vazio. */
void inicializa_polinomio(Polinomio * ap_pol){
    Polinomio cabeca = (Polinomio)malloc(sizeof(No));
    cabeca->valor.grau = -1;
    cabeca->valor.coef = -1;
    cabeca->prox = cabeca;
    cabeca->antec = cabeca;
    (*ap_pol) = cabeca;
}

void primeira_insercao(Polinomio cabeca_pol, int grau, int coef){
    Polinomio novo_no = (Polinomio)malloc(sizeof(No));
    novo_no->valor.coef = coef;
    novo_no->valor.grau = grau;
    novo_no->prox = cabeca_pol;
    novo_no->antec = cabeca_pol;
    cabeca_pol->prox = novo_no;
    cabeca_pol->antec = novo_no;
}

/* Define que o coeficiente de grau grau do polinomio pol eh igual a coef. Deve manter os 
 * coeficientes ordenados por grau. */
void define_coeficiente(Polinomio cabeca_pol, int grau, int coef){
    if(coef == 0)return;
    Polinomio atual = cabeca_pol->prox;
    if(atual == cabeca_pol){
        primeira_insercao(cabeca_pol, grau, coef);
        return;
    }else{
        while(atual != cabeca_pol && atual->valor.grau < grau)
            atual = atual->prox;
        Polinomio no_antec = atual->antec;
        Polinomio novo = (Polinomio)malloc(sizeof(No));
        novo->valor.grau = grau;
        novo->valor.coef = coef;
        novo->antec = no_antec;
        no_antec->prox->antec = novo;
        novo->prox = no_antec->prox;
        no_antec->prox = novo;
    }
}

/* Zera o polinomio, tornando-o um polinomio inicializado, mas igual a zero. Desaloca a memória liberada. 
*/
void zera(Polinomio pol){
    Polinomio cabecaAux = pol;
    Polinomio atual = pol->prox;
    while(atual != cabecaAux){
        Polinomio remove = atual;
        remove->antec->prox = remove->prox;
        remove->prox->antec = remove->antec;
        free(remove);
        atual = atual->prox;
    }
}

/* Computa a soma dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void soma(Polinomio res, Polinomio a, Polinomio b){
    zera(res);
    Polinomio atualA = a->prox;
    Polinomio atualB = b->prox; 
    Polinomio cabecaRes = res;
    Polinomio antecRes = res;
    while(atualA != a && atualB != b){
        if(atualA->valor.grau == atualB->valor.grau){
            int valorRes = atualA->valor.coef + atualB->valor.coef;
            if(valorRes != 0){
                Polinomio novo = (Polinomio)malloc(sizeof(No));
                novo->valor.grau = atualA->valor.grau;
                novo->valor.coef = valorRes;
                novo->antec = antecRes;
                novo->prox = cabecaRes;
                antecRes->prox = novo;
                cabecaRes->antec = novo;
                antecRes = antecRes->prox;
                atualA = atualA->prox;
                atualB = atualB->prox;
            }else{
                atualA = atualA->prox;
                atualB = atualB->prox;
            }
        }else if(atualA->valor.grau < atualB->valor.grau){
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualA->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualA = atualA->prox;
        }else{
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualB->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualB = atualB->prox;
        }
    }
    if(atualB == b && atualA != a){
        while(atualA != a){
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualA->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualA = atualA->prox;
        }
        return;
    }else if(atualA == a && atualB != b){
        while(atualB != b){
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualB->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualB = atualB->prox;
        }
        return;
    }
} 

/* Computa a subtracao dos polinomios a e b colocando o resultado em res. 
 * Libera a memória anteriormente utilizada pelos nos descartados de res, e sobreescreve res. */
void subtrai(Polinomio res, Polinomio a, Polinomio b){
    zera(res);
    Polinomio atualA = a->prox;
    Polinomio atualB = b->prox; 
    Polinomio cabecaRes = res;
    Polinomio antecRes = res;
    while(atualA != a && atualB != b){
        if(atualA->valor.grau == atualB->valor.grau){
            int valorRes = atualA->valor.coef - atualB->valor.coef;
            if(valorRes != 0){
                Polinomio novo = (Polinomio)malloc(sizeof(No));
                novo->valor.grau = atualA->valor.grau;
                novo->valor.coef = valorRes;
                novo->antec = antecRes;
                novo->prox = cabecaRes;
                antecRes->prox = novo;
                cabecaRes->antec = novo;
                antecRes = antecRes->prox;
                atualA = atualA->prox;
                atualB = atualB->prox;
            }else{
                atualA = atualA->prox;
                atualB = atualB->prox;
            }
        }else if(atualA->valor.grau < atualB->valor.grau){
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualA->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualA = atualA->prox;
        }else{
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor.grau = atualB->valor.grau;
            novo->valor.coef = -(atualB->valor.coef);
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualB = atualB->prox;
        }
    }
    if(atualB == b && atualA != a){
        while(atualA != a){
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualA->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualA = atualA->prox;
        }
        return;
    }else if(atualA == a && atualB != b){
        while(atualB != b){
            Polinomio novo = (Polinomio)malloc(sizeof(No));
            novo->valor = atualB->valor;
            novo->antec = antecRes;
            novo->prox = cabecaRes;
            antecRes->prox = novo;
            cabecaRes->antec = novo;
            antecRes = antecRes->prox;
            atualB = atualB->prox;
        }
        return;
    }
}

/* Imprime o polinomio pol no formato do exemplo abaixo
 * [(0,2),(3,-2),(10,5)]
 * onde este polinomio tem 3 coeficientes, o de grau 0 com valor 2, o de grau 3 com valor -2 e o de
 * grau 10 com valor 5. 
 */
void imprime(Polinomio pol){
    Polinomio atual = pol->prox;
    printf("[");
    while(atual != pol){
        printf("(%d,%d)", atual->valor.grau, atual->valor.coef);
        if(atual->prox != pol)
            printf(",");
        atual = atual->prox;
    }
    printf("]\n");
}

/* Desaloca toda a memória alocada da lista.
 */
void desaloca_polinomio(Polinomio *ap_pol){
    Polinomio atual = (*ap_pol)->prox;
    while(atual != (*ap_pol)){
        Polinomio remove = atual;
        remove->antec->prox = remove->prox;
        remove->prox->antec = remove->antec;
        atual = atual->prox;
        free(remove);
    }
    free(*ap_pol);
}
