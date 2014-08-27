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
    int flag = 0;
    
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
    
    struct bst_node *temp;
    
    /*Case 1: Root has no children*/
    if (root->left == NULL && root->right == NULL){
        
        if (parent->left = root){
            parent->left = NULL;
        
        }
        else {
            parent->right = NULL;
        }
        
        root = NULL;
        printf("Deleted node in case 1: no left or right children. prev is %i\n", parent->data);
        free(root);
        return;
    }
    /*Case 2: Root has one child, left*/
    if (root->left != NULL && root->right == NULL){
        temp = root->left;
        parent->left = temp;
        temp = NULL;
        free(temp);
        return;
    }
    else {
        remove_from_tree(root->left, parent->left);
    }
    /*Case 2: Root has one child, right*/
    if (root->left == NULL && root->right != NULL){
        temp = root->right;
        parent->right = temp;
        temp = NULL;
        free(temp);
        return;
        
    }
    else {
        remove_from_tree(root->right, parent->right);
    }
    /*Case 3: Root has two children*/
    if (root->left != NULL && root->right != NULL){
        temp = root->left;
        
        
        /*bottom of BST has no children*/
        if (temp->left == NULL && temp->right == NULL){
            /*set the root data to the rights data*/
            root->data = temp->data;
            root->right = NULL;
            printf("Deleted node in case 3: both null. prev is %i\n", parent->data);
            free(temp);
            return;
            
        }
        /*bottom of BST has one left child*/
        else if (temp->left != NULL && temp->right == NULL){
            
            while(temp->left != NULL){
                parent = temp;
                temp = temp->left;
                
            }
            /*set the root data to the left child data*/
            root->data = temp->data;
            /*set our root next right to temp right*/
            root->left = temp->left;
            printf("Deleted node in case 3: left not null, right null. prev is %i\n", parent->data);
            free(temp);
            return;

        
        }
        /*bottom of BST has one right child*/
        else if (temp->left == NULL && temp->right != NULL){
            
            while(temp->right != NULL){
                parent = temp;
                temp = temp->right;
                
            }
            /*set the root data to the right child data*/
            root->data = temp->data;
            /*set our root next right to temp right*/
            root->right = temp->right;
            printf("Deleted node in case 3: right not null, left null. prev is %i\n", parent->data);
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
        
        previous = temp;
        
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
  
    }else {
        return 0;
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
