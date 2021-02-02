#include "bitset.h"
#include <math.h>
#include <stdlib.h>
// create a new, empty bit vector set with a universe of 'size' items
struct bitset * bitset_new(int size) {
   struct bitset * result = malloc(sizeof(struct bitset));
    float word_size = 64.0;
    int words = ceil(size/word_size);
    result -> size_in_words = words;
   result -> universe_size = size;
    result -> bits = malloc(sizeof(uint64_t)*words);
    for(int i = 0; i<words;i++){
       result -> bits[i] = 0;
   }
    return result;

}

// get the size of the universe of items that could be stored in the set
int bitset_size(struct bitset * this) {
     return this -> universe_size;
    }

// get the number of items that are stored in the set
int bitset_cardinality(struct bitset * this){
    int cardiniality = 0;
    for(int i; i< this->universe_size;i++){
        if(this->bits[i] == 1) cardiniality++; 
    } return cardiniality;
}

// check to see if an item is in the set
int bitset_lookup(struct bitset * this, int item){

    return (this->bits[item/sizeof(uint64_t)] & (1<<item%sizeof(uint64_t)));

}

// add an item, with number 'item' to the set
// has no effect if the item is already in the set
void bitset_add(struct bitset * this, int item) {
     this -> bits[item/sizeof(uint64_t)] |= (1 << (item % sizeof(uint64_t)));
}

// remove an item with number 'item' from the set
void bitset_remove(struct bitset * this, int item) {
    this->bits[item / sizeof(uint64_t)] &= (1 << (item % sizeof(uint64_t)));
}

// place the union of src1 and src2 into dest;
// all of src1, src2, and dest must have the same size universe
void bitset_union(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {

        for (int i = 0; i < src1->size_in_words; i++)
    {
        dest->bits[i] = src1->bits[i] | src2->bits[i];
    }
}

// place the intersection of src1 and src2 into dest
// all of src1, src2, and dest must have the same size universe
void bitset_intersect(struct bitset * dest, struct bitset * src1,
    struct bitset * src2) {

  for(int i = 0; i < src1->size_in_words; i++){
      dest-> bits[i] = src1-> bits[i] & src2-> bits[i];
  }

}
