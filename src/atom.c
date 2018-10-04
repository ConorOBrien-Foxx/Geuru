#include "atom.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

G_ATOM* atom_create(G_ATOM_TYPE type) {
    G_ATOM* ret = malloc(sizeof(G_ATOM));
    ret->type = type;
    
    return ret;
}


G_ATOM* atom_of_int(int64_t i) {
    G_ATOM* res = atom_create(GAT_INT);
    res->value.int_value = i;
    return res;
}
G_ATOM* atom_of_char(char c) {
    G_ATOM* res = atom_create(GAT_CHAR);
    res->value.char_value = c;
    return res;
}
G_ATOM* atom_of_double(double d) {
    G_ATOM* res = atom_create(GAT_DOUBLE);
    res->value.double_value = d;
    return res;
}
// G_ATOM* atom_of_class(G_CLASS);
G_ATOM* atom_of_list(G_ATOM_LIST* l) {
    G_ATOM* res = atom_create(GAT_LIST);
    res->value.list_value = l;
    return res;
}


#define GC_SIZE_MAX (80)

char* atom_str(G_ATOM* atom) {
    char* buf = malloc(sizeof(char) * GC_SIZE_MAX);
    size_t count = 0;
    
    
    switch(atom->type) {
        case GAT_INT:
            count = sprintf(buf, "%"PRId64, atom->value.int_value);
            break;
        default:
            count = sprintf(buf, "%s", "(no repr)");
            break;
    }
    
    buf[count] = 0;
    
    return buf;
}

G_ATOM* atom_dup(G_ATOM* source) {
    G_ATOM* res = atom_create(source->type);
    switch(source->type) {
        case GAT_INT:
            res->value.int_value = source->value.int_value;
            break;
        
        case GAT_CHAR:
            res->value.char_value = source->value.char_value;
            break;
        
        case GAT_DOUBLE:
            res->value.double_value = source->value.double_value;
            break;
        
        // case GAT_CLASS:
            // break;
        
        // case GAT_LIST:
            // break;
        
        default:
            fprintf(stderr, "Unhandled %i in atom_dup (line %i)",
                source->type,
                __LINE__
            );
            break;
    }
    return res;
}


#define GC_INITIAL_CAP      (16)
#define GC_ATOM_SIZEOF      (sizeof(G_ATOM*))
G_ATOM_LIST* atom_list_create() {
    G_ATOM_LIST* res = malloc(sizeof(G_ATOM_LIST));
    
    res->capacity = GC_INITIAL_CAP;
    res->size = 0;
    res->memory = malloc(GC_ATOM_SIZEOF * res->capacity);
    
    return res;
}

void atom_list_resize(G_ATOM_LIST* list) {
    void* tmp = realloc(list->memory, GC_ATOM_SIZEOF * list->capacity);
    if(tmp == NULL) {
        fprintf(stderr, "Ran out of memory while trying to grow an atom_list.");
    }
    else {
        list->memory = tmp;
    }
}

#define GC_GROW_FACTOR  (2)
void atom_list_grow(G_ATOM_LIST* list) {
    list->capacity *= GC_GROW_FACTOR;
    atom_list_resize(list);
}

size_t atom_list_push_same(G_ATOM_LIST* list, G_ATOM* element) {
    list->memory[list->size++] = element;
    
    if(list->size >= list->capacity)
        atom_list_grow(list);
    
    return list->size;
}
size_t atom_list_push(G_ATOM_LIST* list, G_ATOM* element) {
    return atom_list_push_same(list, atom_dup(element));
}

