/*
 * predicates - įvairios funkcijos grąžinančios bool. Daugelio jų
 * veikimas turėtų būti savaime suprantamas.
 */

#pragma once
#ifndef predicates_h__
#define predicates_h__

#include <stdbool.h>

bool char_number_p(char c);
bool char_word_p(char c);
bool char_whitespace_p(char c);

bool tok_number_p(const char *tok);
bool tok_word_p(const char *tok);

bool char_in_str_p(char c, const char *str);

bool divisor_p(long x, long y);

#endif
