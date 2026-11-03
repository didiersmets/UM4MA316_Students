#include "AVL_trees2.h"

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

static struct avl_node *get_parent(const struct avl_node *node);
static int get_dir(const struct avl_node *node);
static int get_balance(const struct avl_node *node);
static void set_pcb(struct avl_node *node, struct avl_node *parent, int dir, int balance);
static void *get_data_address(const struct avl_node *node, int offset);
static struct avl_node *rotate(struct avl_tree *t, struct avl_node *root, bool dir);

void avl_tree_initialize(struct avl_tree *t, int (*cmp)(const void *, const void *), int offset)
{
    t->root = NULL;
    t->cmp = cmp;
    t->offset = offset;
}

void *avl_tree_find(struct avl_tree *t, const void *data)
{
    struct avl_node *curr = t->root;

    while (curr)
    {
        void *curr_data = get_data_address(curr, t->offset);
        int c = t->cmp(data, curr_data);

        if (c == 0)
            return curr_data;
        curr = curr->children[c > 0];
    }
    return NULL;
}

void avl_tree_insert(struct avl_tree *t, void *data)
{
    assert(t);
    assert(data);

    // walk down to find where the new node goes
    struct avl_node *parent = NULL;
    struct avl_node *curr = t->root;
    int dir = 0;
    while (curr)
    {
        int c = t->cmp(data, get_data_address(curr, t->offset));
        if (c == 0)
            return; // duplicate key is ignored
        parent = curr;
        dir = c > 0;
        curr = curr->children[dir];
    }

    struct avl_node *to_insert = (struct avl_node *)((char *)data + t->offset);
    to_insert->children[0] = NULL;
    to_insert->children[1] = NULL;
    set_pcb(to_insert, parent, dir, 0);

    if (!parent)
    {
        t->root = to_insert;
        return;
    }
    parent->children[dir] = to_insert;

    
    while (parent)
    {
        int delta = dir ? 1 : -1;
        int b = get_balance(parent);

        if (b == 0) 
        {
            set_pcb(parent, get_parent(parent), get_dir(parent), delta);
            dir = get_dir(parent);
            parent = get_parent(parent);
            continue;
        }

        if (b == -delta) 
        {
            set_pcb(parent, get_parent(parent), get_dir(parent), 0);
            return;
        }

    
        struct avl_node *child = parent->children[dir];
        if (get_balance(child) == delta) // single rotation
        {
            rotate(t, parent, !dir);
            set_pcb(parent, get_parent(parent), get_dir(parent), 0);
            set_pcb(child, get_parent(child), get_dir(child), 0);
        }
        else // double rotation
        {
            struct avl_node *grandchild = child->children[!dir];
            int bg = get_balance(grandchild);
            rotate(t, child, dir);
            rotate(t, parent, !dir);
            set_pcb(parent, get_parent(parent), get_dir(parent), bg == delta ? -delta : 0);
            set_pcb(child, get_parent(child), get_dir(child), bg == -delta ? delta : 0);
            set_pcb(grandchild, get_parent(grandchild), get_dir(grandchild), 0);
        }
        return;
    }
}

void *avl_tree_first(struct avl_tree *t)
{
    struct avl_node *curr = t->root;
    if (!curr)
        return NULL;
    while (curr->children[0])
        curr = curr->children[0];
    return get_data_address(curr, t->offset);
}

void *avl_tree_next(struct avl_tree *t, void *data)
{
    struct avl_node *curr = (struct avl_node *)((char *)data + t->offset);

    // smallest element of the right subtree
    if (curr->children[1])
    {
        curr = curr->children[1];
        while (curr->children[0])
            curr = curr->children[0];
        return get_data_address(curr, t->offset);
    }
    // otherwise climb until we come up from a left child
    while (get_parent(curr) && get_dir(curr) == 1)
        curr = get_parent(curr);
    curr = get_parent(curr);
    return curr ? get_data_address(curr, t->offset) : NULL;
}

// pcb = parent address | dir << 2 | (balance + 1)
static struct avl_node *get_parent(const struct avl_node *node)
{
    return (struct avl_node *)(node->pcb & ~(uintptr_t)7);
}

static int get_dir(const struct avl_node *node)
{
    return (node->pcb >> 2) & 1;
}

static int get_balance(const struct avl_node *node)
{
    return (int)(node->pcb & 3) - 1;
}

static void set_pcb(struct avl_node *node, struct avl_node *parent, int dir, int balance)
{
    node->pcb = (uintptr_t)parent | ((uintptr_t)dir << 2) | (uintptr_t)(balance + 1);
}

static void *get_data_address(const struct avl_node *node, int offset)
{
    char *node_pos = (char *)node;
    return node_pos - offset;
}

/* dir : 0 (false) = left rotation, 1 (true) = right rotation */
static struct avl_node *rotate(struct avl_tree *t, struct avl_node *root, bool dir)
{
    struct avl_node *next_root = root->children[!dir];
    struct avl_node *tmp = next_root->children[dir];
    struct avl_node *parent = get_parent(root);
    int root_dir = get_dir(root);

    root->children[!dir] = tmp;
    if (tmp)
        set_pcb(tmp, root, !dir, get_balance(tmp));

    next_root->children[dir] = root;
    set_pcb(next_root, parent, root_dir, get_balance(next_root));
    set_pcb(root, next_root, dir, get_balance(root));

    if (parent)
        parent->children[root_dir] = next_root;
    else
        t->root = next_root;
    return next_root;
}