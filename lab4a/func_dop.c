#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_dop.h"

int add_elem(Node **root, char key[100]){
    Node *par = *root;
    Node *ptr = *root;
    Node *new = create_new();
    strcpy(new->key, key);
    new->version = 1;
    if(ptr == NULL)
        *root = new;
    else {
        while (ptr != NULL) {
            if (strcmp(key, ptr->key) < 0) {
                par = ptr;
                ptr = ptr->left;
            } else if (strcmp(key, ptr->key) > 0) {
                par = ptr;
                ptr = ptr->right;
            } else {
                ptr->version ++;
				free(new);
                return 1;//updated
            }
        }
        if (strcmp(key, par->key) < 0)
            par->left = new;
        else
            par->right = new;
    }
    return 0;//added
}

int delete_tree(Node *ptr){
    if(ptr == NULL)
        return 0;
    delete_tree(ptr->left);
    delete_tree(ptr->right);
  	free(ptr);
    return 0;
}

int load_tree(Node *ptr, FILE *output){
    if(ptr == NULL) {
        return 0;
    }
    load_tree(ptr->left, output);
    fprintf(output, "%s   %d\n", ptr->key, ptr->version);
    load_tree(ptr->right, output);
    return 0;
}

Node *create_new(){
    Node *node;
    node = (Node *) calloc(1, sizeof(Node));
    return node;
}

int print_beaty_tree(Node *ptr, int i){
    if(ptr == NULL)
        return 0;
    print_beaty_tree(ptr->right, i + 1);
    for(int i=0; i < i; i++, printf("  "));
    printf("%s\n", ptr->key);
    print_beaty_tree(ptr->left, i + 1);
    return 0;
}
