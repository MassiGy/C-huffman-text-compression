#include "../headers/hcompress.h"

glist_t *create_chars_freq_list(char *file_name)
{
    FILE *_file_ptr_one = fopen(file_name, "rt");
    assert(_file_ptr_one != NULL);

    // create the list
    glist_t *freq_list = NULL;

    int char_freq;
    char charac;

    while (!feof(_file_ptr_one))
    {
        
        fscanf(_file_ptr_one, "%c", &charac);

        char_freq = 1;
        tree_t *char_node = create_node(char_freq, charac);
        assert(char_node != NULL);

        // if it is already on the list, skip and go to the next character
        bool already_in_list = searchIn_glist(&freq_list, char_node, &tree_node_cmp);
        printf("already in list ? %s\n", already_in_list ? "true" : "false");
      
        if (already_in_list)
        {
            free(char_node);
            char_node = NULL;
            continue;
        }
        // if it is not on the list, then it is a new character,
        // so, go through the file and record its frequency
        char temp;
        FILE *_file_ptr_two = fopen(file_name, "rt");

        while (!feof(_file_ptr_two)) // the base pointer is already moved
        {
            fscanf(_file_ptr_two, "%c", &temp);
            if (temp == charac)
                char_freq++;
        }
        fclose(_file_ptr_two);



        // now that we have the charac and its freq, insert a new node to the list containing that
        push_glist(&freq_list, create_node(char_freq, charac), sizeof(tree_t));
    }

    fclose(_file_ptr_one);

    return freq_list;
}

tree_t *create_huffman_tree(glist_t *chars_freq_list);

glist_t *create_chars_binary_path_list(tree_t *huffman_tree);
void hcompress_file(glist_t *chars_binary_path_list, char *bin_filename);
void hdecompress_file(tree_t *huffman_tree, char *text_filename);

/** HELPERS*/

int tree_node_cmp(tree_t *first, tree_t *second)
{
    assert(first != NULL);
    assert(second != NULL);
    printf("%c\t%c\n", first->val, second->val);
  
  
    return (strcmp(&(first->val), &(second->val)));
}

void tree_node_printer(tree_t *node)
{
    assert(node != NULL);

    printf("@node : charc: %c, freq: %i \n", node->val, node->freq);
}