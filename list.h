/*
 * list.c - sąrašų biblioteka.
 *
 * Sąrašai yra list_t* tipo. Jie susideda iš cons ląstelių, kurių
 * velesnis narys rodo į sąrašo tesinį arba į LIST_END (NULL).
 *
 * Stekai yra list_t** arba kitaip tariant stack_t* tipo. Sąrašą
 * galima naudoti kaip steką tiesiog stekų funkcijoms davus rodyklę į
 * jo kintamąjį, pvz.
 *
 *  list_t *lst;
 *  stack_push(&x, &lst);
 *
 */

#pragma once
#ifndef list_h__
#define list_h__

#include <stdio.h>


#ifndef LIST_TYPES_DEFINED
typedef struct list_t list_t;
typedef list_t* stack_t;
#endif


#define LIST_END NULL

#define FIRSTCAST(type, l) (*(type*)list_first(l))
#define POPCAST(type, l) (*(type*)stack_pop(&l))

#define LIST_FOREACH(iter, l)                   \
    for (const list_t *iter = (l);              \
         iter != LIST_END;                      \
         list_next(&iter))

#define LIST_PRINT(type, fmt, l)                \
    LIST_FOREACH(xs, l) {                       \
        printf((fmt), FIRSTCAST(type, xs));     \
    };


/*
 * list_cons - alokuoja naują cons ląstelę.
 */
list_t *list_cons(void *first, list_t *rest);

/*
 * list_first - grąžina rodyklę į cons dalelės ankstesnįjį narį
 * (sąrašo atveju - į tos ląstelės vertę).
 */
void *list_first(const list_t *l);

/*
 * list_setfirst - nustato ankstesnįjį narį.
 */
void *list_rest(const list_t *l);

/*
 * list_rest - grąžina rodyklę į vėlesnijį narį (šąrašo atveju - į
 * sąrašo tęsinį).
 */
void list_setfirst(list_t *l, void* value);

/*
 * list_setrest - nustato paskesnįjį narį.
 */
void list_setrest(list_t *l, list_t* value);

/*
 * list_next - nustato rodyklę į rodyklę į sąrašą į to sąrašo
 * paskesnįjį narį, skirta naudoti iteracijai, pavyzdžiui for ciklo
 * trečiame sakinyje.
 */
void list_next(const list_t **avar);

/*
 * list_free - išlaisvina visas duoto sąrašo cons ląsteles.
 */
void list_free(list_t *l);

/*
 * list_nreverse - apsuka sąrašą į kitą pusę keisdamas originalūjį
 * sąrašą, grąžina rodyklę į naują sąrašo pradžią.
 */
list_t *list_nreverse(list_t *l);

/*
 * list_reverse - apsuka sąrašo kopiją ir ją grąžina.
 */
list_t *list_reverse(const list_t *l);

/*
 * list_copy - padaro sąrašo kopiją ir ją grąžina.
 */
list_t *list_copy(const list_t *l);

/*
 * list_length - grąžina sąrašo ilgį.
 */
long list_length(const list_t *l);

stack_t *stack_new();

/*
 * stack_push - į steką (rodyklę į rodyklę į sąrašą) viršuje įdeda
 * naują narį ir nustato steko rodyklę į jį.
 */
void stack_push(void *val, stack_t *st);

/*
 * stack_pop - iš steko paima naujausio nario verte, atlaisvina jo
 * cons ląstelę, nustato steko rodyklę į senesnį narį.
 */
void *stack_pop(stack_t *st);

#endif
