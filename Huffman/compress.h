#ifndef COMPRESS_H
#define COMPRESS_H

#include <stdio.h>
#include <string.h>
#include "tree.h"

/*
 * Função: frequency_count
 * Recebe o ponteiro para o arquivo original, e o ponteiro pra um array.
 * Sem retorno, as modificações são feitas diretamente no array.
 */
void frequency_count(FILE* arquivo, int* array);

/*
 * Função: add_bit
 * Recebe um BYTE e a posição onde será alocado o bit.
 * Retorna um BYTE com o novo bit setado.
 */
BYTE add_bit(BYTE c_saida, short int pos);

/*
    RECEBE UM PONTEIRO PARA Tree E UM PARA FILE
    GERA UMA STRING CONTENDO A ARVORE IMPRESSA EM PRE-ORDEM
    RETORNA UMA STRING CONTENDO A ARVORE EM PRE-ORDEM
*/
int creating_huffman_string(Tree *huffman, FILE *header);

/*
 * Função: creat_table
 * Recebe uma matriz(tipo byte) e o ponteiro pra arvore de huffman e para uma string vazia. Variável position inicia como 0.
 * Retorna a tabela(matriz de byte) com os caminhos de cada folha(character) na árvore.
 */
void creat_table(BYTE tabela[][150], Tree* bt, BYTE *string, int position);

/*
 * Função: creating_huffman_string
 * Recebe um ponteiro para a árvore de huffman e inicia o processo que gera a partir dela uma string. Recebe um ponteiro para o arquivo de saída e escreve dois bytes vazios no início.
 */
int creating_huffman_string(Tree *huffman, FILE *header);

/*
 * Chama todas as funcoes necessarias para compressao dos dados.
 */
void compress();

#endif // COMPRESS_H
