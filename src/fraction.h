#pragma once
#ifndef fraction_h__
#define fraction_h__

#include <stdio.h>

#ifndef FRACTION_TYPES_DEFINED
typedef int fraction_integer_t;
typedef struct fraction_t fraction_t;
#define FRACTION_TYPES_DEFINED
#endif


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
fraction_integer_t fraction_numerator(fraction_t *frac);
fraction_integer_t fraction_denominator(fraction_t *frac);


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
