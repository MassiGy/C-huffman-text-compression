#include "../headers/htree-node.h"

tree_t *create_node(int freq, char data)
{
    tree_t *res = malloc(sizeof(tree_t));
    assert(res != NULL);

    res->freq = freq;
    res->val = data;
    // res->binary_path[0] = "\0"; // no need to do this

    res->left = NULL;
    res->right = NULL;

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

void print_inorder_tree(tree_t *root, void (*printer)(tree_t *tree_node))
{
    assert(root != NULL);

    if (isleaf(root))
    {
        (*printer)(root);
        return;
    }

    print_inorder_tree(root->left, printer);
    print_inorder_tree(root->right, printer);
    (*printer)(root);
    return;
}