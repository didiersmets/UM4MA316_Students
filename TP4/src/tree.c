#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))


void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset){
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data){
    struct avl_node *x = t->root;

    while (x != NULL){
        void *x_data = (char *)x - t->offset;
        int res = t->cmp(data, x_data);

        if (res == 0){
            return x_data;
        }
        else if (res < 0){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    return NULL;
}

void avl_tree_insert(struct avl_tree *t, void *data){
    struct avl_node *x = t->root;

    while (x != NULL){}
   
}


void right_rotation(struct avl_tree *t){
    struct avl_node * A = t -> root;
    struct avl_node * B = A -> left;
    struct avl_node * T2 = B -> right;
    B -> right = A;
    A -> left = T2;
    update_height(A);
    update_height(B);
}

void left_rotation(struct avl_tree *t){
    struct avl_node * B = t -> root;
    struct avl_node * A = B -> right;
    struct avl_node * T2 = A -> left;
    B -> right = T2;
    A -> left = B;
    update_height(A);
    update_height(B);
}

void update_height(struct avl_node *n){
    n->height = 1 + MAX((n->left->height), (n->right->height));
}