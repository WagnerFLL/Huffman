#include "queue.h"
#include "tree.h"

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

//####################################################################33

static Tree* creat_node(BYTE character, int frequencia){

    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->character= character;
    new_node->frequency = frequencia;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

static Tree* build_Tree(priority_queue *pq){

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

void write_Tree(Tree *root, int *size, FILE *header){

    if(root->left == NULL && root->right == NULL){

        if(root->character== '\\' || root->character== '*'){

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
