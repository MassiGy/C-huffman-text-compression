#include "../headers/generic-linked-lists.h"

void push_glist(glist_t **head, void *val, size_t val_size)
{
    assert(head != NULL);

    if (*head == NULL)
    {
        *head = malloc(sizeof(glist_t));
        assert(*head != NULL);

        (*head)->data = malloc(val_size * sizeof(char));
        assert((*head)->data != NULL);

        memcpy((*head)->data, val, val_size);

        (*head)->data_size = val_size;
        (*head)->next = NULL;
    }
    else
    {
        glist_t *temp = *head;

        while (temp->next != NULL)
        {
            /* code */
            temp = temp->next;
        }

        temp->next = malloc(sizeof(glist_t));
        assert(temp->next != NULL);

        temp = temp->next;

        temp->data = malloc(val_size * sizeof(char));
        assert(temp->data != NULL);

        memcpy(temp->data, val, val_size);

        temp->data_size = val_size;
        temp->next = NULL;
    }
}

void print_glist(glist_t **head, void (*printer)(void *data))
{
    assert(head != NULL);
    if (*head == NULL)
        return;

    glist_t *traversal = *head;

    while (traversal != NULL)
    {
        (*printer)(traversal->data);
        traversal = traversal->next;
    }
}

void destroy_glist(glist_t **head)
{
    assert(head != NULL);
    assert(*head != NULL);

    glist_t *temp = (*head);

    while (temp->next != NULL)
    {
        // point to the next element starting from the head
        temp = temp->next;

        // free the head node
        free((*head)->data);
        free(*head);

        // make the head point to its next
        *head = temp;
    }

    free((*head)->data);
    free(*head);

    // set pointers to null to avoid illegal derefrenciations
    *head = NULL;
    temp = NULL;
}

bool searchIn_glist(glist_t **head, void *data, int (*cmp)(void *first, void *second))
{
    assert(head != NULL);
    assert(*head != NULL);

    glist_t *traversal = *head;

    while (traversal != NULL)
    {
        // compare the elements
        if ((*cmp)(traversal->data, data) == 0)
        {
            return true;
        }
        // increment the traversal
        traversal = traversal->next;
    }
    return false;
}

glist_t *copy_glist(glist_t *head)
{
    assert(head != NULL);

    glist_t *resault;
    glist_t *traversal = head;

    // create the resault copy with one more element at the beginning
    glist_t *current = malloc(sizeof(glist_t));
    assert(current != NULL);

    // make resault points to this first element;
    resault = current;

    while (traversal != NULL)
    {
        /* code */
        current->next = malloc(sizeof(glist_t));
        assert(current->next != NULL);

        current = current->next;

        current->data = malloc(traversal->data_size * sizeof(char));
        assert(current->data != NULL);

        memcpy(current->data, traversal->data, traversal->data_size);

        current->data_size = traversal->data_size;

        traversal = traversal->next;
    }

    // remove the first element;

    current = resault->next;
    free(resault); // WARNING: we do not free the resault->data since we've never allocated it.
    resault = current;

    return resault;
}

void updateAt(glist_t **head, int pos, void *val, size_t val_size)
{
    assert(head != NULL);
    assert(*head != NULL);
    assert(pos >= 0);

    if (pos == -1)
    {
        // insert at the beginning
        glist_t *temp = malloc(sizeof(glist_t));
        assert(temp != NULL);

        temp->data_size = val_size;

        temp->data = malloc(val_size * sizeof(char));
        assert(temp->data != NULL);

        memcpy(temp->data, val, val_size);

        temp->next = *head;

        *head = temp;

        return;
    }

    int counter = 0;
    glist_t *traversal = *head;

    while (counter < pos && traversal->next != NULL)
    {
        /* code */
        traversal = traversal->next;
        counter++;
    }

    // if pos < length
    if (counter == pos)
    {

        // free the old data;
        free(traversal->data);

        // create the new data container
        traversal->data = malloc(val_size * sizeof(char));
        assert(traversal->data != NULL);

        traversal->data_size = val_size;

        memcpy(traversal->data, val, val_size);

        return;
    }

    // if pos > length
    if (traversal->next == NULL && counter != pos)
    {

        traversal->next = malloc(sizeof(glist_t));
        assert(traversal->next != NULL);

        traversal = traversal->next;

        traversal->data_size = val_size;

        traversal->data = malloc(val_size * sizeof(char));
        assert(traversal->data != NULL);

        memcpy(traversal->data, val, val_size);

        traversal->next = NULL;

        return;
    }
}

