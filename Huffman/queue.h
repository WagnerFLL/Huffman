#ifndef QUEUE_H
#define  QUEUE_H

#include "tree.h"

typedef struct priority_q priority_queue;

struct priority_q{
    Tree *head;
};

/*
 * Cria uma lista de prioridades vazia.
 */
priority_queue* creat_priority_queue();

/*
 * Recebe a letra a frequencia e renfileira em prioridade minima.
 */
void enqueue(Tree *node, priority_queue *pq);

/*
 * Recebe uma fila e retorna o prmeiro no, o menos frequente.
 */
Tree* dequeue(priority_queue *pq);

#endif // QUEUE_H
