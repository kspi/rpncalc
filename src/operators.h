#pragma once
#ifndef operators_h__
#define operators_h__

#include <stdbool.h>

/*
 * op_call - iškviečia operatorių vardu name su steku stk. Plačiau žr.
 * operators.c
 */
bool op_call(const char* name, stack_t *stk);

#endif
