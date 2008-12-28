#include <stdlib.h>
#include <stdio.h>

#include "list.h"

list *list_cons(void *first, list *rest) {
    list *ret = malloc(sizeof(list));
    ret->first = first;
    ret->rest = rest;
    return ret;
}

void *list_first(list *l) {
    return l->first;
}

void list_setfirst(list *l, void* value) {
    l->first = value;
}

void *list_rest(list *l) {
    return l->rest;
}

void list_setrest(list *l, list* value) {
    l->rest = value;
}

void list_next(list **avar) {
    (*avar) = list_rest(*avar);
}

void list_free(list *l) {
    list *cur = l;
    list *next;
    
    while (cur) {
        next = list_rest(cur);
        free(cur);
        cur = next;
    }
}

list *list_nreverse(list *l) {
    list *prev = LIST_END;
    list *cur = l;
    list *next;

    while (cur) {
        next = list_rest(cur);
        list_setrest(cur, prev);
        prev = cur;
        cur = next;
    }

    return prev;
}

list *list_copy(list *l) {
    if (l) {
        return list_cons(list_first(l),
                         list_copy(list_rest(l)));
    } else {
        return NULL;
    }
}

