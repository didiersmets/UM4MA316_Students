#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset ){
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

void avl_tree_insert(struct avl_tree *t, void *data);