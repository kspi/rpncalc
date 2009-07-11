#pragma once
#ifndef eval_h__
#define eval_h__

#include <stdbool.h>

#include "list.h"


/*
 * read_token - perskaito iš *str vieną žodį (žodžiai skiriami
 * whitespace, žr. predicates.c, char_whitespace_p), ir jį grąžina.
 * Pakeičia str taip, kad ji (rodyklė) rodytų į sekančio žodžio
 * pradžią. Vietą alokuoja pati.
 */
char *read_token(char **str);


/*
 * eval - iš str skaito žodžius ir, jei jie skaičiai, įdeda į
 * steką, o priešingu atveju bando kviesti atitinkamą operatorių.
 */
bool eval(char *str, stack_t *stk);


/*
 * eval_file - kviečia eval kiekvienai eilutei iš bylos.
 */
void eval_file(FILE *file, const char *filename, stack_t *stk);


#endif
