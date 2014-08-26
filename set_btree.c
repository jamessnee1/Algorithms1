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

/*function prototype for print*/
void print(struct bst_node *node);

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

/*function to destroy a single node*/
void node_destroy(struct bst_node *node){
    
    if (node){
        node_destroy(node->left);
        node_destroy(node->right);
        free(node);
    }
    
}

void set_destroy(set_t *set)
{
    node_destroy(set->parent);
	free(set);
	return;	
}

int set_insert(set_t *set, int new_val)
{

	/* create new temp pointer to set */
    struct bst_node **temp;
    temp = &set->parent;
    
	
    /*if parent is null, insert there*/
	if ((*temp) == NULL){
        struct bst_node *new = safe_malloc(sizeof(struct bst_node));
        new->data = new_val;
        new->left = NULL;
        new->right = NULL;
		(*temp) = new;
		return 1;
	}
    else if ((*temp)->data == new_val){
        /*check for root duplicate found*/
        return 0;
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
            return 1;
        
        }
    
	return 0;
}

int set_delete(set_t *set, int del_val)
{
	
    struct bst_node **node, **previous, *temp;
    node = &set->parent;
    int found = 0;
    
    /*nothing in tree*/
    if (set->parent == NULL){
        return 0;
   
    }
    
        while ((*node) != NULL){
            
            /* if our data is at node, return */
            if ((*node)->data == del_val){
                found = 1;
                break;
            }
            else {
                /*keep track of previous node while traversing*/
                previous = node;
                
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
            /*found it*/
            /*CASE 1: No left or right children*/
            if ((*node)->left == NULL && (*node)->right == NULL){

                if ((*previous)->left == *node){
                    
                    (*previous)->left = NULL;
                    
                }
                else {
                
                    (*previous)->right = NULL;
                    
                }
                
                free(*node);
                return 1;

            }
            
            /*CASE 2: node has one child - left*/
            if ((*node)->left != NULL && (*node)->right == NULL){
            
                temp = (*node)->left;
                /*if we are at the parent node*/
                if ((*previous) == NULL){
                    /*set parent node data to right data*/
                    (*node)->data = temp->data;
                    (*node)->left = NULL;
                    free(*node);
                    return 1;
                    
                }
                /*if previous left is our data*/
                if ((*previous)->left == *node){
                
                    (*previous)->left = (*node)->left;
                }
                else {
                
                    (*previous)->right = (*node)->right;
                }
                free(*node);
                return 1;
                
            }
            
            /*CASE 2: node has one child - right*/
            if ((*node)->right != NULL && (*node)->left == NULL){
                
                temp = (*node)->right;
                /*if we are at the parent node*/
                if ((*previous) == NULL){
                    /*set parent node data to right data*/
                    (*node)->data = temp->data;
                    (*node)->right = NULL;
                    free(*node);
                    return 1;
                    
                }
                /*if previous left is our data*/
                if ((*previous)->left == *node){
                    
                    (*previous)->left = (*node)->left;
                }
                else {
                    
                    (*previous)->right = (*node)->right;
                }
                free(*node);
                return 1;
                
            }
            
            /*CASE 3: two children*/
            if ((*node)->right != NULL && (*node)->left != NULL){
                
                temp = (*node)->right;
                /*if temp has no children*/
                if (temp->right == NULL && temp->left == NULL){
                
                    /*set the root data to the rights data*/
                    (*node)->data = temp->data;
                    (*node)->right = NULL;
                    free(temp);
                    return 1;
                    
                }
                /*if temp has left child*/
                else if (temp->left != NULL) {
                    
                    /*traverse left*/
                    while(temp->left != NULL){
                    
                        (*previous) = temp;
                        temp = temp->left;
                        

                    }
                    /*set the root data to the left child data*/
                    (*node)->data = temp->data;
                    (*previous)->left = NULL;
                    free(temp);
                    return 1;
                
                
                }
                /*if temp has right child*/
                else if (temp->right != NULL && temp->left == NULL){
                    
                    /*set the root data to the right child data*/
                    (*node)->data = temp->data;
                    /*set our root next right to temp right*/
                    (*node)->right = temp->right;
                    free(temp);
                    return 1;
                
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
    print(set->parent);
	
}

void print(struct bst_node *node){

    if (node){
        print(node->left);
        printf("%d\n", node->data);
        print(node->right);
    
    }

}



