#include "./generic-linked-lists.h"
#include "./htree-node.h"

glist_t *create_chars_freq_list(char *file_name);
glist_t *create_huffman_tree(glist_t *chars_freq_list);

glist_t *create_chars_binary_path_list(tree_t *huffman_tree);
void create_chars_binary_path_list_rec(tree_t *root, glist_t **pbinary_paths_list, char *curr_path);
void hcompress_file(glist_t *chars_binary_path_list, char * text_file,char *bin_filename);
void hdecompress_file(tree_t *huffman_tree, char *text_filename);

/** HELPERS*/

int tree_node_cmp(tree_t *first, tree_t *second);
void tree_node_printer(tree_t *node);
int freq_node_cmp(tree_t *first, tree_t *second);
void swap_tree_nodes(glist_t *first, glist_t *second);
