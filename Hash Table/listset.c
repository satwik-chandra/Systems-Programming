#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// include the header files with the declarations of listset
#include "listset.h"

struct listset * listset_new() {
  struct listset * result = malloc(sizeof(struct listset));
  result->head = NULL;
  return result;
}

/* check to see if an item is in the set
   returns 1 if in the set, 0 if not */
int listset_lookup(struct listset * this, char * item) {
  struct listnode*node = malloc(sizeof(struct listnode));

for(node = this->head;node != NULL;node = node->next){
  if(strcmp(node->str,item)==0) return 1; 
}
return 0;
}

void listset_add(struct listset * this, char * item) {
if(listset_lookup(this,item) == 0){
  struct listnode*node = malloc(sizeof(struct listnode)); 
  node->str = item;
  node->next = this->head;
  this->head = node;
}
}

void listset_remove(struct listset * this, char * item) {
  struct listnode* currentNode;
  struct listnode* prevNode;
 if(strcmp(this->head->str,item) == 0)
 {
   this->head = this->head->next;
 }
 else
 {
 for(currentNode = this->head;currentNode != NULL; currentNode = currentNode->next){
   
     if(strcmp(currentNode->str,item)== 0)
     {
       prevNode->next = currentNode->next;
     }
     prevNode = currentNode;
   }
 } 
   
}

// place the union of src1 and src2 into dest
void listset_union(struct listset * dest, struct listset * src1,
  struct listset * src2) {
    if((listset_cardinality(dest) == listset_cardinality(src1)) == listset_cardinality(src2)){
           
           struct listnode*nodeA = malloc(sizeof(struct listnode));
           struct listnode*nodeB = malloc(sizeof(struct listnode));
            
            nodeA = src1->head;
            nodeB = src2->head;

            for( ;nodeA!=NULL && nodeB!=NULL;nodeA = nodeA->next,nodeB = nodeB->next){
              listset_add(dest,nodeA->str);
              listset_add(dest,nodeB->str);
            }
         }
}

// place the intersection of src1 and src2 into dest
void listset_intersect(struct listset * dest, struct listset * src1,
  struct listset * src2) {
    struct listnode*nodeA = malloc(sizeof(struct listnode));
           struct listnode*nodeB = malloc(sizeof(struct listnode)); 
           for(nodeA = src1->head;nodeA != NULL; nodeA = nodeA->next)
           {
             for(nodeB = src2->head;nodeB != NULL; nodeB = nodeB->next)
             {
               if(nodeA->str == nodeB->str) listset_add(dest,nodeA->str);
           }
    }
}

// return the number of items in the listset
int listset_cardinality(struct listset * this) {
int counter = 0;
struct listnode*node = malloc(sizeof(struct listnode));
for(node = this->head;node !=NULL;node = node->next){
  if(node->str != NULL) counter++;
}
return counter;
}

// print the elements of the list set
void listset_print(struct listset * this) {
  struct listnode * p;
  for ( p = this->head; p != NULL; p = p->next ) {
    printf("%s, ", p->str);
  }
  printf("\n");
}
