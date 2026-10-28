#ifndef _TREE_H
#define _TREE_H

struct avl_node {
    struct avl_node *left;
    struct avl_node *right;
    int height;
};

struct avl_tree {
    struct avl_node *root;
    int (*cmp)(const void *, const void *);
    int offset;
};

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset);
void *avl_tree_find(struct avl_tree *t, const void *data);
void avl_tree_insert(struct avl_tree *t, void *data);

#endif