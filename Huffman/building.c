#include "building.h"


Tree *func_exception(FILE *arquivo){
    BYTE character;
    fscanf(arquivo, "%c", &character);

    Tree *h_tree = creat_node(character,0);
    fscanf(arquivo, "%c", &character);
    if(character == '\\') fscanf(arquivo, "%c", &character);
    h_tree->left = creat_node(character, 0);
    return (Tree*) h_tree;

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
    Tree *h_tree = creat_node(character,0);
    if(condition)
    {
        h_tree->left = rebuild_huffman_tree(arquivo);
        h_tree->right = rebuild_huffman_tree(arquivo);
    }

	return (Tree*)h_tree;
}

Tree* build_huffman_tree(int *array){
    
    priority_queue *pq = creat_priority_queue();
    Tree *huffman_tree;

    int i;

    for(i = 255; i >= 0; i--){
        if(*(array+i) != 0)
            enqueue(creat_node(i, *(array+i)), pq);
    }

    huffman_tree = build_Tree(pq);

    return  (Tree*)huffman_tree;
}

Tree* build_Tree(priority_queue *pq){

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

int creating_huffman_string(Tree *huffman, FILE *header){
  
    int *size = (int*) malloc(sizeof(int));
    BYTE aux = 0;
    (*size) = 0;
    fprintf(header, "%c", aux);
    fprintf(header, "%c", aux);
    write_Tree(huffman, size, header);

    return (*size);
}
