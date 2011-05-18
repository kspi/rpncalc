#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "predicates.h"
#include "util.h"
#include "fraction.h"


#define NUM_TYPES_DEFINED
#include "numbers.h"


void num_set_integer(num_t *num, num_integer_t val) {
    num->type = NUM_INTEGER;
    num->value.integer = val;
}


void num_set_real(num_t *num, num_real_t val) {
    num->type = NUM_REAL;
    num->value.real = val;
}


void num_set_fraction(num_t *num, const num_fraction_t *val) {
    if (fraction_denominator(val) == 1) {
        num_set_integer(num, fraction_numerator(val));
    } else if (fraction_numerator(val) == 0) {
        num_set_integer(num, 0);
    } else {
        num->type = NUM_FRACTION;
        num->value.fraction = val;
    }
}


num_t *num_new_integer(const num_integer_t val) {
    num_t *num = malloc(sizeof(num_t));
    num_set_integer(num, val);
    return num;
}


num_t *num_new_real(const num_real_t val) {
    num_t *num = malloc(sizeof(num_t));
    num_set_real(num, val);
    return num;
}


num_t *num_new_fraction(const num_fraction_t *val) {
    num_t *num = malloc(sizeof(num_t));
    num_set_fraction(num, val);
    return num;
}


bool num_typep_integer(const num_t *num) {
    return num->type == NUM_INTEGER;
}


bool num_typep_real(const num_t *num) {
    return num->type == NUM_REAL;
}


bool num_typep_fraction(const num_t *num) {
    return num->type == NUM_FRACTION;
}


void num_free(num_t *num) {
    if (num_typep_fraction(num)) {
        fraction_free((fraction_t *)num->value.fraction);
    }
    free(num);
}


num_integer_t num_get_integer(const num_t *num) {
    ASSERT(num_typep_integer(num));
    return num->value.integer;
}


num_real_t num_get_real(const num_t *num) {
    ASSERT(num_typep_real(num));
    return num->value.real;
}


const num_fraction_t *num_get_fraction(const num_t *num) {
    ASSERT(num_typep_fraction(num));
    return num->value.fraction;
}


