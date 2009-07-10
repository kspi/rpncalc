#pragma once
#ifndef fraction_h__
#define fraction_h__

#include <stdio.h>

typedef long fraction_integer_t;

typedef struct {
    fraction_integer_t numerator;
    fraction_integer_t denominator;
} fraction_t;

/*
 * fraction_new - sukuria naują trupmenos struktūrą su duotu skaitikliu ir vardikliu.
 */
fraction_t *fraction_new(fraction_integer_t numerator, fraction_integer_t denominator);


/*
 * fraction_free - atlaisvina struktūrą.
 */
void fraction_free(fraction_t *frac);


/*
 * fraction_read - paverčia eilutę į trupmeną.
 */
fraction_t *fraction_read(const char *str);


/*
 * fraction_fprint - spausdina trupmeną į FILE*.
 */
void fraction_fprint(FILE *stream, const fraction_t *frac);


/*
 * fraction_copy - padaro trupmenos kopiją.
 */
fraction_t *fraction_copy(const fraction_t *frac);


/*
 * Vardiklis ir skaitiklis:
 */
fraction_integer_t fraction_numerator(const fraction_t *frac);
fraction_integer_t fraction_denominator(const fraction_t *frac);



/*
 * fraction_sqrt - jei iš x traukiasi šaknis, grąžina ją, o priešingu
 * atveju NULL.
 */
fraction_t *fraction_sqrt(const fraction_t *x);

/*
 * Aritmetika:
 */
fraction_t *fraction_add(const fraction_t *x, const fraction_t *y);
fraction_t *fraction_negate(const fraction_t *frac);
fraction_t *fraction_subtract(const fraction_t *x, const fraction_t *y);
fraction_t *fraction_multiply(const fraction_t *x, const fraction_t *y);
fraction_t *fraction_divide(const fraction_t *x, const fraction_t *y);


/*
 * Vertimai:
 */
double fraction_to_double(const fraction_t *frac);
long fraction_to_long(const fraction_t *frac);

#endif
