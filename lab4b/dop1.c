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
                delete_tree(root);
                break;
            case 1:
                input = fopen("input.bin", "wb");
                while(scanf("%d", &key) > 0){
                    fwrite(&key, sizeof(int), 1, input);
                }
                fclose(input);
                break;
            case 2:
                input = fopen("input.bin", "rb");
                while(!feof(input)){
                    fread(&key, sizeof(int), 1, input);
                    printf("%d ", key);
                }
                fclose(input);
                break;
            case 3:
                input = fopen("input.bin", "rb");
                while(!feof(input)){
                    offset = ftell(input);
                    fread(&key, sizeof(int), 1, input);
                    add_elem(&root, key, offset);
                }
                print_tree(root);
                fclose(input);
                break;
        }
    } while (c != 0);
    return 0;
}
