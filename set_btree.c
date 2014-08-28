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

/* typedef struct set set_t is defined in set.h */
struct set {
    
    struct bst_node *parent;
    
};

/*function prototypes*/
void print(struct bst_node *node);
struct bst_node * insert(int new_val);
void insert_into_tree(struct bst_node *root, struct bst_node *new);
void remove_from_tree(struct bst_node *root, struct bst_node *parent);


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
    /*create pointer to set*/
    struct bst_node **node, *temp;
    node = &set->parent;
    
    /*Case 1: Parent node*/
    if ((*node) == NULL){
        
        struct bst_node *new = safe_malloc(sizeof(struct bst_node));
        new->data = new_val;
        new->left = NULL;
        new->right = NULL;
		(*node) = new;
        printf("%i inserted into parent\n", (*node)->data);
		return 1;
    
    }

    /*check for duplicates*/
    if ((*node)->data == new_val){
        return 0;
    }
        
    /*point temp to a new node*/
    temp = insert(new_val);
        
    /*insert function handles left and right*/
    insert_into_tree((*node),temp);

	return 1;
}

void insert_into_tree(struct bst_node *root, struct bst_node *new){
    
    /*if our data is smaller than the roots data, go left*/
    if (new->data < root->data){
        if (root->left == NULL){
            root->left = new;
            printf("Root of %i is %i.\n",root->left->data, root->data);
            printf("%i inserted into left.\n", new->data);
        }
        else {
            insert_into_tree(root->left, new);
        }
    }
    
    /*if our data is larger than the roots data, go right*/
    if (new->data > root->data){
        if (root->right == NULL){
            root->right = new;
            printf("Root of %i is %i.\n",root->right->data, root->data);
            printf("%i inserted into right.\n", new->data);
        }
        else {
            insert_into_tree(root->right, new);
        }
    }

}

struct bst_node * insert(int new_val){
    
    /*create new node*/
    struct bst_node *new = safe_malloc(sizeof(struct bst_node));
    new->data = new_val;
    new->left = NULL;
    new->right = NULL;
    return new;

}

void remove_from_tree(struct bst_node *root, struct bst_node *parent){
    
    struct bst_node *temp, *previous;
    
    /*Case 1: Root has no children*/
    if (root->left == NULL && root->right == NULL){
        
        /*set the previous next to null*/
        if (parent->left == root){
            
            parent->left = NULL;
            
        }
        else {
            
            parent->right = NULL;
            
        }

        printf("Deleted node in case 1: no left or right children.\n");
        free(root);
        return;
    }
    /*Case 2: Root has one child, left*/
    if (root->left != NULL && root->right == NULL){
        
        /*special case for root of tree*/
        if (parent == root){
            /*find the largest element of left subtree to replace*/
            temp = root->left;
            
            /*traverse left until we can't go any further*/
            while (temp->right != NULL){
                temp = temp->right;
            }
            
            if (temp->right == NULL){
                /*set the original node's data to smallest in right subtree*/
                root->data = temp->data;
                printf("Special case parent - left not null\n");
                free(temp);
            }
            return;
        }
        
        
        /*set temp to root node to delete*/
        temp = root;
        parent->left = temp->left;
        printf("Case 2: one child left, deleted %i\n", temp->data);
        free(temp);
        return;
    }
    /*Case 2: Root has one child, right*/
    if (root->left == NULL && root->right != NULL){
        
        /*special case for root of tree*/
        if (parent == root){
            /*find the smallest element of right subtree to replace*/
            temp = root->right;
            
            /*traverse left until we can't go any further*/
            while (temp->left != NULL){
                temp = temp->left;
            }
            
            if (temp->left == NULL){
                /*set the root node's data to smallest in right subtree*/
                root->data = temp->data;
                printf("Special case parent - right not null\n");
                free(temp);
            }
            return;
        }
        
        /*set temp to root node to delete*/
        temp = root;
        parent->right = temp->right;
        printf("Case 2: one child right, deleted %i\n", temp->data);
        free(temp);
        return;
        
    }
    /*Case 3: Root has two children*/
    if (root->left != NULL && root->right != NULL){

        /*go right once then left to find the smallest value to replace node value*/
        temp = root->right;
        /*traverse left until we can't go any further*/
        while (temp->left != NULL){
            previous = temp;
            temp = temp->left;
        }
        
        if (temp->left == NULL){
            /*change the value of root data to bottom of BST*/
            root->data = temp->data;
            previous->left = NULL;
            printf("Case 3: Root has two children. Root node changed to %i\n", root->data);
            printf("temp is %i\n", temp->data);
            free(temp);
            return;
        
        }

        
        return;
    }

}

int set_delete(set_t *set, int del_val)
{
    struct bst_node *temp, *previous;
    temp = set->parent;
    int found = 0;
    
    /*nothing in tree*/
    if (set->parent == NULL){
        return 0;
        
    }
    
    while (temp != NULL){
        
        /* if our data is at node, break */
        if (temp->data == del_val){
            found = 1;
            break;
        }
        else {
            
            /*left traversal*/
            if (temp->data > del_val){
                previous = temp;
                temp = temp->left;
                
                
            }
            /*right traversal*/
            else {
                previous = temp;
                temp = temp->right;
                
            }
        }
        
    }
    
    if (found == 1){
        /*found it*/
        remove_from_tree(temp, previous);
        return 1;
  
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
    /*prints tree in preorder*/
    if (node){
        printf("%d\n", node->data);
        print(node->left);
        print(node->right);
        
        
    }
    
}
