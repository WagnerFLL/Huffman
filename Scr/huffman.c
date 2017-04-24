  /*
 * compress.c
 *
 *  Created on: 6 de abr de 2017
 *      Author: Wagner
 */

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

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

struct priority_q{
    Tree *head;
};

priority_queue* creat_priority_queue();

/*
 * Recebe a letra a frequencia e renfileira em prioridade minima
 */

void enqueue(Tree *node, priority_queue *pq);

/*
 * Recebe uma fila e retorna o prmeiro no, o menos frequente;
 */
Tree* dequeue(priority_queue *pq);

/*
 * Recebe um Char e a sua frequencia e retorna um no desse char
 */
Tree* creat_node(BYTE character, int frequencia);

/*
 * Recebe uma fila e retorna a arvore montada
 */
Tree *build_Tree(priority_queue *pq);

/*
 *Ela recebe um ponteiro pra inteiro, correspondendo ao array de frequÃªncia e retorna a arvore montada
 */
Tree* build_huffman_tree(int *array);

/*
 * Recebe o ponteiro para o arquivo original, e o ponteiro pra um array(256 posiÃ§Ãµes) com 0's.
 * Sem retorno, as modificaÃ§Ãµes sÃ£o feitas diretamente no array.
 */
void ler(FILE* arquivo, int* array);

/*
    RECEBE UM PONTEIRO PARA Tree E UM PARA FILE
    GERA UMA STRING CONTENDO A ARVORE IMPRESSA EM PRE-ORDEM
    RETORNA UMA STRING CONTENDO A ARVORE EM PRE-ORDEM
*/
int creating_huffman_string(Tree *huffman, FILE *header);

/*
    RECEBE UM PONTEIRO PARA ARVORE DO TIPO Tree E UM INTEIRO DE PARTIDA
    CONTA A QUANTIDADE DE NÓS DA ARVORE ATRAVÉ DA PRE-ORDEM
    RETORNA UM INTEIRO CONTENDO A QUANTIDADE DE NÓS (CONSIDERANDO OS CARACTERES DE ESCAPE)
*/
int number_of_nodes(Tree *huffman, int n);

/*
    RECEBE 3 PONTEIROS, UM PARA Tree, UM PARA CHAR E UM PARA INTEIRO
    ESSA FUNÇÃO PREENCHE A STRING USANDO A PRE-ORDEM DA ARVORE UTILIZANDO O PONTEIRO DE INTEIRO PARA AUXILIAR NO INDICE
    NÃO POSSUI RETORNO
*/
void writing_pre_order(Tree *huffman, BYTE *string, int *index);

/*
    RECEBE UM CARACTER, UM INTEIRO E UM CARACTER
    SETA COM SHIFT BIT EM i VEZES O BYTE DE mask E COMPARA COM C UTILIZANDO | (OU)
    RETORNA UM VALOR INTEIRO CORRESPONDENTE AO NOVO BYTE SETADO
*/
int set_bit (BYTE character, BYTE mask, int i);

/*
    RECEBE UM PONTEIRO PARA FILE, UMA STRING CONTENDO O HUFFMAN EM PRE-ORDEM E UM INTEIRO CONTENDO O TAMANHO DA STRING
    SETA BITA A BIT OS DOIS PRIMEIROS BYTES DO HEADER (SEM O LIXO) E COLOCA EM UM ARQUIVO txt JUNTO COM A ARVORE
    NÃO POSSUI RETORNO
*/
void putting_huffman_tree_on_header (FILE *header, BYTE *huffman, int huffman_size);

/*
 * Chama todas as funcoes necessarias para compressao dos dados.
 */
void compress();

/*############################################################################################################*/

Tree* build_huffman_tree(int *array){
    priority_queue *init = creat_priority_queue();
    Tree *huffman_tree;

    int a;

    for(a = 255; a >= 0; a--){
        if(*(array+a) != 0)
            enqueue(creat_node(a, *(array+a)), init);
    }

    huffman_tree = build_Tree(init);

    return  (Tree*)huffman_tree;
}

