#ifndef GEURU_INCL_ATOM
#define GEURU_INCL_ATOM
#include <stdint.h>
#include <stdlib.h>

typedef union G_ATOM_VALUE {
    int64_t             int_value;
    char                char_value;
    double              double_value;
    // G_CLASS          class_value;
    struct G_ATOM_LIST* list_value;
} G_ATOM_VALUE;

typedef enum G_ATOM_TYPE {
    GAT_INT,
    GAT_CHAR,
    GAT_DOUBLE,
    // GAT_CLASS,
    GAT_LIST,
} G_ATOM_TYPE;

typedef struct G_ATOM {
    G_ATOM_VALUE    value;
    G_ATOM_TYPE     type;
} G_ATOM;

typedef struct G_ATOM_LIST {
    G_ATOM**    memory;
    size_t      capacity;
    size_t      size;
} G_ATOM_LIST;

//------- G_ATOM
G_ATOM*         atom_create     (G_ATOM_TYPE);
G_ATOM*         atom_of_int     (int64_t);
G_ATOM*         atom_of_char    (char);
G_ATOM*         atom_of_double  (double);
// G_ATOM*         atom_of_class   (G_CLASS);
G_ATOM*         atom_of_list    (G_ATOM_LIST*);
char*           atom_str        (G_ATOM*);
G_ATOM*         atom_dup        (G_ATOM*);
void            atom_print      (G_ATOM*);

//------- G_ATOM_LIST
G_ATOM_LIST*    atom_list_create    ();
void            atom_list_grow      (G_ATOM_LIST*);
void            atom_list_resize    (G_ATOM_LIST*);
size_t          atom_list_push      (G_ATOM_LIST*, G_ATOM*);
size_t          atom_list_push_same (G_ATOM_LIST*, G_ATOM*);
G_ATOM*         atom_list_pop       (G_ATOM_LIST*);

#endif