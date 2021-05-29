#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        puts("Make your choice: ");
        choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

char *get_str() {
    char buf[81] = {};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len =(int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

List *new_version(List *next, char *info){
    List *head;
    head = (List *) calloc(1, sizeof(List));
    head->next = next;
    head->info = (char *) calloc(strlen(info)+1, sizeof(char));
    memcpy(head->info, info, strlen(info)+1);
    if(next == NULL)
        head->release = 1;
    else
        head->release = head->next->release + 1;
    return head;
}

int add_elem(Node **root, char *key, char *info){
    Node *par = *root;
    Node *ptr = *root;
    Node *new = create_new();
    memcpy(new->key, key, strlen(key));
    new->versions = new_version(new->versions, info);;
    if(ptr == NULL)
        *root = new;
    else {
        while (ptr != NULL) {
            if (strcmp(key, (ptr)->key) < 0) {
                par = ptr;
                (ptr) = (ptr)->left;
            } else if (strcmp(key, (ptr)->key) > 0) {
                par = ptr;
                (ptr) = (ptr)->right;
            } else {
                (ptr)->versions = new_version((ptr)->versions, info);
				free(new->versions->info);
				free(new->versions);
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

void print_all_versions(List *versions){
    List *ptr = versions;
    printf("Info: ");
    while(ptr->next != NULL){
        printf("v%d -%s; ", ptr->release, ptr->info);
        ptr = ptr->next;
    }
    printf("v%d -%s\n", ptr->release, ptr->info);
}

int print_tree(Node *ptr){
    if(ptr == NULL)
        return 0;
    printf("Key: %s\n", ptr->key);
    print_all_versions(ptr->versions);
    print_tree(ptr->left);
    print_tree(ptr->right);
    return 0;
}

Node *search_elem(Node *ptr, char *key){
    Node *search = NULL;
    while(ptr != NULL && search == NULL){
        if(strcmp(key, ptr->key) < 0)
            ptr = ptr->left;
        else if(strcmp(key, ptr->key) > 0)
            ptr = ptr->right;
        else
            search = ptr;
    }
    return search;
}

Node *search_elem_par(Node *ptr, char *key){
    Node *search = search_elem(ptr, key), *par = NULL;
    while(ptr != NULL && search != NULL){
        if(strcmp(key, ptr->key) < 0) {
            par = ptr;
            ptr = ptr->left;
        }
        else if(strcmp(key, ptr->key) > 0) {
            par = ptr;
            ptr = ptr->right;
        }
        else
            search = NULL;
    }
    return par;
}

Node * search_nearest_next(Node *root, char *key){
    Node *ptr = root, *next = NULL;
    while(ptr != NULL){
        if(strcmp(key, ptr->key) < 0){
            next = ptr;
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
    }
    return next;
}

Node * search_nearest_prev(Node *root, char *key){
    Node *ptr = root, *prev = NULL;
    while(ptr != NULL){
        if(strcmp(key, ptr->key) > 0){
            prev = ptr;
            ptr = ptr->right;
        }
        else{
            ptr = ptr->left;
        }
    }
    return prev;
}

void delete_list(List *head){
    List *ptr = head, *del;
    while (ptr->next != NULL) {
        free(ptr->next->info);
        del = ptr->next;
        ptr->next = ptr->next->next;
        free(del);
    }
    free(ptr->info);
	del = ptr;
	head = NULL;
    free(del);
}

void delete_last_list(List *head){
    List *ptr = head, *del = head;
    while (del->next != NULL) {
        ptr = del;
        del = del->next;
    }
    ptr->next = del->next;
    free(del->info);
    free(del);
}

void delete_elem(Node **root, char *key){
    Node *par = search_elem_par(*root, key);
    Node *delete = search_elem(*root, key);
    Node *next, *par_next;
    if(delete == NULL)
        printf("This element not found\n");
    else if(delete->versions->next != NULL){
        delete_last_list(delete->versions);
        printf("First version deleted\n");
    }
    else{
        if(delete->left == NULL && delete->right == NULL){
            if(par != NULL) {
                if (par->left == delete) {
                    par->left = NULL;
                } else if (par->right == delete) {
                    par->right = NULL;
                }
            }
            delete_list(delete->versions);
            free(delete);
            if(par == NULL)
                *root = NULL;
        }
        else if(delete->left == NULL || delete->right == NULL){
            if(delete->left == NULL){
                if(par != NULL) {
                    if (par->left == delete) {
                        par->left = delete->right;

                    } else if (par->right == delete) {
                        par->right = delete->right;
                    }
                }
                else{
                    *root = delete->right;
                }
                delete_list(delete->versions);
                free(delete);
            }
            else{
                if(par != NULL) {
                    if (par->left == delete) {
                        par->left = delete->left;
                    } else if (par->right == delete) {
                        par->right = delete->left;
                    }
                }
                else
                    *root = delete->left;
                delete_list(delete->versions);
                free(delete);
            }
        }
        else{
            next = search_nearest_next(*root, key);
            par_next = search_elem_par(*root, next->key);
            memcpy(delete->key, next->key, strlen(next->key));
            delete_list(delete->versions);
            delete->versions = next->versions;
            if(par_next->left == next)
                par_next->left = next->right;
            else
                par_next->right = next->right;
            //delete_list(next->versions);
            free(next);
        }
        printf("Element deleted\n");
    }
}

int delete_tree(Node *ptr){
    if(ptr == NULL)
        return 0;
    delete_tree(ptr->left);
    delete_tree(ptr->right);
    delete_list(ptr->versions);
    free(ptr);
    return 0;
}

int loading(Node **root){
    FILE *input;
    char key[31], info[1000];
    input = fopen("input.txt", "r");
    if(input == NULL)
        return -1;
    else{
        while(!feof(input)){
            fscanf(input, "%s\n", key);
            fscanf(input, "%s\n", info);
            add_elem(root, key, info);
        }
    }
    fclose(input);
    return 0;
}

int print_beaty_tree(Node *ptr, int probel){
    if(ptr == NULL)
        return 0;
    print_beaty_tree(ptr->right, probel + 1);
    for(int i=0; i<probel;i++, printf("  "));
    printf("%s\n", ptr->key);
    print_beaty_tree(ptr->left, probel + 1);
    return 0;
}

Node *create_new(){
    Node *node;
    node = (Node *) calloc(1, sizeof(Node));
    return node;
}
