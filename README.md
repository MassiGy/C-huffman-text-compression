# C Based Huffman Compression Algorithm Impelementation.


### File Architecture

```BASH
    .
    ├── headers
    │   ├── generic-linked-lists.h
    │   ├── hcompress.h
    │   ├── htree.h
    │   ├── htree-node.h
    │   ├── main.h
    │   └── sys_headers.h
    ├── README.md
    ├── ressources
    └── src
        ├── generic-linked-lists.c
        ├── hcompress.c
        ├── htree.c
        ├── htree-node.c
        ├── main.c
        └── Makefile

    3 directories, 13 files

```

### Description


This project implements a basic version of the Huffman compression algorithm for english text only. This is performed as follows:

##### Compression Algorithm

###### Constructing the huffman tree
- First, go through the text, and for each character create a node storing it and its frequency.
- Second, append each node to a list.
- Third, sort the list regarding the frequency.
- Forth, get the two least, frequency wise, nodes and creat a sub tree, the min will go to the left, and the other one (the max of both) will be the right leaf. 
- Fifth, link these two leaves with a parent node which will have as data the sum of its sons frequencies.
- Sixth, remove the these two elements from your list.
- Seventh, insert the sub tree to your list, respecting the order of frequencies.
- Eighth, redo this for each element of your list.
- At the end, you will end up with a huffman tree, that you will need to store.


###### Subtituting the text with the in-tree binary location
- First, go to a leaf, while doing that, store the path to it in the appropriate binary form.
- Once, on the leaf, insert to a new list the leaf character and its binary path.
- Redo this for each leaf.
- Then, read the file character by character, for each one, substitute it with its binary path on a binary file.
- At the end, the binary file will be the compressed file.


##### Decompression Algorithm

- First, get back the huffman tree & the binary file ( the compression resault ).
- Second, walkthough the compressed file bit by bit, using these to traverse the tree.
- Once, a leaf is hit, write down the character into another txt file. 
- Redo this until foef.
- Then, the text file will be equal to the initial one.



    
