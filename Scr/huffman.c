 /*
 * compress.c
 *
 *  Created on: 6 de abr de 2017
 *      Author: Wagner
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct _tree Tree;
typedef struct _deck deck;

deck* creat_deck();

/*
 * Recebe a letra a frequencia e renfileira em prioridade minima
 */
void enqueue(Tree *node, deck *deck);

/*
 * Recebe uma fila e retorna o prmeiro no, o menos frequente;
 */
Tree* dequeue(deck *deck);

/*
 * Recebe um Char e a sua frequencia e retorna um no desse char
 */
Tree* creat_node(unsigned char character, int frequencia);

/*
 * Recebe uma fila e retorna a arvore montada
 */
Tree *bilding_Tree(deck *deck);

/*
 *Ela recebe um ponteiro pra inteiro, correspondendo ao array de frequÃªncia e retorna a arvore montada
*/
Tree* Biulding_huffman_tree(int *array);

/*
 * Recebe o ponteiro para o arquivo original, e o ponteiro pra um array(256 posiÃ§Ãµes) com 0's.
 * Sem retorno, as modificaÃ§Ãµes sÃ£o feitas diretamente no array.
 */
void ler(FILE* arquivo, int* array);

/*
* Chama todas as funÃ§Ãµes necessÃ¡rias para compressÃ£o dos dados.
 */
void compress();

/*############################################################################################################*/

Tree* Biulding_huffman_tree(int *array){
    deck *init = creat_deck();
    Tree *huffman_tree;

    int a;

    for(a = 255; a >= 0; a--){
        if(*(array+a) != 0)
            enqueue(creat_node(a, *(array+a)), init);
    }

    huffman_tree = bilding_Tree(init);

    return  (Tree*)huffman_tree;
}

struct _tree{
    int repear;
    unsigned char c;
    Tree *next;
    Tree *left;
    Tree *right;
};

struct _deck{
    Tree *head;
};

Tree* creat_node(unsigned char character, int frequencia){
    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->c = character;
    new_node->repear = frequencia;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

deck* creat_deck(){
    deck *new_deck = (deck*) malloc(sizeof(deck));
    new_deck->head = NULL;
    return new_deck;
}

void enqueue(Tree *new_node, deck *deck){

    if(deck->head == NULL || deck->head->repear >= new_node->repear){
        new_node->next = deck->head;
        deck->head = new_node;
        return ;
    }

    Tree *aux = deck->head;
    while(aux->next != NULL && aux->next->repear < new_node->repear)
        aux = aux->next;
    new_node->next = aux->next;
    aux->next = new_node;
    return ;
}

Tree* dequeue(deck *deck){
    if(deck->head == NULL)
        return NULL;
    Tree *aux = deck->head;
    deck->head = deck->head->next;
    aux->next = NULL;
    return aux;
}

Tree *bilding_Tree(deck *deck){

	Tree *aux;

    while(1){
        aux = creat_node('*', 0);
        aux->left = dequeue(deck);
        if(aux->left != NULL)
            aux->repear += aux->left->repear;
        aux->right = dequeue(deck);
        if(aux->right != NULL)
            aux->repear += aux->right->repear;
        if(deck->head == NULL)
            break;
        enqueue(aux, deck);
    }
    return aux;
}

void ler(FILE* arquivo, int* array){

	unsigned char capture;

	while((fscanf(arquivo,"%c",&capture)) != EOF){
		++array[capture];
	}
    /*
	int a;
	for(a = 0; a < 256; a++)
    {
        if(array[a] != 0)
            printf("%d %d\n", a, array[a]);
    }
    */

	return;
}

unsigned char add_bit(unsigned char c_saida, short int pos){
    return (c_saida | (1<<(7-pos)));
}

int write(unsigned char tabela[256][150], FILE* arquivo, FILE* saida){

    unsigned char aux,c = 0,cond = 1;
    short int tam = 0,pos = 0;


    while((fscanf(arquivo,"%c",&aux)) != EOF){
        printf(".");
        pos = 0;

        while(tabela[aux][pos] != '\0'){

            if(tam == 8){
                fprintf(saida,"%c",c);
                tam = 0;
                c = 0;
            }

            if(tabela[aux][pos] == '1')c = add_bit(c,tam);

            ++tam;
            ++pos;
        }
    }
    printf("\n");
    int lixo = 8 - tam;
    fprintf(saida,"%c",c);
    return lixo;
}

void criar_tabela(unsigned char tabela[256][150], Tree* bt, unsigned char *k, int p){
	if(bt->left == NULL && bt->right == NULL){
        k[p] = '\0';
        strcpy(tabela[bt->c],k);
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

void compress(){

	char name[200],aux[150];
	int frequency[256] = {0};

    FILE* arquivo;
    FILE* novo_arquivo;

	while(1){
		printf("-------------------------\n");
		printf("Digite o nome do arquivo:\n");
		printf("-------------------------\n");
		printf("> ");
		scanf("%s",name);
		arquivo = fopen(name,"rb");
		if(arquivo == NULL){
			printf("O nome do arquivo ou caminho\nesta incorreto!\n Tente novamente...");
			getchar();
			system("cls");
		}else{
			break;
		}
	}

	ler(arquivo, frequency);
	fseek(arquivo,0,SEEK_SET);
    printf("Lido!\n");

	Tree* bt = Biulding_huffman_tree(frequency);
    printf("Arvore feita!\n");

    unsigned char tabela[256][150];
    criar_tabela(tabela,bt,aux,0);
    /*
    int a;
    for(a = 0; a < 256; a++)
    {
        if(tabela[a][1] == '1' || tabela[a][1] == '0')
            printf("%d %s\n", a, tabela[a]);
    }
    */
    printf("Tabela criada!\n");

    novo_arquivo = fopen("gerado","wb");

    int lixo = write(tabela,arquivo,novo_arquivo);
    //printf("%d\n", lixo);
    printf("Arquivo escrito!");

    fclose(arquivo);
    fclose(novo_arquivo);
}


int main(){

    int option;

    while(1){
        printf("--------------------------\n");
        printf("  Escolha uma das opcoes: \n");
        printf("  Tecle 1 para comprimir. \n");
        printf("  Tecle 2 para descomprimir.\n");
        printf("--------------------------\n");
        printf("> ");
        scanf("%d",&option);

        if(option == 1){
            compress();
            break;
        }
        else if(option == 2){
            //descompress();
            break;
        }
        else{
            printf("Opcao invÃ¡lida! Tente Novamente.\n");
        }
        system("cls");
    }

    getchar();
    getchar();
}
