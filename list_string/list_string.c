//   list_string.c
//   David Gregg
//   January 2021

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list_string.h"



// create a new list string with the same value as a normal
// NULL-terminated C string
struct list_string * new_list_string(char * text) {
     struct list_string * result = malloc(sizeof(struct list_string));
     struct ls_node * temp = malloc(sizeof(struct ls_node));
     result->head = malloc(sizeof(struct ls_node));
     temp = result->head;
    for(int i = 0; text[i] != '\0' ; i++){
            temp->c = text[i];
            if(text[i + 1] != '\0')
            {
            temp->next = malloc(sizeof(struct ls_node));
            temp = temp->next;
            }
    }

    return result;
 
}

// find the length of the list string
int list_string_length(struct list_string *this) {

    int size = 0;
    

    for(struct ls_node *traverse = this->head; traverse != NULL; traverse = traverse->next){
        size++;
    }

    return size;
}


// compare two strings; return -1 is s1 is lexicographically less that s2;
// return 0 if the strings are equal; return 1 if s1 is lexicographically
// larger than s2. E.g. "aB" is less than "ab" because 'B' has a smaller
// ASCII code than 'b'. Also "abc" is less that "abcd". 
int list_string_compare(struct list_string * s1, struct list_string * s2) {
 int value_s1 = return_ascii_value(s1);
    int value_s2 = return_ascii_value(s2);

    if(value_s1 < value_s2) return -1;
    else if (value_s1 == value_s2) return 0;
    else return 1;
}


// return 1 if str is a substring of text; 0 otherwise
int list_string_substring(struct list_string * text, struct list_string * str) {
 struct ls_node *node_txt = malloc(sizeof(struct ls_node));
   struct ls_node *node_str = malloc(sizeof(struct ls_node));
   struct ls_node *traverse = malloc(sizeof(struct ls_node));
    int found = 0;
   
   node_txt = text->head;
   node_str = str->head;

    //go along the text(string_list) and go through it unitll a match, 
    //once the first letter of "str" is matched
    //move to the next element of "str" and continue after from where the previous match was found
    for(traverse = node_txt; traverse->next!=NULL;traverse = traverse->next){

        if(node_str->next == NULL){
            break;
        }

        else if (traverse->c == node_str->c )
        {   
            found = 1;                                       
            node_str = node_str->next;      
            node_txt = node_txt->next;     
            
        }

        else
        {
            found = 0;
            node_str = str->head;
        }
        
        

    }


  return found;
}

//returns the sum of the ascii values of the characters in a string list
int return_ascii_value(struct list_string *this){
    int value = 0;
    int ascii_value = 0;
    struct ls_node *temp = malloc(sizeof(struct ls_node));
    temp = this->head;
    while (temp->next != NULL)
    {
        ascii_value = (int)(temp->c);
        value = value + ascii_value;
        temp = temp->next;
    }
     return value;
}


