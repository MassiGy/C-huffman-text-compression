#include "../headers/main.h"

int main(void)
{
    // creating the freq list
    glist_t *freq_list = create_chars_freq_list("../ressources/init_text.txt");
    assert(freq_list != NULL);

    // sorting the list
    bubble_sort_glist(&freq_list, get_length_glist(freq_list), &freq_node_cmp, &swap_tree_nodes);
    // print_glist(&freq_list, &tree_node_printer);

    // creating the huffman tree
    glist_t *root = create_huffman_tree(freq_list);
    // print_inorder_tree(root->data, &tree_node_printer);

    // finding every character binary based in-tree location
    glist_t *binary_paths_list = create_chars_binary_path_list(root->data);
    // print_glist(&binary_paths_list, &tree_node_printer);

    // compressing the file
    hcompress_file(binary_paths_list, "../ressources/init_text.txt", "../ressources/compressed.bin");
    printf("\nLOG: File ../ressources/init_text.txt compressed. \nOutput: File ../ressources/compressed.bin \n");
    // decompressing the file
    hdecompress_file(root->data, binary_paths_list, "../ressources/compressed.bin", "../ressources/decompressed_file_text.txt");
    printf("\nLOG: File ../ressources/compressed.bin decompressed. \nOutput: File ../ressources/decompressed_file_text.txt \n\n");


    // CAUTION: since, our tree is created within our list,
    // destroying the list will also destroy the tree.
    destroy_glist(&binary_paths_list);
    destroy_glist(&freq_list);
    free(root->data);
    free(root);
    root = NULL;

    return 0;
}