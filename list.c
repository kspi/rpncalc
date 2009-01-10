#include <stdlib.h>
#include <stdio.h>

typedef struct list_t {
    void *first;
    struct list_t *rest;
} list_t;
typedef list_t* stack_t;

#define LIST_TYPES_DEFINED
#include "list.h"


list_t *list_cons(void *first, list_t *rest) {
    list_t *ret = malloc(sizeof(list_t));
    ret->first = first;
    ret->rest = rest;
    return ret;
}


void *list_first(const list_t *l) {
    return l->first;
}


void list_setfirst(list_t *l, void* value) {
    l->first = value;
}


void *list_rest(const list_t *l) {
    return l->rest;
}


void list_setrest(list_t *l, list_t* value) {
    l->rest = value;
}


void list_next(const list_t **avar) {
    (*avar) = list_rest(*avar);
}


void list_free(list_t *l) {
    list_t *cur = l;
    list_t *next;
    
    while (cur) {
        next = list_rest(cur);
        free(cur);
        cur = next;
    }
}


list_t *list_nreverse(list_t *l) {
    list_t *prev = LIST_END;
    list_t *cur = l;
    list_t *next;

    while (cur) {
        next = list_rest(cur);
        list_setrest(cur, prev);
        prev = cur;
        cur = next;
    }

    return prev;
}


list_t *list_reverse(const list_t *l) {
    return list_nreverse(list_copy(l));
}


list_t *list_copy(const list_t *l) {
    const list_t *cur = l;
    list_t *newprev = NULL;
    list_t *newcur = LIST_END;
    list_t *init = NULL;

    while (cur) {
        newcur = list_cons(list_first(cur), LIST_END);
        if (!init) {
            init = newcur;
        }
        if (newprev) {
            list_setrest(newprev, newcur);
        }

        newprev = newcur;
        list_next(&cur);
    }

    if (newprev) {
        list_setrest(newprev, LIST_END);
    }

    return init;
}


long list_length(const list_t *l) {
    long len = 0;
    LIST_FOREACH(cons, l) {
        len++;
    }
    return len;
}


void stack_push(void *val, stack_t *st) {
    (*st) = list_cons(val, *st);
}


void *stack_pop(stack_t *st) {
    void *val = list_first(*st);
    list_t *cons = *st;
    (*st) = list_rest(*st);
    free(cons);
    return val;
}