num_integer_t num_coerce_integer(const num_t *num) {
    switch (num->type) {
    case NUM_INTEGER:
        return num->value.integer;
    case NUM_REAL:
        return llrintl(num->value.real);
    case NUM_FRACTION:
        return fraction_to_long(num->value.fraction);
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
}


num_real_t num_coerce_real(const num_t *num) {
    switch (num->type) {
    case NUM_INTEGER:
        return num->value.integer;
    case NUM_REAL:
        return num->value.real;
    case NUM_FRACTION:
        return fraction_to_double(num->value.fraction);
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
}


num_fraction_t *num_coerce_fraction(const num_t *num) {
    switch (num->type) {
    case NUM_INTEGER:
        return fraction_new(num->value.integer, 1);
    case NUM_REAL:
        e_fatal("Coercion of reals to fractions unimplemented.\n");
    case NUM_FRACTION:
        return fraction_copy(num->value.fraction);
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
}


void num_fprint(FILE* stream, const num_t *num) {
    switch (num->type) {
    case NUM_INTEGER:
        fprintf(stream, "%lld", num->value.integer);
        break;
    case NUM_REAL:
        {
            const int NS = 255;
            char s[NS];
            snprintf(s, NS, "%.10Lg", num->value.real);
            s[NS-2] = 0;
            char *p = s;
            while ((*p) && (*p != '.')) p++;
            if (!*p) {
                *p = '.';
                p[1] = 0;
            }
            fprintf(stream, "%s", s);
        }
        break;
    case NUM_FRACTION:
        fraction_fprint(stream, num->value.fraction);
        break;
        
    EXHAUSTIVE_SWITCH
    }
}


void num_print(const num_t *num) {
    num_fprint(stdout, num);
}


num_t *num_from_str(const char *str) {
    char *rest;
    const char *nstr;
    num_t *ret;
    int base = 10;
    
    if (char_in_str_p('#', str)) {
        base = strtol(str, (char **)&nstr, 10);
        nstr++;
    } else {
        nstr = str;
    }
    
    if (any_char_in_str_p(".eE", nstr)) {
        /* Floating point */
        if (base == 10) {
            return num_new_real(strtod(nstr, NULL));
        } else if (base == 16) {
            char *tmp = malloc((strlen(nstr)+3)*sizeof(char));
            sprintf(tmp, "0x%s", nstr);
            ret = num_new_real(strtod(tmp, NULL));
            free(tmp);
            return ret;
        } else {
            e_error("error: floating point literals only support bases of"
                    "10 and 16, tried to use %d\n", base);
            return NULL;
        }
    } else if (char_in_str_p('/', nstr)) { /* fraction */
        /* Fraction */
        return num_new_fraction(fraction_read(nstr, base));
    } else {
        /* Integer */
        ret = num_new_integer(strtoll(nstr, &rest, base));
        if ((rest == nstr) || (rest[0] != '\0')) {
            e_error("error: malformed integer: %s\n", str);
            return NULL;
        } else {
            return ret;
        }
    }
    
    EXHAUSTIVE_FUNCTION
}


num_t *num_copy(const num_t *x) {
    switch (x->type) {
    case NUM_INTEGER:
        return num_new_integer(num_get_integer(x));
    case NUM_REAL:
        return num_new_real(num_get_real(x));
    case NUM_FRACTION:
        return num_new_fraction(fraction_copy(num_get_fraction(x)));
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
}


num_t *num_sqrt(const num_t *x) {
    num_integer_t i;
    num_fraction_t *f;
    
    switch(x->type) {
    case NUM_INTEGER:
        i = num_get_integer(x);
        if (integer_sqrt(i, &i)) {
            return num_new_integer(i);
        } else {
            return num_new_real(sqrt(i));
        }
        
    case NUM_REAL:
        return num_new_real(sqrt(num_get_real(x)));
        
    case NUM_FRACTION:
        f = fraction_sqrt(num_get_fraction(x));
        if (f) {
            return num_new_fraction(f);
        } else {
            return num_new_real(sqrt(num_coerce_real(x)));
        }
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
    
}


num_t *num_add(const num_t *x, const num_t *y) {
    if (num_typep_real(x) || num_typep_real(y)) {
        return num_new_real(num_coerce_real(x) + num_coerce_real(y));
    } else if (num_typep_fraction(x) || num_typep_fraction(y)) {
        num_fraction_t *xf = num_coerce_fraction(x);
        num_fraction_t *yf = num_coerce_fraction(y);
        num_t *ret = num_new_fraction(fraction_add(xf, yf));
        free(xf);
        free(yf);
        return ret;
    } else {
        return num_new_integer(num_get_integer(x) + num_get_integer(y));
    }
}


num_t *num_negate(const num_t *x) {
    switch(x->type) {
    case NUM_INTEGER:
        return num_new_integer(-num_get_integer(x));
    case NUM_REAL:
        return num_new_real(-num_get_real(x));
    case NUM_FRACTION:
        return num_new_fraction(fraction_negate(num_get_fraction(x)));
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
}


num_t *num_subtract(const num_t *x, const num_t *y) {
    num_t *minus_y = num_negate(y);
    num_t *result = num_add(x, minus_y);
    num_free(minus_y);
    return result;
}


num_t *num_multiply(const num_t *x, const num_t *y) {
    if (num_typep_real(x) || num_typep_real(y)) {
        return num_new_real(num_coerce_real(x) * num_coerce_real(y));
    } else if (num_typep_fraction(x) || num_typep_fraction(y)) {
        num_fraction_t *xf = num_coerce_fraction(x);
        num_fraction_t *yf = num_coerce_fraction(y);
        num_t *ret = num_new_fraction(fraction_multiply(xf, yf));
        free(xf);
        free(yf);
        return ret;
    } else {
        return num_new_integer(num_get_integer(x) * num_get_integer(y));
    }
}


bool num_integer_divisor_p(const num_t *x, const num_t *y) {
    return
        num_typep_integer(x) &&
        num_typep_integer(x) &&
        !divisor_p(num_get_integer(x), num_get_integer(y));
}


num_t *num_divide(const num_t *x, const num_t *y) {
    if (num_typep_real(x)
        || num_typep_real(y)) {
        return num_new_real(num_coerce_real(x) / num_coerce_real(y));
    } else if (num_typep_fraction(x)
               || num_typep_fraction(y)
               || num_integer_divisor_p(x, y)) {
        num_fraction_t *xf = num_coerce_fraction(x);
        num_fraction_t *yf = num_coerce_fraction(y);
        num_t *ret = num_new_fraction(fraction_divide(xf, yf));
        free(xf);
        free(yf);
        return ret;
    } else {
        return num_new_integer(num_get_integer(x) / num_get_integer(y));
    }
}

