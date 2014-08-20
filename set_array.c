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
    
    int i;
    int flag = 1;
    /*create temp array with size of current array minus one*/
    int *temp_array = safe_malloc((temp->memory_used - 1) * sizeof(int));
    
    for (i = 0; i < temp->memory_used; i++){
        
        /*put every element before the delete value into new array*/
        temp_array[i] = temp->array[i];
    
        if (temp->array[i] == del_val){
        
            /*we have found the delete value, so we simply skip over it*/
            i++;
            /*return temp->array[i];*/
        
        }else {
            flag = 0;
        }
        
    
    }
    
    /*set our shortened array into the set array and free existing one*/
    free(temp->array);
    temp->array = temp_array;
    
    
    if (flag == 0){
        return 0;
    }
    return 1;
}

int set_search(set_t *set, int search_val)
{
	set_t *temp;
    temp = set;
    
    int i;
    
    for (i = 0; i < temp->memory_used; i++){
    
        if (temp->array[i] == search_val){
        
            return temp->array[i];
        
        }
    
    }
    
    
	return 0;	
}

void set_print(set_t *set)
{
    set = NULL;
	/* optional, may help with testing */
}

