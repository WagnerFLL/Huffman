#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include "queue.h"

typedef unsigned char BYTE;

typedef struct _tree Tree;

struct _tree{
    int frequency;
    BYTE character;
    Tree *next;
    Tree *left;
    Tree *right;
};

/*
 * FALTA COMENTAR!!!!!!!!!!!!!!!!!
 */
Tree* creating_nodes (BYTE character);

/*
 * FALTA COMENTAR!!!!!!!!!!!!!!!!!
 */
Tree* rebuild_huffman_tree (FILE *arquivo);

/*
 * Recebe um Char e a sua frequencia e retorna um no desse char
 */
static Tree* creat_node(BYTE character, int frequencia);

/*
 * Recebe uma fila e retorna a arvore montada
 */
static Tree *build_Tree(priority_queue *pq);

/*
 *Ela recebe um ponteiro pra inteiro, correspondendo ao array de frequÃªncia e retorna a arvore montada
 */
Tree* build_huffman_tree(int *array);

/*
 * FALTA COMENTAR!!!!!!!!!!!!!!!!!!!
 */
void write_Tree(Tree *root, int *size, FILE *header);

#endif // TREE_H
