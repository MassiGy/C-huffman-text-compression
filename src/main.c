#include "../headers/main.h"

int main(void)
{
    glist_t *freq_list = create_chars_freq_list("../ressources/init_text.txt");
    assert(freq_list != NULL);

    bubble_sort_glist(&freq_list, get_length_glist(freq_list), &freq_node_cmp, &swap_tree_nodes);
    // print_glist(&freq_list, &tree_node_printer);

    // printf("#########################\n");

    glist_t *root = create_huffman_tree(freq_list);
    // print_inorder_tree(root->data, &tree_node_printer);

    // printf("#########################\n");

    glist_t *binary_paths_list = create_chars_binary_path_list(root->data);
    // print_glist(&binary_paths_list, &tree_node_printer);
    // printf("#########################\n");

    printf("#########################\n");

    hcompress_file(binary_paths_list,"../ressources/init_text.txt", "../ressources/compressed.bin");
    printf("#########################\n");





    // CAUTION: since, our tree is created within our list,
    // destroying the list will also destroy the tree.
    destroy_glist(&freq_list);
    free(root->data);
    free(root);
    root = NULL;
    destroy_glist(&binary_paths_list);



    return 0;
}