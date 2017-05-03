#include "tree.h"

Tree* creat_node(BYTE character, int frequencia){

    Tree *new_node = (Tree*) malloc(sizeof(Tree));
    new_node->character= character;
    new_node->frequency = frequencia;
    new_node->next = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
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
