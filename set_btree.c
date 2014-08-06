/*
set ADT for binary trees
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

/* typedef struct set set_t is defined in set.h */
struct set {
    
    int data;
    struct set *left, *right;
    
};

set_t *set_create(void)
{
	/* TODO: define for binary trees */
    set_t *new = safe_malloc(sizeof(set_t));
	return new;
}

void set_destroy(set_t *set)
{
	free(set);
	return;	
}

int set_insert(set_t *set, int new_val)
{
	/* TODO: define for binary trees */
    
    
	return 0;
}

int set_delete(set_t *set, int del_val)
{
	/* TODO: define for binary trees */
	return 0;	
}

int set_search(set_t *set, int search_val)
{

    set_t *temp;
    temp = set;
    
    while(temp != NULL){
    
        if(temp->data == search_val){
        /*We have found it*/
            printf("Value %i found!\n", temp->data);
            return temp;
        
        }
        
        if (temp->data > search_val){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
        
    
    }
    
	return 0;	
}

void set_print(set_t *set)
{
    
	/* optional, may help with testing */
}

