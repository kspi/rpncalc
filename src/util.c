#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>

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


bool integer_sqrt(long int i, long int *out) {
    long int root = sqrt(i);
    if (root * root == i) {
        *out = root;
        return true;
    } else {
        return false;
    }    
}


/* Kodas paimtas iš http://en.wikipedia.org/wiki/Binary_GCD_algorithm#Implementation */
unsigned long int gcd(unsigned long int u, unsigned long int v) {
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
            unsigned long int diff = u - v;
            u = v;
            v = diff;
        }
        v >>= 1;
    } while (v != 0);
 
    return u << shift;
}
