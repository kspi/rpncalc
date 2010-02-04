#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "predicates.h"
#include "util.h"


#include "fraction.h"


fraction_t *fraction_nnormalize(fraction_t *frac) {
    fraction_integer_t sign, num, den, anum, aden;
    unsigned long int agcd;

    num = frac->numerator;
    den = frac->denominator;
    
    anum = labs(num);
    aden = labs(den);
    
    sign = (num/anum)/(den/aden);

    agcd = gcd((unsigned long int)anum, (unsigned long int)aden);

    frac->numerator = sign * anum / (fraction_integer_t)agcd;
    frac->denominator = aden / (fraction_integer_t)agcd;
    
    return frac;
}


fraction_t *fraction_new(fraction_integer_t numerator, fraction_integer_t denominator) {
    fraction_t *frac = malloc(sizeof(fraction_t));
    frac->numerator = numerator;
    frac->denominator = denominator;
    
    fraction_nnormalize(frac);
    return frac;
}


void fraction_free(fraction_t *frac) {
    free(frac);
}


fraction_t *fraction_read(const char *str, int base) {
    char *endptr;
    fraction_integer_t num, den;

    ASSERT(str);
    num = strtol(str, &endptr, base);

    ASSERT(endptr);
    ASSERT(*endptr == '/');
    endptr++;
    den = strtol(endptr, NULL, base);

    return fraction_new(num, den);
}


void fraction_fprint(FILE *stream, const fraction_t *frac) {
    fprintf(stream, "%lld/%lld", frac->numerator, frac->denominator);
}


fraction_t *fraction_copy(const fraction_t *frac) {
    return fraction_new(frac->numerator, frac->denominator);
}


fraction_integer_t fraction_numerator(const fraction_t *frac) {
    return frac->numerator;
}


fraction_integer_t fraction_denominator(const fraction_t *frac) {
    return frac->denominator;
}


fraction_t *fraction_sqrt(const fraction_t *x) {
    fraction_integer_t num, den;

    num = x->numerator;
    den = x->denominator;

    if (integer_sqrt(num, &num) && integer_sqrt(den, &den)) {
        return fraction_new(num, den);
    } else {
        return NULL;
    }
}


fraction_t *fraction_add(const fraction_t *x, const fraction_t *y) {
    fraction_integer_t nnum, nden;
    nnum = x->numerator * y->denominator + y->numerator * x->denominator;
    nden = x->denominator * y->denominator;
    return fraction_new(nnum, nden);
}


fraction_t *fraction_negate(const fraction_t *frac) {
    return fraction_new(-frac->numerator,
                        frac->denominator);
}


fraction_t *fraction_subtract(const fraction_t *x, const fraction_t *y) {
    fraction_t *minus_y = fraction_negate(y);
    fraction_t *result = fraction_add(x, minus_y);
    fraction_free(minus_y);
    return result;
}


fraction_t *fraction_multiply(const fraction_t *x, const fraction_t *y) {
    return fraction_new(x->numerator * y->numerator,
                        x->denominator * y->denominator);
}


fraction_t *fraction_divide(const fraction_t *x, const fraction_t *y) {
    return fraction_new(x->numerator * y->denominator,
                        x->denominator * y->numerator);
}


double fraction_to_double(const fraction_t *frac) {
    return ((double)frac->numerator) / ((double)frac->denominator);
}


long fraction_to_long(const fraction_t *frac) {
    return ((long)frac->numerator) / ((long)frac->denominator);
}

