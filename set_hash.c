/*
set ADT for hash tables with separate chaining
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

/*create struct for linked list separate chaining*/
struct list_t {
    
    int data;
    struct list_t *next;

};

/* typedef struct set set_t is defined in set.h */
struct set {
    
    int size;
    struct list_t **table;
    
};

set_t *set_create(void)
{
    int size = 10;
    int i = 0;
	set_t *new_set = safe_malloc(sizeof(set_t));
    /*We need to specify a size for hash table, todo*/
    new_set->table = safe_malloc(sizeof(struct list_t) * size);
    
    /*initialise elements of table*/
    for(i = 0; i < size; i++){
        
        new_set->table[i] = NULL;
    }
    
    new_set->size = size;
	return new_set;
}

void set_destroy(set_t *set)
{
	int i;
    struct list_t *list, *temp;
    
    /*if nothing in hash table*/
    
    if (set == NULL){
        
        return;
    }
    /*free memory for everything in the hash table*/
    for (i = 0; i < set->size; i++){
        list = set->table[i];
        
        while(list != NULL){
            temp = list;
            list = list->next;
            free(temp);
        }
    
    }
    
    /*lastly, free set*/
    free(set->table);
    free(set);
	return;	
}

int set_insert(set_t *set, int new_val)
{
	/* TODO: define for hash tables with separate chaining */
    new_val = 0;
    set = NULL;
	return 0;
}

int set_delete(set_t *set, int del_val)
{
	/* TODO: define for hash tables with separate chaining */
    del_val = 0;
    set = NULL;
	return 0;	
}

int set_search(set_t *set, int search_val)
{
	/* TODO: define for hash tables with separate chaining */
    set = NULL;
    search_val = 0;
	return 0;	
}

void set_print(set_t *set)
{
    set = NULL;
	/* optional, may help with testing */
}

