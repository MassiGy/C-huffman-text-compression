#include "../headers/htree-node.h"

tree_t *create_node(int freq, char data)
{
    tree_t *res = malloc(sizeof(tree_t));
    assert(res != NULL);

    res->freq = freq;
    res->val = data;

    return res;
}

bool isleaf(tree_t *node)
{
    assert(node != NULL);
    return (node->left == NULL && node->right == NULL);
}

void destroy_tree(tree_t **proot)
{
    assert(proot != NULL);
    assert(*proot != NULL);

    tree_t *root = *proot;

    if (isleaf(root))
    {
        free(root);
        root = NULL;
        return;
    }

    destroy_tree(&(root->left));
    destroy_tree(&(root->right));
   
    free(root);
    root = NULL;
    return;
}