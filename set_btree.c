/*
set ADT for binary trees
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/

struct bst_node {

	int data;
	struct bst_node *left;
	struct bst_node *right;
	

};

/* typedef struct set set_t is defined in set.h */
struct set {
    
    struct bst_node *parent;
    
};

set_t *set_create(void)
{
    
    set_t *new = safe_malloc(sizeof(set_t));
    new->parent = NULL;
	return new;
}

void set_destroy(set_t *set)
{
    set_t *temp;
    struct bst_node *temp_node;
    
    temp = set;
    temp_node = temp->parent;
    
    while (temp_node != NULL){
    
        if (temp_node->right != NULL){
        
            temp_node = temp_node->right;
            set_destroy(temp);
            temp = NULL;
            
        }
        if (temp_node->left != NULL){
        
            temp_node = temp_node->left;
            set_destroy(temp);
            temp = NULL;

        
        }
    
    }
    
	free(set);
	return;	
}

int set_insert(set_t *set, int new_val)
{
	
    struct bst_node *new = safe_malloc(sizeof(struct bst_node));
    new->data = new_val;
	
    /* create new temp pointer to set */
    set_t *temp;
    temp = set;
    
	
    /*if parent is null, insert there*/
	if (temp->parent == NULL){
		temp->parent = new;
		return 1;
	}
    
        /*if our data is smaller than nodes data, insert left*/
		if (new->data < temp->parent->data){
			if (temp->parent->left == NULL){
				temp->parent->left = new;
				return 1;
            
			}
            /*else, call set_insert again, going one level deeper in tree*/
            else {
                temp->parent->left = temp->parent->left->left;
                set_insert(temp, new_val);
            
            }
        
		}
        /*if our data is larger than nodes data, insert right*/
		if (new->data > temp->parent->data){
			if (temp->parent->right == NULL){
				temp->parent->right = new;
				return 1;

			}
            /*else, call set_insert again, going one level deeper in tree*/
            else {
                temp->parent->right = temp->parent->right->right;
                set_insert(temp, new_val);
                
            }
		}
	
    
	return 0;
}

int set_delete(set_t *set, int del_val)
{
	
    struct bst_node *node = NULL, *previous = NULL;
    node = set->parent;
    
    /*nothing in tree*/
    if (set->parent == NULL){
        
        return 0;
   
    }
    
    else{
 
        if (del_val == node->data){
            /*found it*/
            
            /*CASE 1: No left or right children*/
            if (node->left == NULL && node->right == NULL){
            
                /*no previous node*/
                if (previous == NULL){
                    
                    free(node);
                    return 1;
                }
                
                
                if (previous->left == node){
                    
                    previous->left = NULL;
                    
                }
                else {
                
                    previous->right = NULL;
                    
                }
                
                free(node);
                return 1;

            
            }
            
            /*CASE 2: node has one child - left*/
            if (node->left == NULL){
            
                if (previous == NULL){
                
                    struct bst_node *temp = node;
                    node = node->right;
                    free(temp);
                    return 1;
                    
                }
                
                if (previous->left == node){
                
                    previous->left = node->right;
                }
                else {
                
                    previous->right = node->right;
                }
                free(node);
                return 1;
                
            }
            
            /*CASE 2: node has one child - right*/
            if (node->right == NULL){
                
                if (previous == NULL){
                    
                    struct bst_node *temp = node;
                    node = node->left;
                    free(temp);
                    return 1;
                    
                }
                
                if (previous->left == node){
                    
                    previous->left = node->left;
                }
                else {
                    
                    previous->right = node->left;
                }
                free(node);
                return 1;
                
            }
            
            /*CASE 3: two children*/
            struct bst_node *right_child, *right_parent;
            right_child = node->right;
            right_parent = node;
            
            while (right_child->left != NULL){
            
                right_parent = right_child;
                right_child = right_child->left;

            }
            node->data = right_child->data;
            
            if (right_parent == node){
                
                node->right = right_child->right;
            
            }
            else{
            
                right_parent->left = right_child->right;
            
            
            }
            free(right_child);
            
            if (previous == NULL){
                
                return 0;
            }

            
            
            return 1;
        }
        
        else{
            
            if (del_val < node->data){
                
                /*traversal left*/
                previous = node;
                node = node->left;
                
            }
            
            if (del_val > node->data){
                
                /*traversal right*/
                previous = node;
                node = node->right;
                
            }
            
        
        }
        
    
    }
    
	return 0;	
}

int set_search(set_t *set, int search_val)
{
    /*assign a pointer to parent of tree*/
    struct bst_node *temp;
    temp = set->parent;
    
    while (temp != NULL){
    
        /* if our data is at node, return */
        if (temp->data == search_val){
            return 1;
        }
        else {
            /*left traversal*/
            if (temp->data > search_val){
                temp = temp->left;
            }
            /*right traversal*/
            else {
                temp = temp->right;
            }
        }
    
    }
    
	return 0;	
}

void set_print(set_t *set)
{
    set_t *node;
	node = set;
	
}

