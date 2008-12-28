#include <stdio.h>

typedef struct list {
    void *first;
    struct list *rest;
} list;

list *list_cons(void *first, list *rest);
void *list_first(list *l);
void *list_rest(list *l);
void list_setfirst(list *l, void* value);
void list_setrest(list *l, list* value);
void list_next(list **avar);
void list_free(list *l);
list *list_nreverse(list *l);
list *list_copy(list *l);

#define LIST_END NULL

#define LIST_FOREACH(iter, l)                   \
    for (list *iter = (l);                      \
         iter != LIST_END;                      \
         list_next(&iter))

#define LIST_PRINT(type, fmt, l)                 \
    LIST_FOREACH(xs, l) {                        \
        printf((fmt), *(type*)list_first(xs));   \
    }
