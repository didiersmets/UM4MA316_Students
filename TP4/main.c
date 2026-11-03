#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "AVL_trees.h"

#define MAX_PEOPLE 1000
#define LEN 64

struct person
{
    char surname[LEN];
    char name[LEN];
    int age;
    struct avl_node node;
};

int cmp_person(const void *a, const void *b)
{
    const struct person *x = a, *y = b;
    int c = strcmp(x->surname, y->surname);
    if (c != 0)
        return c;
    return strcmp(x->name, y->name);
}

static struct person people[MAX_PEOPLE];
static int count = 0;

int main(void)
{
    struct avl_tree t;
    avl_tree_initialize(&t, cmp_person, offsetof(struct person, node));

    int find_mode = 0;
    char line[256];

    printf("INSERT mode: type 'name surname age'. Commands: find, insert, quit\n");
    while (1)
    {
        printf(find_mode ? "find> " : "insert> ");
        fflush(stdout);
        if (!fgets(line, sizeof line, stdin))
            break;

        char cmd[LEN];
        if (sscanf(line, "%63s", cmd) != 1)
            continue;
        if (strcmp(cmd, "quit") == 0)
            break;
        if (strcmp(cmd, "find") == 0)
        {
            find_mode = 1;
            printf("FIND mode: type 'name surname'\n");
            continue;
        }
        if (strcmp(cmd, "insert") == 0)
        {
            find_mode = 0;
            printf("INSERT mode: type 'name surname age'\n");
            continue;
        }

        if (find_mode)
        {
            struct person key;
            if (sscanf(line, "%63s %63s", key.name, key.surname) != 2)
            {
                printf("usage: name surname\n");
                continue;
            }
            struct person *p = avl_tree_find(&t, &key);
            if (p)
                printf("found: %s %s, age %d\n", p->name, p->surname, p->age);
            else
                printf("%s %s not found\n", key.name, key.surname);
        }
        else
        {
            if (count == MAX_PEOPLE)
            {
                printf("phonebook full\n");
                continue;
            }
            struct person *p = &people[count];
            if (sscanf(line, "%63s %63s %d", p->name, p->surname, &p->age) != 3)
            {
                printf("usage: name surname age\n");
                continue;
            }
            if (avl_tree_find(&t, p))
            {
                printf("%s %s already exists\n", p->name, p->surname);
                continue;
            }
            avl_tree_insert(&t, p);
            count++;
            printf("added %s %s (%d people)\n", p->name, p->surname, count);
        }
    }
    return 0;
}