#include "tree.h"
#include "queue.h"

Tree *func_exception(FILE *arquivo);

/*
 * Constrói a árvore de huffman a partir do cabeçalho do arquivo.
 */
Tree* rebuild_huffman_tree (FILE *arquivo);

/*
 * Recebe um ponteiro pra inteiro, correspondendo ao array de frequência e retorna a arvore montada.
 */
Tree* build_huffman_tree(int *array);

/*
 * Recebe uma fila e monta a árvore de huffman.
 */
Tree *build_Tree(priority_queue *pq);

/*
 * Recebe um ponteiro para a árvore de huffman e inicia o processo que gera a partir dela uma string em pré-ordem. 
 * Recebe um ponteiro para o arquivo de saída e escreve dois bytes vazios no início.
 */
int creating_huffman_string(Tree *huffman, FILE *header);

// gcc main.c compress.h compress.c decompress.h decompress.c building.h building.c tree.h tree.c queue.h queue.c -o test2.exe