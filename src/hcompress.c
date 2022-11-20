#include "../headers/hcompress.h"

glist_t *create_chars_freq_list(char *file_name)
{
    FILE *_file_ptr_one = fopen(file_name, "rt");
    assert(_file_ptr_one != NULL);

    // create the list
    glist_t *freq_list = NULL;

    // temp structures
    char charac;
    tree_t *char_node;

    while (!feof(_file_ptr_one))
    {

        fscanf(_file_ptr_one, "%c", &charac);

        char_node = create_node(0, charac);
        assert(char_node != NULL);

        // if it is already on the list, skip and go to the next character
        bool already_in_list = searchIn_glist(&freq_list, char_node, &tree_node_cmp);

        if (already_in_list)
        {
            free(char_node);
            char_node = NULL;
            continue;
        }

        // if it is not on the list, then it is a new character,
        // so, go through the file and record its frequency
        char temp;
        FILE *_file_ptr_two = fopen(file_name, "rt"); // open the file in a new stream on the memory

        while (!feof(_file_ptr_two)) // the base pointer is already moved
        {
            fscanf(_file_ptr_two, "%c", &temp);
            if (temp == charac)
                char_node->freq++;
        }
        fclose(_file_ptr_two);

        // now that we have the charac and its freq, insert a new node to the list containing that
        push_glist(&freq_list, char_node, sizeof(tree_t));
        free(char_node);
        char_node = NULL;
    }

    fclose(_file_ptr_one);

    return freq_list;
}

glist_t *create_huffman_tree(glist_t *chars_freq_list)
{
    assert(chars_freq_list != NULL);

    // since our list is sorted on the asc order.
    // we will start creating our huffman tree from the first to buttom nodes of the list

    glist_t *traversal = chars_freq_list;
    tree_t *first;
    tree_t *second;
    tree_t *local_root;

    while (traversal->next->next != NULL)
    {

       
        first = traversal->data;
        second = traversal->next->data;

      

        // set traversal to the rest of the list
        traversal = traversal->next->next;

        // now, for the first time, we will set the left and the right
        local_root = create_node(first->freq + second->freq, '^'); // ^ is the default char, which is not used in the text

        if (freq_node_cmp(first, second) < 0)
        {
            local_root->left = first;
            local_root->right = second;
        }
        else
        {
            local_root->left = second;
            local_root->right = first;
        }

        // now we need to insert back the local_root to the list

        // if there is no list left, insert as the unique element.
        if (traversal->next == NULL)
        {
            traversal->next = malloc(sizeof(glist_t));
            assert(traversal->next != NULL);

            traversal->next->data = local_root;
            traversal->next->data_size = sizeof(tree_t);
            traversal->next->next = NULL;

            break;
        }
        // else, insert at the right pos
        glist_t *walker = traversal;

        while (walker->next != NULL && ((tree_t *)(walker->data))->freq < local_root->freq)
        {
            walker = walker->next;
        }

        glist_t *temp = walker->next;

        glist_t *el_to_insert = malloc(sizeof(glist_t));
        assert(el_to_insert != NULL);

        el_to_insert->data = local_root;
        el_to_insert->data_size = sizeof(tree_t);

        walker->next = el_to_insert;
        el_to_insert->next = temp;
    }

    // at the end, the last position of traversal on the list will be our tree main root.
    return traversal;
}

glist_t *create_chars_binary_path_list(tree_t *huffman_tree);
void hcompress_file(glist_t *chars_binary_path_list, char *bin_filename);
void hdecompress_file(tree_t *huffman_tree, char *text_filename);

/** HELPERS*/

int freq_node_cmp(tree_t *first, tree_t *second)
{
    return first->freq - second->freq;
}

void swap_tree_nodes(glist_t *first, glist_t *second)
{
    // since data points to the tree_t * that should be swapped,
    // and since the data_size is always equal to sizeof(tree_t)
    // we just need to swap the pointers

    void *temp = first->data;
    first->data = second->data;
    second->data = temp;
}

int tree_node_cmp(tree_t *first, tree_t *second)
{
    assert(first != NULL);
    assert(second != NULL);
    if ((first->val == second->val))
        return 0;
    else
        return -1;
}

void tree_node_printer(tree_t *node)
{
    assert(node != NULL);

    printf("@node : charc: %c, freq: %i \n", node->val, node->freq);
}