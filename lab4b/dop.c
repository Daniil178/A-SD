#include <stdio.h>
#include <stdlib.h>
#include "func_4b_dop.h"

const char *MSGS[] = {"0. Quit", "1. Write to file", "2. Print from file",
                      "3. Just function"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c;
    int key, offset;
    FILE *input;
    Node *root = NULL;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch (c) {
            case 0://Quit
                break;
            case 1:
                input = fopen("input.bin", "w+b");
                do{
                    scanf("%d", &key);
                    fwrite(&key, sizeof(int), 1, input);
                }while(getchar() != '\n');
                fclose(input);
                break;
            case 2:
                input = fopen("input.bin", "r+b");
                do{
                    fread(&key, sizeof(int), 1, input);
                    if(!feof(input))
                        printf("%d ", key);
                }while(!feof(input));
                fclose(input);
                break;
            case 3:
                input = fopen("input.bin", "r+b");
                Node *root = NULL;
                do{
                    offset = ftell(input);
                    fread(&key, sizeof(int), 1, input);
                    if(!feof(input))
                        add_elem(&root, key, offset);
                }while(!feof(input));
                print_tree(root);
                delete_tree(root);
                fclose(input);
                break;
        }
    } while (c != 0);
    return 0;
}
