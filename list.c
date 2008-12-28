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

void *list_rest(list *l) {
    return l->rest;
}

void list_next(list **avar) {
    (*avar) = list_rest(*avar);
}

void list_free(list *l) {
    if (l) {
        list_free(list_rest(l));
        free(l);
    }
}

list *list_copy(list *l) {
    if (l) {
        return list_cons(list_first(l),
                         list_copy(list_rest(l)));
    } else {
        return NULL;
    }
}

