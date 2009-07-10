/*
 * util - įvairios funkcijos ir konstantos.
 */

#pragma once
#ifndef util_h__
#define util_h__

#define RPNCALC_DEBUG

/*
 * MAX_TOKEN_LEN - ilgiausias galimas žodis. Čia kad išvengtume buffer
 * overflow.
 */
#define MAX_TOKEN_LEN 255


/*
 * MAX_LINE_LEN - ilgiausia eilutė skaitant iš bylos.
 */
#define MAX_LINE_LEN 1024


/*
 * ASSERT - programa nusižudo, jei expr yra false. fun ir name -
 * paskutiniai jos žodžiai.
 */
#define ASSERT(expr)                                                    \
    if (!(expr))                                                        \
        e_fatal("error:%s:%d: assertion failed: %s", __FILE__, __LINE__, #expr)


/*
 * EXHAUSTIVE_SWITCH - vietoje default dalies switch sakinyje, išmeta
 * klaidą, jei yra pasiektas.
 */
#define EXHAUSTIVE_SWITCH                                           \
    default:                                                        \
    e_fatal("error: non exhaustive switch statement in %s:%d\n",    \
            __FILE__,                                               \
            __LINE__);

/*
 * EXHAUSTIVE_FUNCTION - panašiai, kaip EXHAUSTIVE_SWITCH, bet
 * funkcijoms. Dar paslepia warningą. Funkcijos turėtų būti skaičiaus
 * arba rodyklės tipo.
 */
#define EXHAUSTIVE_FUNCTION                                             \
    e_fatal("error: control reached end of non-void function in %s:%d\n", \
            __FILE__,                                                   \
            __LINE__);                                                  \
    return 0;                                                           \


/*
 * e_error - į stderr spausdina pranešimą, naudojama kaip printf.
 */
void e_error(const char *fmt, ...);


/*
 * e_fatal - kaip e_error bet dar ir nužudo programą.
 */
void e_fatal(const char *fmt, ...);


/*
 * gcd - randa dviejų skaičių didžiausią bendrą daliklį.
 */
unsigned long int gcd(unsigned long int u, unsigned long int v);


/*
 * PDEBUG - į stderr spausdina pranešimą, jei įjungtas debug režimas.
 */

#ifdef RPNCALC_DEBUG
#  define PDEBUG(fmt, expr)                                             \
    e_error("DEBUG %s:%u: %s = " fmt "\n", __FILE__, __LINE__, #expr, (expr))
#else
#  define PDEBUG(fmt, expr)
#endif


#endif
