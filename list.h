#pragma once
#ifndef __list_h__
#define __list_h__

#include <stdio.h>

typedef struct list_t {
    void *first;
    struct list_t *rest;
} list_t;

typedef list_t* stack_t;

#define LIST_END NULL

#define FIRSTCAST(type, l) (*(type*)list_first(l))
#define POPCAST(type, l) (*(type*)stack_pop(&l))

#define LIST_FOREACH(iter, l)                   \
    for (list_t *iter = (l);                      \
         iter != LIST_END;                      \
         list_next(&iter))

#define LIST_PRINT(type, fmt, l)                \
    LIST_FOREACH(xs, l) {                       \
        printf((fmt), FIRSTCAST(type, xs));     \
    };


list_t *list_cons(void *first, list_t *rest);
void *list_first(list_t *l);
void *list_rest(list_t *l);
void list_setfirst(list_t *l, void* value);
void list_setrest(list_t *l, list_t* value);
void list_next(list_t **avar);
void list_free(list_t *l);
list_t *list_nreverse(list_t *l);
list_t *list_reverse(list_t *l);
list_t *list_copy(list_t *l);
unsigned long list_length(list_t *l);

void stack_push(void *val, stack_t *st);
void *stack_pop(stack_t *st);

#endif