void swap_glist(glist_t **head, int first_pos, int second_pos)
{
    assert(head != NULL);
    assert(*head != NULL);

    assert(first_pos >= 0);
    assert(second_pos >= 0);
    assert(first_pos < second_pos);

    glist_t *traversal = *head;
    glist_t *first;
    glist_t *second;
    int counter = 0;

    while (counter < second_pos && traversal != NULL)
    {
        /* code */
        if (counter == first_pos)
        {
            first = traversal;
        }
        counter++;
        traversal = traversal->next;
    }

    // assert that second pos < len, cuz if second pos > len there is no element to swap
    assert(traversal != NULL);

    // now counter == second pos
    second = traversal;

    // swap them;

    // temp will store the data of the second
    glist_t *temp = malloc(sizeof(glist_t));
    assert(temp != NULL);

    temp->data_size = second->data_size;

    temp->data = malloc(second->data_size * sizeof(char));
    assert(temp->data != NULL);

    memcpy(temp->data, second->data, second->data_size);

    // copy the data of the first to the second;

    free(second->data); // destroy the old data;

    second->data_size = first->data_size;

    second->data = malloc(first->data_size * sizeof(char));
    assert(second->data != NULL);

    memcpy(second->data, first->data, first->data_size);

    // copy the data from temp to first;

    free(first->data); // destroy old data;

    first->data_size = temp->data_size;

    first->data = malloc(temp->data_size * sizeof(char));
    assert(first->data != NULL);

    memcpy(first->data, temp->data, temp->data_size);

    // destroy temp;
    free(temp->data);
    free(temp);

    return;
}

void bubble_sort_glist(glist_t **head, int length, int (*cmp)(void *first, void *second), void (*swap)(glist_t *first, glist_t *second))
{
    assert(head != NULL);
    assert(*head != NULL);
    assert(length > 0);
    assert(cmp != NULL);
    assert(swap != NULL);

    int i = 0;
    glist_t *swap_pointer;
    bool swaps = true;

    while (i < length - 1 && swaps)
    {

        swaps = false;
        int j = 0;
        swap_pointer = *head;

        while (j < length - i - 1 && swap_pointer->next != NULL)
        {
            if ((*cmp)(swap_pointer->data, swap_pointer->next->data) > 0)
            {
                (*swap)(swap_pointer, swap_pointer->next);
                swaps = true;
            }
            swap_pointer = swap_pointer->next;
            j++;
        }
        i++;
    }
}

/** HELPERS */

/*
    This will swap two nodes of the generic linked list
    assuming that they contain strings pointers as data
*/
void swap_glist_str(glist_t *first, glist_t *second)
{
    assert(first != NULL);
    assert(second != NULL);

    // we know that first->data and second->data are char *

    // store the second data
    char buffer[second->data_size];
    strcpy(buffer, (char *)second->data);

    // copy first to second
    free(second->data);

    second->data_size = first->data_size;

    second->data = malloc(first->data_size * sizeof(char));
    assert(second->data != NULL);

    strcpy((char *)second->data, (char *)first->data); // this will copy logically, copies till the \0

    // copy the buffer to the first
    free(first->data);

    first->data_size = strlen(buffer) + 1; // strlen gives the logical length of buffer and it does not count \0

    first->data = malloc((strlen(buffer) + 1) * sizeof(char));
    assert(first->data != NULL);

    strcpy(first->data, buffer);

    ((char *)first->data)[strlen(buffer)] = '\0';
}

void print_str(char *data)
{
    assert(data != NULL);

    printf("%s\n", data);
}

/** TO DEBUG*/

/*

void copy_glist(glist_t **dest, glist_t **src)
{
    assert(src != NULL);
    assert(*src != NULL);

    assert(dest != NULL);

    glist_t *traversal = *src;
    glist_t *current = *dest;

    if (current == NULL)
    {
        current = malloc(sizeof(glist_t));

        current->data = traversal->data;
        current->data_size = traversal->data_size;

        memcpy(current->data, traversal->data, traversal->data_size);

        current->next = NULL;

        traversal = traversal->next;
    }

    while (traversal != NULL)
    {
        current->next = malloc(sizeof(glist_t));

        current->next->data = traversal->data;
        current->next->data_size = traversal->data_size;

        memcpy(current->next->data, traversal->data, traversal->data_size);

        current->next->next = NULL;

        current = current->next;
        traversal = traversal->next;
    }
}
*/