#include "AVL_trees.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static int get_balance(struct avl_node *root);
static void update_height(struct avl_node *root);
static struct avl_node *rotate(struct avl_node *root, bool dir);
static struct avl_node *fix_balance(struct avl_node *root);
static void *get_data_address(const struct avl_node *node, int offset);
static struct avl_node *insert_rec(struct avl_tree *t, struct avl_node *root, struct avl_node *to_insert, void *data);

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset)
{
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}
// the insert function needs multiple helpers to get the job done correctly mainly a fix_balance function after every insetions is
// necessary to keep the AVL self balancing condition alive
void *avl_tree_find(struct avl_tree *t, const void *data)
{
    struct avl_node *curr = t->root;

    while (curr)
    {
        void *curr_data = get_data_address(curr, t->offset);
        int c = t->cmp(data, curr_data);

        if (c == 0)
            return curr_data;
        else if (c < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return NULL;
}

static struct avl_node *insert_rec(struct avl_tree *t, struct avl_node *root, struct avl_node *to_insert, void *data)
{
    if (!root)
        return to_insert;

    int c = t->cmp(data, get_data_address(root, t->offset));

    if (c < 0)
        root->left = insert_rec(t, root->left, to_insert, data);
    else if (c > 0)
        root->right = insert_rec(t, root->right, to_insert, data);
    else
        return root; //for now a duplicate key is ignored 

    update_height(root);
    return fix_balance(root);
}

void avl_tree_insert(struct avl_tree *t, void *data)
{
    assert(t);
    assert(data);
    struct avl_node *to_insert = (struct avl_node *)((char *)data + t->offset);
    to_insert->left = NULL;
    to_insert->right = NULL;
    to_insert->height = 1;
    t->root = insert_rec(t, t->root, to_insert, data);
}

static int get_balance(struct avl_node *root)
{
    if (!root)
    {
        return 0;
    }
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height : 0;
    return right - left;
}

static void update_height(struct avl_node *root)
{
    if (!root)
        return;
    int left = root->left ? root->left->height : 0;
    int right = root->right ? root->right->height : 0;
    root->height = 1 + (left > right ? left : right);
}

/* dir : 0 (false) = left, 1 (true) = right */
static struct avl_node *rotate(struct avl_node *root, bool dir)
{
    assert(root);
    struct avl_node *next_root = !dir ? root->right : root->left;
    assert(next_root);
    struct avl_node *tmp = dir ? next_root->right : next_root->left;
    if (dir)
    {
        root->left = tmp;
        next_root->right = root;
    }
    else
    {
        root->right = tmp;
        next_root->left = root;
    }
    update_height(root);
    update_height(next_root);
    return next_root;
}
static struct avl_node *fix_balance(struct avl_node *root)
{
    int b = get_balance(root);

    if (b > 1) // right heavy
    {
        if (get_balance(root->right) < 0)
            root->right = rotate(root->right, true);
        root = rotate(root, false);
    }
    else if (b < -1) // left heavy
    {
        if (get_balance(root->left) > 0)
            root->left = rotate(root->left, false);
        root = rotate(root, true);
    }
    return root;
}

static void *get_data_address(const struct avl_node *node, int offset)
{
    char *node_pos = (char *)node;
    return node_pos - offset;
}
