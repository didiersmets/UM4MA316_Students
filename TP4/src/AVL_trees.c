#include "AVL_trees.h"

#include <stdlib.h>
#include <stdbool.h>

static int get_balance(struct avl_node *root);
static void update_height(struct avl_node *root);
static struct avl_node *rotate(struct avl_node *root, bool dir);

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *),  int offset)
{
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}
//the insert function needs multiple helpers to get the job done correctly mainly a fix_balance function after every insetions is
//necessary to keep the AVL self balancing condition alive
void *avl_tree_find(struct avl_tree *t, const void *data)
{

}

struct avl_node *fix_balance(struct avl_node *root)
{

}

void avl_tree_insert(struct avl_tree *t, void *data)
{

}

static int get_balance(struct avl_node *root)
{
    if(!root){
        return root;
    }
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height : 0;
    return right - left;
}

static void update_height(struct avl_node *root)
{
    if (!root) return;
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height : 0;
    root -> height = 1 + (left > right ? left : right);
}

/* dir : 0 (false) = left, 1 (true) = right */
static struct avl_node *rotate(struct avl_node *root, bool dir)
{
    assert(root);
    struct avl_node *next_root = !dir ? root->right : root->left;
    assert(next_root); 
    struct avl_node *tmp = dir ? root->right : root->left;
    if (dir){
        root->left = tmp;
        next_root->right = root;
    } 
    else{
        root->right = tmp;
        next_root->left = root;
    }
    update_height(root);
    update_height(next_root);
    return next_root;
}