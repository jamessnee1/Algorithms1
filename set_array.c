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

/*function prototype for sort*/
void sort(int *array, int array_size);

set_t *set_create(void)
{
	set_t *new_set;
    new_set = safe_malloc(sizeof(set_t));
    /*malloc space enough for one int*/
	new_set->array = (int *)safe_malloc(1 * sizeof(int));
    new_set->memory_used = 0;
    new_set->size = sizeof(new_set->array);
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
    int duplicate_found = 0;
    
    /*If we have no more memory in the array, allocate more*/
    if (set->memory_used == set->size){
        set->size *= 2;
        set->array = (int *)safe_realloc(set->array, set->size * sizeof(int));
    }
    
    /*search for duplicates using search function*/
    duplicate_found = set_search(set, new_val);
    if (duplicate_found == 1){
        return 0;
    }
    
    /*allocate more memory for one int*/
    set->size += 4;
    set->array = (int *)safe_realloc(set->array, set->size * sizeof(int));
    set->array[set->memory_used++] = new_val;
    
    /*sort the array*/
    sort(set->array, set->memory_used);
    
	return 1;
}

int set_delete(set_t *set, int del_val)
{
    int i, j;
    
    for (i = 0; i < set->memory_used; i++){
        
        if (set->array[i] == del_val){
            
            /*if our value is found shift everything back by one*/
            for (j = i; j < set->memory_used; j++){
                set->array[j] =  set->array[j+1];
            
            }
            
            /*decrement memory used*/
            set->memory_used--;
            return 1;
        
        }
    
    }
    return 0;
}




int set_search(set_t *set, int search_val)
{
    /*search through the array. Insert and delete uses this function*/
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

void sort(int *array, int array_size)
{
    
    /*implements bubble sort on our array for sorting*/
    /*when insertion and deletion happens to preserve order*/
    /*Implementation from: http://stackoverflow.com/questions/3893937/c-array-sorting-tips*/
    
    int i, j, temp;
    
    for (i = 0; i < array_size - 1; i++){
        
        for (j = 0; j < (array_size - 1) - i; j++){
            
            if (array[j] > array[j+1]){
                
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            
            }
            
        }
    
    
    }


}



