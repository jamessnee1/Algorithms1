/*
set ADT for arrays
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

/* typedef struct set set_t is defined in set.h */
struct set {
	
    /* Pointer to int array, we will allocate size when we create */
    int *array;
    /* size of the array */
    int memory_used;
    /* size in bytes */
    int size;
};

set_t *set_create(void)
{
	set_t *new_set;
    new_set = safe_malloc(sizeof(set_t));
    /*malloc space enough for one int*/
	new_set->array = (int *)safe_malloc(1 * sizeof(int));
    new_set->memory_used = 0;
    new_set->size = sizeof(set_t);
	return new_set;
	
}

void set_destroy(set_t *set)
{
	free(set->array);
    set->array = NULL;
    set->memory_used = 0;
    set->size = 0;
    free(set);
	return;	
}

int set_insert(set_t *set, int new_val)
{
    int i;
    
    /*If we have no more memory in the array, allocate more*/
    if (set->memory_used == set->size){
        set->size *= 2;
        set->array = (int *)safe_realloc(set->array, set->size * sizeof(int));
    }
    /*search for duplicates*/
    for (i = 0; i < set->memory_used; i++){
        if (set->array[i] == new_val){
            return 0;
        }
    }
    set->array[set->memory_used++] = new_val;
        
   
	return 1;
}

int set_delete(set_t *set, int del_val)
{
	set_t *temp;
    temp = set;
    
    int i, j;
    
    /*Go through the array*/
    for (i = 0; i < temp->memory_used; i++){
        
        if (temp->array[i] == del_val){
            /*if we find delete value, go through array again*/
            for (j = 0; j < temp->memory_used; j++){
                /*shift elements back by one*/
                temp->array[j] = temp->array[j+1];
            
            }
            /*decrement memory used*/
            temp->memory_used--;
            return 1;
            
        }
        
    }
    
    
	return 0;	
}


int set_search(set_t *set, int search_val)
{
	set_t *temp;
    temp = set;
    
    int i;
    
    for (i = 0; i < temp->memory_used; i++){
    
        if (temp->array[i] == search_val){
        
            return 1;
        
        }
    
    }
    
    
	return 0;	
}

void set_print(set_t *set)
{
    int i;
    for (i = 0; i < set->memory_used; i++){
        printf("%d\n", set->array[i]);
    }
	
}



