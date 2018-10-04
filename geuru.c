#include "geuru.h"
#include <stdio.h>

int main() {
    G_ATOM_LIST* list = atom_list_create();
    
    for(size_t i = 0; i < 10; i++) {
        atom_list_push_same(list, atom_of_int(i * i));
    }
    
    for(size_t i = 0; i < list->size; i++) {
        char* str = atom_str(list->memory[i]);
        printf("%s\n", str);
        free(str);
    }
}