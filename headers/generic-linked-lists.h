#include "./sys_headers.h"

struct Node
{
    void *data;
    size_t data_size;
    struct Node *next;
};

typedef struct Node glist_t;

/** CRUD OPERATIONS */
void push_glist(glist_t **head, void *val, size_t val_size);
void print_glist(glist_t **head, void (*printer)(void *data));
void updateAt(glist_t **head, int pos, void *val, size_t val_size);
bool searchIn_glist(glist_t **head, void *data, int (*cmp)(void *first, void *second));
void destroy_glist(glist_t **head);

/** COPY OPERATIONS */
glist_t *copy_glist(glist_t *head);

/** SWAP OPERATIONS */
void swap_glist(glist_t **head, int first_pos, int second_pos);

/** SORTING OPERATIONS */
void bubble_sort_glist(glist_t **head, int length, int (*cmp)(void *first, void *second), void (*swap)(glist_t *first, glist_t *second));

/** HELPERS */
void swap_glist_str(glist_t *first, glist_t *second);
void print_str(char *data);

/** TO DEBUG*/
// void copy_glist(glist_t **dest, glist_t **src); // does not work
