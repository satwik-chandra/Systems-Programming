// code for a huffman coder


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"

// create a new huffcoder structure
struct huffcoder *  huffcoder_new()
{
     struct huffcoder *huffman_coder = malloc(sizeof(struct huffcoder));

    huffman_coder->tree = malloc(sizeof(struct huffchar)*NUM_CHARS);

    for(int i = 0; i<NUM_CHARS; i++){
        huffman_coder->tree[i].freq = huffman_coder->freqs[i];
        huffman_coder->tree[i].is_compound = 0;
        huffman_coder->tree[i].seqno = i;
        huffman_coder->tree[i].u.c = i;
        huffman_coder->tree[i].u.compound.left = malloc(sizeof(struct huffchar));
        huffman_coder->tree[i].u.compound.right = malloc(sizeof(struct huffchar)); 
    } 
    return huffman_coder;
}

// count the frequency of characters in a file; set chars with zero
// frequency to one
void huffcoder_count(struct huffcoder * this, char * filename)
{  FILE *file;
    file = fopen(filename, "r");
    unsigned char character = fgetc(file);
while (!feof(file))
{
    this->freqs[character]++;
}

for(int i  = 0; i<NUM_CHARS; i++){
    if(this->freqs[i] == 0) this->freqs[i] = 1;
}

    fclose(file);
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes
void huffcoder_build_tree(struct huffcoder * this)
{
     struct huffchar *sorted[NUM_CHARS];
    for (int i = NUM_CHARS - 1; i >= 0; i--) {
        sorted[i] =  malloc(sizeof(struct huffchar));
        sorted[i]->u.c = i;
        sorted[i]->freq = this->freqs[i];
        sorted[i]->seqno = i;
    }
    selectionSort(sorted, NUM_CHARS);

    int seqNo = NUM_CHARS;
    int currentSize = NUM_CHARS;
    while (currentSize > 1) {
        struct huffchar *one = sorted[0];
        struct huffchar *two = sorted[1];

        struct huffchar *new = malloc(sizeof(struct huffchar));
        new->freq = one->freq + two->freq;
        new->is_compound = 1;
        new->u.compound.left = one;
        new->u.compound.right = two;
        new->seqno = seqNo;

        sorted[0] = NULL;
        sorted[1] = new;

        shiftElemsDown(sorted, currentSize, 1);
        currentSize -= 1;
        selectionSort(sorted, currentSize);

        seqNo++;
    }

    this->tree = sorted[0];
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder * this)
{
    tree2table_recursive(this, this->tree, 0, 0);
}


// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder * this)
{
  for ( int i = 0; i < NUM_CHARS; i++ ) {
    // print the code
    printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], this->codes[i]);;
  }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{
    FILE *file;
    file = fopen(input_filename, "r");
    unsigned char character = fgetc(file);

    FILE *output;
    output = fopen(output_filename,"w");
    
    while (!feof(file))
    {
       fputs(this->codes[character],output);
    }
    
    
    fclose(file);
    fclose(output);

}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder * this, char * input_filename,
    char * output_filename)
{ FILE *file;
    file = fopen(input_filename, "r");
    unsigned char bit = fgetc(file);

    FILE *output;
    output = fopen(output_filename,"w");
    
    while(!feof(file)){
        struct huffchar *tree = this->tree;
    
        while(tree->is_compound){
            if(bit == '0') tree = tree->u.compound.left;
            else tree = tree->u.compound.right;
        }
        // we have reached the leaf node
        fputc(tree->u.c,output);
    
    }

    fclose(file);
    fclose(output);
}


void switchElements(struct huffchar **array, int i, int j) {
    struct huffchar *temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void selectionSort(struct huffchar **array, int size) {
    for (int i = 0; i < size; i++) {
        int selected = i;
        for (int j = i + 1; j < size; j++) {
            if (array[j]->freq < array[selected]->freq) {
                selected = j;
            } else if (array[j]->freq == array[selected]->freq) {
                if (array[j]->seqno < array[selected]->seqno) {
                    selected = j;
                }
            }
        }

        if (selected != i) {
            switchElements(array, i, selected);
        }
    }
}

void shiftElemsDown(struct huffchar **array, int size, int num) {
    for (int i = 0; i < size; i++) {
        array[i] = array[i + num];
    }
}

// recursive function to convert the Huffman tree into a table of
// Huffman codes
void tree2table_recursive(struct huffcoder *this, struct huffchar *node, int *path, int depth) {
    if (node->is_compound == 1) {
        if (node->u.compound.left != NULL) {
            int *temp = malloc(sizeof(int) * depth + 1);
            for (int i = 0; i < depth; i++) {
                temp[i] = path[i];
            }
            temp[depth] = 0;

            tree2table_recursive(this, node->u.compound.left, temp, depth + 1);
        }
        if (node->u.compound.right != NULL) {
            int *temp = malloc(sizeof(int) * depth + 1);
            for (int i = 0; i < depth; i++) {
                temp[i] = path[i];
            }
            temp[depth] = 1;

            tree2table_recursive(this, node->u.compound.right, temp, depth + 1);
        }
    } else {
        unsigned long long code = 0;
        for (int i = 0; i < depth; i++) {
            code = (code << 1) | path[i];
        }

        this->codes[node->u.c] = (char *)code;
        this->code_lengths[node->u.c] = depth;
    }
}