Tree* creat_node(BYTE character, int frequencia){
    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->character= character;
    new_node->frequency = frequencia;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
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

Tree* dequeue(priority_queue *pq){
    if(pq->head == NULL)
        return NULL;
    Tree *aux = pq->head;
    pq->head = pq->head->next;
    aux->next = NULL;
    return aux;
}

Tree *build_Tree(priority_queue *pq){

    Tree *aux;

    while(1){
        aux = creat_node('*', 0);
        aux->left = dequeue(pq);
        if(aux->left != NULL)
            aux->frequency += aux->left->frequency;
        aux->right = dequeue(pq);
        if(aux->right != NULL)
            aux->frequency += aux->right->frequency;
        if(pq->head == NULL)
            break;
        enqueue(aux, pq);
    }
    return aux;
}

void frequency_count(FILE* arquivo, int* array){

    BYTE character;

    while((fscanf(arquivo,"%c",&character)) != EOF){
        ++array[character];
    }

    return;
}

BYTE add_bit(BYTE c_saida, short int pos){
    return (c_saida | (1<<(7-pos)));
}

void write_compress(BYTE tabela[256][150], FILE* arquivo, FILE* saida, int tree_size){

    BYTE aux,character= 0,cond = 1;
    short int tam = 0,pos = 0;

    while((fscanf(arquivo,"%c",&aux)) != EOF){
        pos = 0;

        while(tabela[aux][pos] != '\0'){
            if(tam == 8){
                fprintf(saida,"%c",character);
                tam = 0;
                character = 0;
            }
            if(tabela[aux][pos] & 1)character = add_bit(character,tam);
            ++tam;
            ++pos;
        }
    }

    BYTE lixo = (8 - tam)<<5;
    fprintf(saida,"%c",character);

    //SETANDO O PRIMEIRO BYTE (BITS DO LIXO)

    fseek(saida,0,SEEK_SET);
    lixo = lixo | tree_size>>8;
    fprintf(saida, "%c", lixo);
    lixo = tree_size  & 255;
    fprintf(saida, "%c", lixo);

    return;
}

void criar_tabela(BYTE tabela[][150], Tree* bt, BYTE *k, int p){
    if(bt->left == NULL && bt->right == NULL){
        k[p] = '\0';
        strncpy(tabela[bt->character],k,p+1);
        return;
    }
    if(bt->left != NULL)
    {
        k[p] = '0';
        criar_tabela(tabela,bt->left, k, p+1);
    }
    if(bt->right != NULL)
    {
        k[p] = '1';
        criar_tabela(tabela,bt->right, k, p+1);
    }
}

void write_Tree(Tree *root, int *size, FILE *header){
    if(root->left == NULL && root->right == NULL)
    {
        if(root->character== '\\' || root->character== '*')
        {
            BYTE aux = '\\';
            (*size)++;
            fprintf(header, "%c", aux);
        }
        (*size)++;
        fprintf(header, "%c", root->character);

        return ;
    }
    (*size)++;
    fprintf(header, "%c", root->character);

    if(root->left != NULL)
        write_Tree(root->left, size, header);
    if(root->right != NULL)
        write_Tree(root->right, size, header);

}

int creating_huffman_string(Tree *huffman, FILE *header){
    int *size = (int*) malloc(sizeof(int));
    BYTE aux = 0;
    (*size) = 0;
    fprintf(header, "%c", aux);
    fprintf(header, "%c", aux);
    write_Tree(huffman, size, header);

    return (*size);
}

void compress(){

    char nome_entrada[200],nome_saida[200],aux[150];
    int frequency[256] = {0};

    FILE* arquivo;
    FILE* novo_arquivo;

    while(1){

        system("cls");
        printf("Digite o nome do arquivo:\n");
        scanf("%[^\n]s", nome_entrada);
        getchar();
        arquivo = fopen(nome_entrada,"rb");
        if(arquivo == NULL){
            printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
            system("pause");
            continue;
        }
        printf("Digite o nome do arquivo de saida:\n");
        scanf("%[^\n]s", nome_saida);
        getchar();
        break;
    }

    strcat(nome_saida,".huff");

    frequency_count(arquivo, frequency);
    fseek(arquivo,0,SEEK_SET);
    system("cls");
    printf("Aguarde ...\n");

    Tree* bt = build_huffman_tree(frequency);
    system("cls");
    printf("Aguarde ...\n");

    BYTE tabela[256][150];
    criar_tabela(tabela,bt,aux,0);

    system("cls");
    printf("Aguarde ...\n");

    novo_arquivo = fopen(nome_saida,"wb");

    int size_tree;
    BYTE aux1;
    size_tree = creating_huffman_string(bt, novo_arquivo);

    write_compress(tabela,arquivo,novo_arquivo, size_tree);

    printf("Concluido com exito!");

    fclose(arquivo);
    fclose(novo_arquivo);
}

//###########################################################################################################################################

Tree* creating_nodes (BYTE character){
	Tree *h_tree = (Tree *)malloc(sizeof(Tree));
	h_tree->character = character;
	h_tree->left = NULL;
	h_tree->right = NULL;
	return h_tree;
}

Tree* rebuild_huffman_tree (FILE *arquivo){
    int condition = 1;
    BYTE character;

    fscanf(arquivo, "%c", &character);

    if(character != '*')
    {
        condition = 0;
    }
    if(character == '\\')
    {
        fscanf(arquivo, "%c", &character);
        condition = 0;
    }
    Tree *h_tree = creating_nodes(character);
    if(condition)
    {
        h_tree->left = rebuild_huffman_tree(arquivo);
        h_tree->right = rebuild_huffman_tree(arquivo);
    }

	return (Tree*)h_tree;
}

void write_decompress(Tree *bt, FILE *entrada, FILE *saida, int lixo){
    Tree *aux = bt;
    BYTE character, aux1;
    int i;

    fscanf(entrada, "%c", &character);
    aux1 = character;

    while(fscanf(entrada, "%c", &character) != EOF){

        for(i = 7; i >= 0; i--){

            if(aux->left == NULL && aux->right == NULL){
                fprintf(saida,"%c",aux->character);
                aux = bt;
            }

            if(aux1 & 1<<i)
                aux = aux->right;
            else
                aux = aux->left;
        }
        aux1 = character;
    }

    for(i = 7; lixo <= 8; lixo++, i--){
        if(aux->left == NULL && aux->right == NULL)
        {
            fprintf(saida,"%c",aux->character);
            aux = bt;
        }
        if(aux1 & 1<<i)
            aux = aux->right;
        else
            aux = aux->left;
    }
    return ;
}

int verf(char *nome){
    int condition = 0,i,j,size = strlen(nome);
    char *huff;
    huff = ".huff";

    for(i = size-1,j = 4 ; i>size-6 ; i--,j--)
        if(huff[j] != nome[i])condition = 1;

    if(condition){
        printf("Nao se trata de um arquivo compactado.\nArquivos compactados devem ter a extensao: .huff\n");
        system("pause");
    }
    return condition;
}

void decompress(){

    char nome_entrada[100], nome_saida[100];

    FILE *arquivo_entrada;
    FILE *arquivo_saida;

    BYTE character, *arvore;
    int lixo, size_tree = 0, i;
    Tree *bt = NULL;

    while(1){

        system("cls");
        printf("Digite o nome do arquivo:\n");
        scanf("%[^\n]s", nome_entrada);
        getchar();

        arquivo_entrada = fopen(nome_entrada, "rb");

        if(arquivo_entrada == NULL){
            printf("O nome do arquivo ou caminho esta incorreto!\n Tente novamente...");
            system("pause");
            continue;
        }
        if(verf(nome_entrada))continue;
        printf("O nome do arquivo de saida:\n");
        scanf("%[^\n]s", nome_saida);
        getchar();
        break;
    }

    system("cls");
    printf("Aguarde ...\n");

    // LENDO O TAMANHO DO LIXO
    fscanf(arquivo_entrada, "%c", &character);
    lixo = character>>5;

    // LENDO O TAMANHO DA ARVORE
    size_tree = character & 0b00011111;
    size_tree = size_tree << 8;
    fscanf(arquivo_entrada, "%c", &character);
    size_tree = size_tree | character;


    arvore = (BYTE*) malloc((sizeof(unsigned char)*size_tree));

    system("cls");
    printf("Aguarde ...\n");

    bt = rebuild_huffman_tree(arquivo_entrada);
    arquivo_saida = fopen(nome_saida, "wb");

    write_decompress(bt, arquivo_entrada, arquivo_saida, lixo);

    printf(" Concluido com exito\n");

    fclose(arquivo_saida);
    fclose(arquivo_entrada);

    return;
}
//##########################################################################################################################3

int main(){

    int option;

    while(1){

        printf("  Escolha uma das opcoes: \n");
        printf("  Tecle 1 para comprimir. \n");
        printf("  Tecle 2 para descomprimir.\n  ");

        scanf("%d",&option);
        getchar();

        if(option == 1){
            compress();
            system("pause");
            break;
        }
        else if(option == 2){
            decompress();
            system("pause");
            break;
        }
        else{
            printf("Opcao invalida! Tente Novamente.\n");
        }
        system("cls");
    }

    getchar();
}


