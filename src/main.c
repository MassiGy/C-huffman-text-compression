#include "../headers/main.h"



int main(void)
{   
    glist_t *freq_list = create_chars_freq_list("../ressources/init_text.txt");
    assert(freq_list != NULL);
    

    // print_glist(&freq_list,&tree_node_printer);

    destroy_glist(&freq_list);


    return 0;
}