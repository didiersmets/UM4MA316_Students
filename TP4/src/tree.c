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

static struct avl_node *right_rotation(struct avl_node *A){
    struct avl_node * B = A -> left;
    struct avl_node * T2 = B -> right;
    B -> right = A;
    A -> left = T2;
    update_height(A);
    update_height(B);
    return B;
}

static struct avl_node *left_rotation(struct avl_node *B){
    struct avl_node * A = B -> right;
    struct avl_node * T2 = A -> left;
    A -> left = B;
    B -> right = T2;
    update_height(B);
    update_height(A);
    return A;
}

int height(struct avl_node *n){
    if (n == NULL){
        return 0;
    }
    return (n->height);
}

void update_height(struct avl_node *n){
    if (n == NULL){
        return;
    }
    n->height = 1 + MAX(height(n->left), height(n->right));
}

static int balance(struct avl_node *n){
    if (n == NULL){
        return 0;
    }
    return (height(n->left) - height(n->right));
}


void avl_tree_insert(struct avl_tree *t, void *data){

    struct avl_node *n = (struct avl_node *)((char *)data + t->offset);

    if (t->root == NULL){
        n->left = NULL;
        n->right = NULL;
        n->height = 1;
        t->root = n;
        return;
    }

    struct avl_node **path[128];
    int depth = 0;

    struct avl_node **x = &t->root;

    while (*x != NULL){

        void *x_data = (char *)(*x) - t->offset;
        int res = t->cmp(data, x_data);

        if (res == 0){
            return;
        }

        if (depth == 128){
            return;
        }

        path[depth++] = x;

        if (res < 0){
            x = &(*x)->left;
        }
        else{
            x = &(*x)->right;
        }
    }

    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    *x = n;

    while (depth > 0){

        x = path[--depth];

        update_height(*x);
        int bf = balance(*x);

        if (bf == 2){
            if (balance((*x)->left) == -1){
                (*x)->left = left_rotation((*x)->left);
            }
            *x = right_rotation(*x);
        }

        else if (bf == -2){
            if (balance((*x)->right) == 1){
                (*x)->right = right_rotation((*x)->right);
            }
            *x = left_rotation(*x);
        }
    }
}
