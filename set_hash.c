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

/*hash function*/
int hash(set_t *set, int h){
    
    unsigned int hash_val;
    
    hash_val = 0;
    
    /*for each element in the table, we multiply hash by 32 and minus hashval*/
    /*bit shifting and subtraction are more cost effective than multiplication*/
    hash_val = h + (hash_val << 5) - hash_val;
    /*return the hash value mod the size so it will fit in range*/
    return hash_val % set->size;
    
}

set_t *set_create(void)
{
    int size = 1;
    int i = 0;
    
    if (size < 1){
        return NULL;
    }
	set_t *new_set = safe_malloc(sizeof(set_t));
    /*We need to specify a size for hash table*/
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
    int find_duplicate = 0;
	struct list_t *new;
    /*hash the new value*/
    unsigned int hash_val = hash(set, new_val);
    /*allocate memory for new*/
    new = safe_malloc(sizeof(struct list_t));
    
    /*check if new_val already exists*/
    find_duplicate = set_search(set, new_val);
    if (find_duplicate == 1){
        return 0;
    }
    /*otherwise, insert into list*/
    new->data = new_val;
    new->next = set->table[hash_val];
    set->table[hash_val] = new;
	return 1;
}

int set_delete(set_t *set, int del_val)
{
    struct list_t *list, *temp;
    /*hash the delete value*/
    unsigned int hash_val = hash(set, del_val);
    
    
    /*iterate through the list with hash values*/
    for (list = set->table[hash_val]; list != NULL; list = list->next){
    
        if (list->data == del_val){
            /*found it to delete*/
            temp = list;
            list = list->next;
            free(temp);
            return 1;
        }
        
    }
	return 0;
}

int set_search(set_t *set, int search_val)
{
    struct list_t *list;
    /*hash the search value*/
    unsigned int hash_val = hash(set, search_val);
    
    /*iterate through the list with the hash value*/
    for (list = set->table[hash_val]; list != NULL; list = list->next){
        
        if (list->data == search_val){
            /*data found*/
            return 1;
        }
    
    }
    
	return 0;	
}

void set_print(set_t *set)
{
    set = NULL;
	/* optional, may help with testing */
}


