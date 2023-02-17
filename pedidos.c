/* Aqui os pedidos devem ser gerados de forma infinita
seguindo regras como sempre ter o pão na parte de cima e de baixo
e alternarem entre 4-8 ingredientes, sendo eles 
-pão = 1
-hamburguer = 2
-alface = 3 
-tomate = 4
-queijo = 5 
-cebola = 6

O que precisa ser feito é:
- Criar a lista que deve incorporar os pedidos
- Criar a função que gera os pedidos
- Criar um tempo para cada pedido que estara dentro da estrutura de dados dele
- Criar uma função que reconhece se o pedido montado é igual a algum dos pedidos na lista
- Criar uma função que remove os pedidos que já foram entregues
- Criar uma função que remove o pedido caso ele não tenha sido entregue dentro de um tempo limite
- Criar função que retorna um número de pontos para cada pedido entregue dentro do tempo limite
- Criar função que subtrai uma quantidade de pontos por pedidos expirados 
*/
#include "dbheader.h"


struct list* createList(){
    struct list* newList = malloc(sizeof(struct list));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}

struct orderNode* createNode(int id, struct order order){
    struct orderNode* newNode = malloc(sizeof(struct orderNode));
    newNode->id = id;
    newNode->nxtOrder = NULL;
    return newNode;
}

void addOrderNode(struct list* list, struct orderNode* orderNode){
    if(list->head == NULL){
        list->head = orderNode;
        list->tail = orderNode;
    }
    else{
        list->tail->nxtOrder = orderNode;
        list->tail = orderNode;
    }
    list->size++;
}

void removeOrderNode(struct list* list, struct orderNode* orderNode){
    struct orderNode* aux = list->head;
    if(aux == orderNode){
        list->head = aux->nxtOrder;
        free(aux);
    }
    else{
        while(aux->nxtOrder != orderNode){
            aux = aux->nxtOrder;
        }
        aux->nxtOrder = orderNode->nxtOrder;
        free(orderNode);
    }
    list->size--;
}

void sortTime(struct orderNode* head){
    // função que ordena os pedidos de acordo com o tempo limite
    struct orderNode* aux;
    int trades;

    if(head == NULL){
        return;
    }
    while(1){
        aux = head;
        trades = 0;
        while(aux->nxtOrder != NULL){
            if(aux->id->deadline > aux->nxtOrder->id->deadline){
                struct orderNode* temp = aux->id;
                aux->id = aux->nxtOrder->id;
                aux->nxtOrder->id = temp;
                trades++;
            }
            aux = aux->nxtOrder;
        }
        if(trades == 0){
            return;
        }
    }
}

int genNumIng(int numIng){
    // função que gera um número aleatório de ingredientes entre 4 e 8
    return (rand() % 5 + 4);
}

int genIngredients(int numIng){
    // função que gera um vetor de ingredientes aleatórios
    int* ing = malloc (numIng*sizeof(int));
    ing[0] = 1;
    ing[numIng-1] = 1;

    int gnr;

    for(int i = 1; i < numIng-1; i++){
        ing[i] = (rand() % 6 + 2);
    }
    return ing;
}

struct order* createOrder(int numIng, int* ingredients){
    struct order* newOrder = malloc(sizeof(struct order));
    newOrder->numIng = genNumIng(numIng);
    newOrder->ingredients = genIngredients(numIng);
    return newOrder;
}
