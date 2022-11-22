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
        bool already_in_list = (searchIn_glist(&freq_list, char_node, &tree_node_cmp) != NULL);

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

/**
 * NOTE: this algorithm is created in such a way that our tree will be formed
 * via dependencies between the list nodes, basically every node of our list will
 * have pointers to other nodes in such a manner that the resault is a binary tree.
 *
 * CAUTION: as a resault of this impelementation, destroying the list will also destroy
 * the tree, but the other way around is not true, since, our list is the formal holder of
 * our tree.
 *
 */

glist_t *create_huffman_tree(glist_t *chars_freq_list)
{
    assert(chars_freq_list != NULL);

    // since our list is sorted on the asc order.
    // we will start creating our huffman tree from the first to buttom nodes of the list

    glist_t *traversal = chars_freq_list;
    tree_t *first = NULL;
    tree_t *second = NULL;
    tree_t *local_root = NULL;
    glist_t *el_to_insert = NULL;

    while (traversal->next != NULL)
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
        if (traversal == NULL)
        {
            traversal = malloc(sizeof(glist_t));
            assert(traversal != NULL);

            traversal->data = local_root;
            traversal->data_size = sizeof(tree_t);
            traversal->next = NULL;

            break;
        }
        // else, insert at the right pos
        glist_t *walker = traversal;

        while (walker->next != NULL && ((tree_t *)(walker->data))->freq < local_root->freq)
        {
            walker = walker->next;
        }

        glist_t *temp = walker->next;

        el_to_insert = malloc(sizeof(glist_t));
        assert(el_to_insert != NULL);

        el_to_insert->data = local_root;
        el_to_insert->data_size = sizeof(tree_t);

        walker->next = el_to_insert;
        el_to_insert->next = temp;
    }

    // at the end, the last position of traversal on the list will be our tree main root.

    return traversal;
}

glist_t *create_chars_binary_path_list(tree_t *huffman_tree)
{
    assert(huffman_tree != NULL);

    glist_t *binary_paths_list = NULL;

    create_chars_binary_path_list_rec(huffman_tree, &binary_paths_list, "\0");

    return binary_paths_list;
}

void create_chars_binary_path_list_rec(tree_t *root, glist_t **pbinary_paths_list, char *curr_path)
{
    assert(pbinary_paths_list != NULL);

    if (isleaf(root))
    {
        tree_t *node = malloc(sizeof(tree_t));
        strcpy(node->binary_path, curr_path);
        node->freq = root->freq;
        node->val = root->val;
        node->left = NULL;
        node->right = NULL;

        push_glist(pbinary_paths_list, node, sizeof(tree_t));

        free(node);
        node = NULL;

        return;
    }

    char left_binary_path[strlen(curr_path) + 1 + 1]; // +1 for the new bit && +1 for the null terminator
    strcpy(left_binary_path, curr_path);
    strcat(left_binary_path, "0");

    char right_binary_path[strlen(curr_path) + 1 + 1];
    strcpy(right_binary_path, curr_path);
    strcat(right_binary_path, "1");

    create_chars_binary_path_list_rec(root->left, pbinary_paths_list, left_binary_path); // consider adding my own strcat
    create_chars_binary_path_list_rec(root->right, pbinary_paths_list, right_binary_path);
}

void hcompress_file(glist_t *chars_binary_path_list, char *text_filename, char *bin_filename)
{
    assert(chars_binary_path_list != NULL);

    // open the txt file
    FILE *_initial_file = fopen(text_filename, "rt");
    assert(_initial_file != NULL);

    // open the bin file
    FILE *_compressed_file = fopen(bin_filename, "wb");
    assert(_compressed_file != NULL);

    // charac will be our current in-txt-file character
    char charac = '\0';
    // char_node will be our tree node that holds charac, used to search in the list
    tree_t *char_node = NULL;
    // list_node will be either a specific in-list node or a traversal node
    glist_t *list_node = NULL;

    // get the total number of binary digits in the compressed file binary representation
    list_node = chars_binary_path_list;
    int total_binary_digits_count = 0;

    while (list_node != NULL)
    {
        // the total = char_freq * char_binary_path to its location in the huffman tree
        total_binary_digits_count += (strlen(((tree_t *)(list_node->data))->binary_path)) * ((tree_t *)(list_node->data))->freq;
        list_node = list_node->next;
    }

    // set an blob of bits containing n bits, where n = total_binary_digits_count
    u_int8_t *bit_feild = malloc(((total_binary_digits_count / 8) + 1) * sizeof(u_int8_t));
    assert(bit_feild != NULL);

    // clear the bits on the allocated blob
    for (int i = 0; i < (total_binary_digits_count / 8); ++i)
        bit_feild[i] = 0;

    // set our base binary wise rigth shift position
    int actual_next_bit_insert_pos = 1;

    while (!feof(_initial_file))
    {
        fscanf(_initial_file, "%c", &charac);

        // find the binary path of the char in the list;
        char_node = create_node(0, charac);

        // search for the current charac binary path
        list_node = searchIn_glist(&chars_binary_path_list, char_node, &tree_node_cmp);
        assert(list_node != NULL);

        free(char_node);

        // get the current charac binary path length
        int size = strlen(((tree_t *)(list_node->data))->binary_path);

        // push from left ( to rigth ) the current charac binary path as bits, using right bit wise shift
        for (int counter = 0; counter < size; ++counter)
        {
            if (((tree_t *)(list_node->data))->binary_path[counter] == '1')
                SET_BIT(*bit_feild, actual_next_bit_insert_pos);
        }

        // make the new bit wise rigth shift go further through the for-bits allocated blob
        actual_next_bit_insert_pos += size;
    }

    // write the for-bits allocated blob into the _compressed_file
    fwrite(bit_feild, sizeof(u_int8_t), (total_binary_digits_count / 8) + 1, _compressed_file);

    // free the blob
    free(bit_feild);

    // close the files
    fclose(_initial_file);
    fclose(_compressed_file);
    return;
}

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

    printf("@node : charc: %c, freq: %i, binary_path: %s \n", node->val, node->freq, node->binary_path);
}

void print_compression_binary_output(glist_t *chars_binary_paths_list)
{
    assert(chars_binary_paths_list != NULL);

    glist_t *traversal = chars_binary_paths_list;
    while (traversal->next != NULL)
    {
        printf("%s", ((tree_t *)(traversal->data))->binary_path);
        traversal = traversal->next;
    }
}