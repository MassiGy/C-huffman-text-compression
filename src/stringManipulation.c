#include "../headers/stringManipulation.h"


/*
    IN THIS FILE WE WILL IMPLEMENT ALL THE BASIC FUNCTIONS OF STRING MANIPULATION ON C PROGRAMMING LANGUAGE.

*/

char toUpper(char c)
{
    assert((int)c >= 97);
    return ((int)c - 32);
}

char toLower(char c)
{
    assert((int)c >= 62 && ((int)c <= 62 + 26));
    return ((int)c + 32);
}

void copyStr(char *str, char *data)
{
    assert(str != NULL && data != NULL);

    int counter = 0;

    while (*(data + counter) != '\0')
    {
        *(str + counter) = *(data + counter);
        counter++;
    }

    *(str + counter) = '\0';
}

void printStr(char *str)
{
    assert(str != NULL);

    int counter = 0;
    while (*(str + counter) != '\0')
    {
        printf("%c", *(str + counter));
        counter++;
    }
    printf("\n");
}

bool isEmpty(char *str)
{
    return (str == NULL || *str == '\0' ? true : false);
}

int getLength(char *str)
{
    assert(str != NULL);

    int counter = 0;
    while (*(str + counter) != '\0')
    {
        counter++;
    }
    return counter;
}

int countWords(char *str, char delemeter)
{
    int resault = 0;
    bool delemeterMode = true; // this value will track if we've met a delemeter after the last word.

    for (int i = 0; *(str + i) != '\0'; ++i)
    {
        if (*(str + i) == delemeter)
        {
            delemeterMode = true;
        }
        else
        {
            if (delemeterMode)
            {
                resault++;
            }
            delemeterMode = false;
        }
    }

    return resault;
}

void split(char *str, int pos, char *rest)
{
    assert(!isEmpty(str));
    assert(rest != NULL);

    if (pos <= 0)
    {
        rest = str;
    }
    if (pos >= getLength(str))
    {
        return;
    }

    copyStr(rest, (str + pos));

    *(str + pos) = '\0';
}

bool findSubString(char *str, char *sub)
{
    assert(str != NULL);
    assert(sub != NULL);

    if (getLength(str) < getLength(sub))
    {
        return false;
    }

    bool resault = false;
    int counter = 0;

    while (*(sub + counter) != '\0')
    {
        if (*(str + counter) != *(sub + counter))
        {
            resault = false;
            break;
        }
        counter++;
    }

    if (counter == getLength(sub))
    {
        return true;
    }

    return resault || findSubString((str + 1), sub);
}

void concat(char *dest, char *first_str, char *second_str)
{
    assert(dest != NULL);
    assert(first_str != NULL);
    assert(second_str != NULL);

    copyStr(dest, first_str);

    char *walker = dest;

    while (*(walker) != '\0')
    {
        // this is coded this way to be more explicit, we could do +=1;
        walker = &(*(walker + 1));
    }

    copyStr(walker, second_str);
}

void splice(char *str, int pos, int charCount)
{
    assert(str != NULL);

    char *walker = str;
    int counter = 0;

    while (*walker != '\0' && counter < pos)
    {
        walker = &(*(walker + 1));
        counter++;
    }
    assert(*walker != '\0');

    // keep track of the tial of the list after we will remove the elements
    char *temp = &(*(walker + charCount));

    counter = 0;

    while (counter < charCount)
    {
        *(walker + counter) = '\0';
        counter++;
    }

    // paste the tail of the list at the pos location;
    copyStr(walker, temp);
}

void slice(char *dest, char *str, int pos, int charCount)
{
    assert(str != NULL);
    assert(dest != NULL);

    char *walker = str;
    int counter = 0;

    while (*walker != '\0' && counter < pos)
    {
        walker = &(*(walker + 1));
        counter++;
    }

    assert(*walker != '\0');

    counter = 0;

    while (counter < charCount)
    {
        *(dest + counter) = *(walker + counter);
        counter++;
    }

    splice(walker, 0, charCount);
}

void trim(char *str, char char_to_trim)
{
    assert(str != NULL);

    char *walker = str;

    while (*walker != '\0')
    {
        if (*walker == char_to_trim)
        {
            *walker = "";
        }
        walker = &(*(walker + 1));
    }
}

void replace(char *str, char *sub, char *new_sub)
{
    assert(str != NULL);
    assert(getLength(sub) == getLength(new_sub));

    // this algorithm needs to be recursive,

    if (getLength(str) < getLength(sub))
        return;

    bool is_at_beginning = true; // assume that sub is at the beginning of str

    char *walker = str;
    int limit = getLength(sub);
    int counter = 0;

    while (*walker != '\0' && counter < limit && is_at_beginning)
    {
        if (*(walker + counter) != *(sub + counter))
            is_at_beginning = false;

        counter++;
    }

    counter = 0;

    if (is_at_beginning)
    {
        while (*walker != '\0' && counter < limit)
        {
            *(walker + counter) = *(new_sub + counter);
            counter++;
        }
        replace(str + getLength(sub), sub, new_sub);
    }
    else
    {
        replace(str + 1, sub, new_sub);
    }
}