#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "tree.h"
#include <stdio.h>


/*
 * Funções internas:
 */

/*
 * Função: write_decompress
 * Recebe a árvore do huffman, o arquivo a ser descompactado, o arquivo onde será armazenado e a quantidade de bits de lixo ao fim do arquivo.
 * Não tem nenhum retorno, todas as alterações são armazenadas diretamente no arquivo de saída.
 */
static void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo);

/*
 * Função: verification
 * Recebe o nome do arquivo a ser descompactado e verifica se é um arquivo com extensão ".huff".
 * Retorna 0, caso a extensão esteja correta. Retorna 1 caso não seja um arquivo ".huff".
 */
static int verification(char *nome);

//##############################

/*
 * Função: decompress
 * Não recebe nenhum dado. Mas efetua a leitura do nome do arquivo a ser descompactado e o abre.
 * Chama as funções necessárias para descompactação.
 * Não retorna nenhum valor, o arquivo final será aberto e finalizado nela.
 */
void decompress();

#endif // DECOMPRESS_H
