#ifndef COMPRESS_H
#define COMPRESS_H

#include "building.h"

/*
 * Recebe o ponteiro para o arquivo original, e o ponteiro pra um array.
 * Sem retorno, as modificações são feitas diretamente no array.
 */
void frequency_count(FILE* arquivo, int* array);

/*
 * Recebe um BYTE e a posição onde será alocado o bit.
 * Retorna um BYTE com o novo bit setado.
 */
BYTE add_bit(BYTE c_saida, short int pos);

/*
 * Recebe uma matriz(tipo byte) e o ponteiro pra arvore de huffman e para uma string vazia. Variável position inicia como 0.
 * Retorna a tabela(matriz de byte) com os caminhos de cada folha(character) na árvore.
 */
void creat_table(BYTE tabela[][150], Tree* bt, BYTE *string, int position);

/*
 * Chama todas as funcoes necessarias para compressao dos dados.
 */
void compress();

/*
 * Recebe a tabela, os arquivos e o tamanho da arvore. Escreve os bytes comprimdos no arquivo final.
 */
void write_compress(BYTE tabela[][150], FILE* arquivo, FILE* saida, int tree_size);

#endif // COMPRESS_H