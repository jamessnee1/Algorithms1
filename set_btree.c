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
    struct bst_node **temp, **previous;
    temp = &set->parent;
    
	
    /*if parent is null, insert there*/
	if ((*temp) == NULL){
        struct bst_node *new = safe_malloc(sizeof(struct bst_node));
        new->data = new_val;
        new->left = NULL;
        new->right = NULL;
        previous = temp;
		(*temp) = new;
        printf("%i inserted into parent\n", (*temp)->data);
		return 1;
	}
    else if ((*temp)->data == new_val){
        /*check for root duplicate found*/
        return 0;
    }
    /*if data at current node is smaller than input data, insert right*/
    else if ((*temp)->data < new_val){
            
            while ((*temp)->right != NULL && (*temp)->data < new_val){
                previous = temp;
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
            /*update previous correctly*/
            previous = temp;
            (*temp)->right = new;
            printf("%i inserted into right. Previous is %i\n", (*temp)->right->data, (*previous)->data);
            return 1;
        }
    
    else{
            /*data at current node is larger than input data, insert left*/
            while ((*temp)->left != NULL && (*temp)->data > new_val){
                previous = temp;
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
            /*update previous correctly*/
            previous = temp;
            (*temp)->left = new;
            printf("%i inserted into left. Previous is %i\n", (*temp)->left->data, (*previous)->data);
            return 1;
        
        }
    
	return 0;
}

int set_delete(set_t *set, int del_val)
{
	
    struct bst_node **node = NULL, **previous = NULL, *temp;
    node = &set->parent;
    int found = 0;
    
    /*nothing in tree*/
    if (set->parent == NULL){
        return 0;
   
    }
    
        while ((*node) != NULL){
            
            previous = node;
            
            /* if our data is at node, break */
            if ((*node)->data == del_val){
                found = 1;
                break;
            }
            else {
                
                /*left traversal*/
                if ((*node)->data > del_val){
                    previous = node;
                    node = &(*node)->left;
                    
                }
                /*right traversal*/
                else {
                    previous = node;
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
                
                printf("Deleted node in case 1: no left or right children. prev is %i\n", (*previous)->data);
                free(*node);
                return 1;

            }
            
            /*CASE 2: node has one child - left*/
            if ((*node)->left != NULL && (*node)->right == NULL){
            
                temp = (*node)->left;
                
                /*parent special case*/
                if ((*previous) == *node){
                    printf("Parent special case - left node not null. prev is %i\n", (*previous)->data);
                    (*node)->data = temp->data;
                    /*temp left needs to link back to previous left*/
                    if ((*node)->left != NULL){
                        (*node)->left = temp->left;
                    }
                    printf("Deleted temp - %i\n", temp->data);
                    temp = NULL;
                    free(temp);
                    return 1;
                }
                
                /*if previous left is our data*/
                if ((*previous)->left == *node){
                    
                    /*point the next data to prev left*/
                    (*previous)->left = (*node)->left;
                }
                else {
                
                    (*previous)->right = (*node)->right;
                }
                printf("Deleted node in case 2: one child-left. prev is %i\n", (*previous)->data);
                free(*node);
                return 1;
                
            }
            
            /*CASE 2: node has one child - right*/
            if ((*node)->right != NULL && (*node)->left == NULL){
                
                temp = (*node)->right;
                
                /*parent special case*/
                if ((*previous) == *node){
                    printf("Parent special case - right node not null. prev is %i\n", (*previous)->data);
                    (*node)->data = temp->data;
                    /*temp left needs to link back to previous left*/
                    if ((*node)->right != NULL){
                        (*node)->right = temp->right;
                    }
                    printf("Deleted temp - %i\n", temp->data);
                    temp = NULL;
                    free(temp);
                    return 1;
                    
                }
                
                /*if previous left is our data*/
                if ((*previous)->left == *node){
                    
                    (*previous)->left = (*node)->left;
                }
                else {
                    
                    (*previous)->right = (*node)->right;
                }
                printf("Deleted node in case 2: one child-right. prev is %i\n", (*previous)->data);
                free(*node);
                return 1;
                
            }
            
            /*CASE 3: two children*/
            if ((*node)->right != NULL && (*node)->left != NULL){
                
                temp = (*node)->right;
                /*if bottom of bst has no children*/
                if (temp->right == NULL && temp->left == NULL){
                
                    /*set the root data to the rights data*/
                    (*node)->data = temp->data;
                    (*node)->right = NULL;
                    printf("Deleted node in case 3: both null. prev is %i\n", (*previous)->data);
                    free(temp);
                    return 1;
                    
                }
                /*if temp has left child*/
                else if (temp->left != NULL && temp->right == NULL) {
                    
                    /*traverse left*/
                    while(temp->left != NULL){
                    
                        (*previous) = temp;
                        temp = temp->left;
                        

                    }
                    /*set the root data to the left child data*/
                    (*node)->data = temp->data;
                    (*previous)->left = NULL;
                    printf("Deleted node in case 3: left not null, right null. prev is %i\n", (*previous)->data);
                    free(temp);
                    return 1;
                
                
                }
                /*if temp has right child*/
                else if (temp->right != NULL && temp->left == NULL){
                    
                    /*set the root data to the right child data*/
                    (*node)->data = temp->data;
                    /*set our root next right to temp right*/
                    (*node)->right = temp->right;
                    printf("Deleted node in case 3: right not null, left null. prev is %i\n", (*previous)->data);
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



