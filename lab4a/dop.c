#include <stdio.h>
#include "func_dop.h"

char *processing_word(char * str){
    int i = 0;
    while(str[i] != '\0'){
        if(str[i] < 90 && str[i] >64)
            str[i] += 32;
        if(str[i] == ',' || str[i] == '.' || str[i] == ':' || str[i] == ';' || str[i] == '!' || str[i] == '?')
            str[i] = '\0';
        i++;
    }
    return str;
}

int main(){
    FILE *input, *output = fopen("output.txt", "wa");
    Node *root = NULL;
    char str[100];
    if(!(input = fopen("input1.txt", "r")))
        printf("Error\n");
    else{
        while(!feof(input)) {
            fscanf(input, "%s", str);
			fscanf(input, "%*c");
            add_elem(&root, processing_word(str));
        }
        load_tree(root, output);
        delete_tree(root);
    }
    fclose(output);
    fclose(input);
    return 0;
}


