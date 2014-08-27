/*
 set ADT for binary trees
 */

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

struct bst_node {
    
	int data;
	struct bst_node *left;
	struct bst_node *right;
	
    
};


int set_insert(set_t *set, int new_val)
{
    
	/* create new temp pointer to set */
    struct bst_node **temp, **previous;
    temp = &set->parent;
    int found = 0;
    
    while ((*temp) != NULL){
    
        /*set previous to current value*/
        previous = temp;
        
        /* if our data is at node, break */
        if ((*node)->data == new_val){
            found = 1;
            break;
        }
        
        else {
            
            /*left traversal*/
            if ((*node)->data > del_val){
                node = &(*node)->left;
                
            }
            /*right traversal*/
            else {
                node = &(*node)->right;
                
            }
        }

    }
    
    if (found == 1){
        /*found, return duplicate */
        return 0;
    }
    else {
        
        /*if parent is null, insert there*/
        if ((*temp) == NULL){
            struct bst_node *new = safe_malloc(sizeof(struct bst_node));
            new->data = new_val;
            new->left = NULL;
            new->right = NULL;
            (*temp) = new;
            printf("%i inserted into parent\n", (*temp)->data);
            return 1;
        }
        
        /*if our data is smaller than nodes data, insert right*/
        else if ((*temp)->data < new_val){
            
            while ((*temp)->right != NULL && (*temp)->data < new_val){
                
                temp = &(*temp)->right;
                
                if (new_val == (*temp)->data){
                    /*duplicate found*/
                    return 0;
                }
            }
            
            struct bst_node *new = safe_malloc(sizeof(struct bst_node));
            new->data = new_val;
            new->left = NULL;
            new->right = NULL;
            (*temp)->right = new;
            printf("%i inserted into right\n", (*temp)->right->data);
            return 1;
        }
        
        else{
            /*data is larger than node's data, insert left*/
            while ((*temp)->left != NULL && (*temp)->data > new_val){
                
                temp = &(*temp)->left;
                
                if ((*temp)->data == new_val){
                    /*duplicate found*/
                    return 0;
                }
            }
            
            struct bst_node *new = safe_malloc(sizeof(struct bst_node));
            new->data = new_val;
            new->left = NULL;
            new->right = NULL;
            (*temp)->left = new;
            printf("%i inserted into left\n", (*temp)->left->data);
            return 1;
            
        }
    
    
    }

	return 0;
}

