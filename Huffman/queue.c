#include "queue.h"

Tree* dequeue(priority_queue *pq){
    
    if(pq->head == NULL)
        return NULL;
    Tree *aux = pq->head;
    pq->head = pq->head->next
;    aux->next = NULL;
    return aux;
}

priority_queue* creat_priority_queue(){

    priority_queue *new_pq = (priority_queue*) malloc(sizeof(priority_queue));
    new_pq->head = NULL;
    return new_pq;

}

void enqueue(Tree *new_node, priority_queue *pq){

    if(pq->head == NULL || pq->head->frequency >= new_node->frequency){
        new_node->next = pq->head;
        pq->head = new_node;
        return ;
    }

    Tree *aux = pq->head;
    while(aux->next != NULL && aux->next->frequency < new_node->frequency)
        aux = aux->next;
    new_node->next = aux->next;
    aux->next = new_node;
    return ;
}