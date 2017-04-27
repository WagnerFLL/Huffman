#ifndef QUEUE_H
#define  QUEUE_H

#include <stdio.h>
#include "tree.h"

typedef struct priority_q priority_queue;

struct priority_q{
    Tree *head;
};

/*
 * Função: creat_priority_queue
 * Cria uma lista de prioridades vazia.
 */
priority_queue* creat_priority_queue();

/*
 * Função: enqueue
 * Recebe a letra a frequencia e renfileira em prioridade minima.
 */
void enqueue(Tree *node, priority_queue *pq);

/*
 * Função: dequeue
 * Recebe uma fila e retorna o prmeiro no, o menos frequente.
 */
Tree* dequeue(priority_queue *pq);

#endif // QUEUE_H
