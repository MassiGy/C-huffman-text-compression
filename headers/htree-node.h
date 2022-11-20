#include "./sys_headers.h"

struct node
{
    int freq;
    char binary_path[32]; // this is an over estimate, but it is like this to minimize pointer overhead
    char val;
    struct node *left;
    struct node *right;
};

typedef struct node tree_t;

tree_t *create_node(int freq, char data);
bool isleaf(tree_t *node);
void print_inorder_tree(tree_t *root, void (*printer)(tree_t *tree_node));
void destroy_tree(tree_t **proot);