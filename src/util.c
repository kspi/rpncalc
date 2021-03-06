#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

#include "util.h"

void e_error(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}


void e_fatal(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);

    exit(EXIT_FAILURE);
}


bool integer_sqrt(util_integer_t i, util_integer_t *out) {
    util_integer_t root = sqrt(i);
    if (root * root == i) {
        if (out) *out = root;
        return true;
    } else {
        return false;
    }    
}


/* Kodas paimtas iš http://en.wikipedia.org/wiki/Binary_GCD_algorithm#Implementation */
unsigned long long gcd(unsigned long long u, unsigned long long v) {
    int shift;
 
    /* GCD(0,x) := x */
    if (u == 0 || v == 0)
        return u | v;
 
    /* Let shift := lg K, where K is the greatest power of 2
       dividing both u and v. */
    for (shift = 0; ((u | v) & 1) == 0; ++shift) {
        u >>= 1;
        v >>= 1;
    }
 
    while ((u & 1) == 0)
        u >>= 1;
 
    /* From here on, u is always odd. */
    do {
        while ((v & 1) == 0)  /* Loop X */
            v >>= 1;
 
        /* Now u and v are both odd, so diff(u, v) is even.
           Let u = min(u, v), v = diff(u, v)/2. */
        if (u < v) {
            v -= u;
        } else {
            unsigned long long diff = u - v;
            u = v;
            v = diff;
        }
        v >>= 1;
    } while (v != 0);
 
    return u << shift;
}
