#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "linalg.h"

struct llnode {
    struct matrix *mat;
    struct llnode *next;
};

struct llist {
    struct llnode *front;
};

struct llist *list_create(void) {
    struct llist *lst = malloc(sizeof(struct llist));
    lst->front = NULL;
    return lst;
}

void add_front(struct matrix *mat, struct llist *lst) {
    assert(lst);
    assert(mat);
    struct llnode *newnode = malloc(sizeof(struct llnode));
    newnode->mat = mat;
    newnode->next = lst->front;
    lst->front = newnode;
}

void list_destroy(struct llist *lst, int d) {
    assert(lst);
    assert(d == 0 || d == 1);
    struct llnode *curnode = lst->front;
    struct llnode *nextnode = NULL;
    while (curnode) {
        nextnode = curnode->next;
        destroy_matrix(curnode->mat);
        free(curnode);
        curnode = nextnode;
    }
    if (d) {
        free(lst);
    } else {
        lst->front = NULL;
    }
}

int list_length(const struct llist *lst) {
    assert(lst);
    int len = 0;
    struct llnode *node = lst->front;
    while (node) {
        ++len;
        node = node->next;
    }
    return len;
}

struct matrix *matrix_at(int index, struct llist *lst) {
    assert(lst);
    if (index < 0) {
        fprintf(stderr, "Error: This is an invalid index\n");
        return NULL;
    }
    if (index >= list_length(lst)) {
        fprintf(stderr, "Error: There is no matrix at that index\n");
        return NULL;
    }
    struct llnode *curnode = lst->front;
    for (int i = 0; i < index; ++i) {
        curnode = curnode->next;
    }
    return curnode->mat;
}

void remove_item(int index, struct llist *lst) {
    assert(lst);
    if (index < 0) {
        fprintf(stderr, "Error: This is an invalid index\n");
        return;
    }
    if (index >= list_length(lst)) {
        fprintf(stderr, "Error: There is no matrix at that index\n");
        return;
    }
    struct llnode *curnode = lst->front;
    struct llnode *prevnode = NULL;
    for (int i = 0; i < index; ++i) {
        prevnode = curnode;
        curnode = curnode->next;
    }
    destroy_matrix(curnode->mat);
    if (prevnode == NULL) {
        lst->front = curnode->next;
    } else {
        prevnode->next = curnode->next;
    }
    free(curnode);
}

void print_llist(struct llist *lst) {
    assert(lst);
    struct llnode *curnode = lst->front;
    int i = 0;
    if (!lst->front) {
        printf("[Empty]\n");
        return;
    }
    while (curnode) {
        printf("%d) ", i);
        print_matrix(curnode->mat);
        ++i;
        curnode = curnode->next;
    }
}