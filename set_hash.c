/*
set ADT for hash tables with separate chaining
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

/* typedef struct set set_t is defined in set.h */
struct set {
	/* TODO: define for hash tables with separate chaining */
};

set_t *set_create(void)
{
	/* TODO: define for hash tables with separate chaining */
	return NULL;
}

void set_destroy(set_t *set)
{
	/* TODO: define for hash tables with separate chaining */
    set = NULL;
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

