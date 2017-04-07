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
 *Ela recebe um ponteiro pra inteiro, correspondendo ao array de frequência e retorna a arvore montada
*/
Tree* Biulding_huffman_tree(int *array);

/*
 * Recebe o ponteiro para o arquivo original, e o ponteiro pra um array(256 posições) com 0's.
 * Sem retorno, as modificações são feitas diretamente no array.
 */
void ler(FILE* arquivo, int* array);

/*
* Chama todas as funções necessárias para compressão dos dados.
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
    unsigned char chracter;
    Tree *next;
    Tree *left;
    Tree *right;
};

struct _deck{
    Tree *head;
};

Tree* creat_node(unsigned char character, int frequencia){
    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->chracter = character;
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

	return;
}

//IGNOREM ESSA!!!
void demonstration_func(Tree* bt){
	if(bt == NULL)return;
	printf("%c | %d\n",bt->chracter,bt->repear);
	demonstration_func(bt->left);
	demonstration_func(bt->right);
}

void compress(){

	char name[200];
	int frequency[256] = {0};

    FILE* arquivo;

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

	Tree* bt = Biulding_huffman_tree(frequency);

	demonstration_func(bt);

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
            printf("Opcao inválida! Tente Novamente.\n");
        }
        system("cls");
    }

}
