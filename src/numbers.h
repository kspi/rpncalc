/*
 * numbers - dinaminių skaičiukų biblioteka.
 *
 * num_t struktūra aprašo skaičių bendrai, kurio gali būtų įvairių
 * tipų, kuriuos visu galima saugoti toje struktūroje. Tik tokiu
 * atveju kiekvienam tipų deriniui reikia aprašinėti atskirai pvz.
 * sudeties funkcijas. Visa tai rašiau, nes ruošiuosi pridėti
 * racionaliuosius skaičius, nes priešingu atveju galima būtų
 * išsisukti su double visur.
 */

#pragma once
#ifndef numbers_h__
#define numbers_h__

#include "predicates.h"
#include "fraction.h"

#ifndef NUM_TYPES_DEFINED
typedef long num_integer_t;
typedef double num_real_t;
typedef fraction_t num_fraction_t;

typedef struct num_t num_t;
#endif

/*
 * Atminties atlaisvinimas
 */
void num_free(num_t *num);

/*
 * Reikšmės nustatymas
 */
void num_set_integer(num_t *num, num_integer_t val);
void num_set_real(num_t *num, num_real_t val);

/*
 * Naujų num_t kūrimas
 */
num_t *num_new_integer(const num_integer_t val);
num_t *num_new_real(const num_real_t val);

/*
 * Tipų tikrinimas
 */
bool num_typep_integer(const num_t *num);
bool num_typep_real(const num_t *num);

/*
 * Griežtas tam tikro tipo grąžinimas
 */
num_integer_t num_get_integer(const num_t *num);
num_real_t num_get_real(const num_t *num);

/*
 * Laisvas tam tikro tipo grąžinimas (pvz. apvalina real, jei prašomas
 * integer)
 */
num_integer_t num_coerce_integer(const num_t *num);
num_real_t num_coerce_real(const num_t *num);

/*
 * Spausdinimas
 */
void num_fprint(FILE* stream, const num_t *num);
void num_print(const num_t *num);

/*
 * num_from_str - paverčia eilutę į skaičių.
 */
num_t *num_from_str(const char *str);

/*
 * num_copy - nukopijuoja skaičiaus struktūrą.
 */
num_t *num_copy(const num_t *x);

/*
 * Matematinės operacijos
 */
num_t *num_add(const num_t *x, const num_t *y);
num_t *num_negate(const num_t *x);
num_t *num_subtract(const num_t *x, const num_t *y);
num_t *num_multiply(const num_t *x, const num_t *y);
num_t *num_divide(const num_t *x, const num_t *y);

#endif
