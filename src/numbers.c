#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "predicates.h"
#include "util.h"
#include "fraction.h"
#include "frap.h"

typedef long num_integer_t;
typedef double num_real_t;
typedef fraction_t num_fraction_t;


enum num_type_enum {
    NUM_INTEGER,
    NUM_REAL,
    NUM_FRACTION
};

typedef struct {
    enum num_type_enum type;
    union {
        num_integer_t integer;
        num_real_t real;
        num_fraction_t *fraction;
    } value;
} num_t;

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


void num_set_fraction(num_t *num, num_fraction_t *val) {
    if (fraction_denominator(val) == 1) {
        num_set_integer(num, fraction_numerator(val));
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


num_t *num_new_fraction(num_fraction_t *val) {
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
        fraction_free(num->value.fraction);
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


num_fraction_t *num_get_fraction(const num_t *num) {
    ASSERT(num_typep_fraction(num));
    return num->value.fraction;
}


num_integer_t num_coerce_integer(const num_t *num) {
    switch (num->type) {
    case NUM_INTEGER:
        return num->value.integer;
    case NUM_REAL:
        return round(num->value.real);
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
        return frap(num->value.real);
    case NUM_FRACTION:
        return num->value.fraction;
        
    EXHAUSTIVE_SWITCH
    }
    EXHAUSTIVE_FUNCTION
}


void num_fprint(FILE* stream, const num_t *num) {
    switch (num->type) {
    case NUM_INTEGER:
        fprintf(stream, "%ld", num->value.integer);
        break;
    case NUM_REAL:
        fprintf(stream, "%g", num->value.real);
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
    if (char_in_str_p('.', str)) {
        return num_new_real(strtod(str, NULL));
    } else if (char_in_str_p('/', str)) {
        return num_new_fraction(fraction_read(str));
    } else {
        return num_new_integer(strtol(str, NULL, 10));
    }
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

num_t *num_add(const num_t *x, const num_t *y) {
    if (num_typep_real(x) || num_typep_real(y)) {
        return num_new_real(num_coerce_real(x) + num_coerce_real(y));
    } else if (num_typep_fraction(x) || num_typep_fraction(y)) {
        return num_new_fraction(fraction_add(num_coerce_fraction(x),
                                             num_coerce_fraction(y)));
    } else {
        return num_new_integer(num_get_integer(x) + num_get_integer(y));
    }
}

num_t *num_negate(const num_t *x) {
    switch(x->type) {
    case NUM_INTEGER:
        return num_new_integer(-num_get_integer(x));
        break;
    case NUM_REAL:
        return num_new_real(-num_get_real(x));
        break;
    case NUM_FRACTION:
        return num_new_fraction(fraction_negate(num_get_fraction(x)));
        break;
        
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
        return num_new_fraction(fraction_multiply(num_coerce_fraction(x),
                                                  num_coerce_fraction(y)));
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
        return num_new_fraction(fraction_divide(num_coerce_fraction(x),
                                                num_coerce_fraction(y)));
    } else {
        return num_new_integer(num_get_integer(x) / num_get_integer(y));
    }
}
