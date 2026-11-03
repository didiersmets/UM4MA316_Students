#ifndef AVL_TREES2_H
#define AVL_TREES2_H

#include <stdint.h>

struct avl_node
{
    struct avl_node *children[2];
    uintptr_t pcb;
};

struct avl_tree
{
    struct avl_node *root;
    int (*cmp)(const void *, const void *);
    int offset;
};

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset);

void *avl_tree_find(struct avl_tree *t, const void *data);

void avl_tree_insert(struct avl_tree *t, void *data);

void *avl_tree_first(struct avl_tree *t);

void *avl_tree_next(struct avl_tree *t, void *data);

#endif