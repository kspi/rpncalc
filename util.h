/*
 * util - įvairios funkcijos ir konstantos.
 */

#pragma once
#ifndef util_h__
#define util_h__


/*
 * MAX_TOKEN_LEN - ilgiausias galimas žodis. Čia kad išvengtume buffer
 * overflow.
 */
#define MAX_TOKEN_LEN 255


/*
 * ASSERT - programa nusižudo, jei expr yra false. fun ir name -
 * paskutiniai jos žodžiai.
 */
#define ASSERT(fun, name, expr)                         \
    if (!(expr))                                        \
        e_fatal("%s: assertion failed: %s", fun, name)

#define EXHAUSTIVE_SWITCH                                           \
    default:                                                        \
    e_fatal("error: non exhaustive switch statement in %s:%d\n",    \
            __FILE__,                                               \
            __LINE__);

/*
 * e_error - į stderr spausdina pranešimą, naudojama kaip printf.
 */
void e_error(const char *fmt, ...);

/*
 * e_fatal - kaip e_error bet dar ir nužudo programą.
 */
void e_fatal(const char *fmt, ...);

#endif
