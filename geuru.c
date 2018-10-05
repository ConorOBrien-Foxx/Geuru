#include "geuru.h"
#include <stdio.h>

int main() {
    G_ATOM_LIST* list = atom_list_create();
    
    for(size_t i = 0; i < 10; i++) {
        atom_list_push_same(list, atom_of_int(i * i));
    }
    
    G_ATOM* tail = atom_list_pop(list);
    
    atom_print(tail);
}