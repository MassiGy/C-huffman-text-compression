#include "../headers/main.h"

int main(void)
{
    glist_t *freq_list = create_chars_freq_list("../ressources/init_text.txt");
    assert(freq_list != NULL);

    bubble_sort_glist(&freq_list, get_length_glist(freq_list), &freq_node_cmp, &swap_tree_nodes);
    print_glist(&freq_list, &tree_node_printer);

    glist_t *root = create_huffman_tree(freq_list);

    printf("#########################\n");

    print_inorder_tree(root->data, &tree_node_printer);
   
   
    printf("#########################\n");

  

    destroy_glist(&freq_list);

    return 0;
}