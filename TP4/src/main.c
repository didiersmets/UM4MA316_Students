#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "tree.h"

struct word {
    const char *text;
    struct avl_node node;
};

int compare_words(const void *a, const void *b){
    const struct word *w1 = a;
    const struct word *w2 = b;
    return strcmp(w1->text, w2->text);
}

int main(void){
    struct avl_tree tree;
    avl_tree_initialize(&tree, compare_words, offsetof(struct word, node));

    struct word w[] = {
        {"a"},
        {"b"},
        {"c"},
        {"d"},
        {"e"}
    };

    for (int i = 0; i < 5; i++){
        avl_tree_insert(&tree, &w[i]);
    }

    struct word w1 = {"a"};
    struct word *found = avl_tree_find(&tree, &w1);

    if (found != NULL){
        printf("Found: %s\n", found->text);
    }
    else{
        printf("Not found\n");
    }

    return 0;
}
