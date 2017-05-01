#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BYTE;

typedef struct _tree Tree;
typedef struct priority_q priority_queue;

struct _tree{
    int frequency;
    BYTE character;
    Tree *next;
    Tree *left;
    Tree *right;
};

/*
 * Recebe um caractere e retorna um no só com essa informação.
 */
Tree* creating_nodes (BYTE character);


/*
 * Recebe um Char e a sua frequencia e retorna um no com esse char.
 */
Tree* creat_node(BYTE character, int frequencia);

/*
 * FALTA COMENTAR!!!!!!!!!!!!!!!!!!!
 */
void write_Tree(Tree *root, int *size, FILE *header);

#endif // TREE_H
