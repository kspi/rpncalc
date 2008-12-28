#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "operators.h"
#include "util.h"

typedef void (*operator_fun_t)(stack_t *stk);

typedef struct {
    char *name;
    int arity;
    operator_fun_t fun;
} operator_t;

#define DEFOP_2(op_name, body)                  \
    void op_name(stack_t *_stk) {               \
        long *_res = malloc(sizeof(long));      \
        long *_y = (long*)stack_pop(_stk);      \
        long *_x = (long*)stack_pop(_stk);      \
        long x = *_x;                           \
        long y = *_y;                           \
        long result;                            \
        body;                                   \
        (*_res) = result;                       \
        free(_x);                               \
        free(_y);                               \
        stack_push(_res, _stk);                 \
    }

#define DEFOP_1(op_name, body)                  \
    void op_name(stack_t *_stk) {               \
        long *_res = malloc(sizeof(long));      \
        long *_x = (long*)stack_pop(_stk);      \
        long x = *_x;                           \
        long result;                            \
        body;                                   \
        (*_res) = result;                       \
        free(_x);                               \
        stack_push(_res, _stk);                 \
    }

DEFOP_2(op_add, {
        result = x + y;
    })

DEFOP_2(op_sub, {
        result = x - y;
    })

DEFOP_2(op_mul, {
        result = x * y;
    })

DEFOP_2(op_div, {
        result = x / y;
    })

DEFOP_1(op_sqr, {
        result = x * x;
    })

const int operator_count = 3;
const operator_t operators[] = {
    { "+", 2, &op_add },
    { "-", 2, &op_sub },
    { "*", 2, &op_mul },
    { "/", 2, &op_div },
    { "sqr", 1, &op_sqr }
};

void op_call(const char* name, stack_t *stk) {
    const operator_t *op = NULL;
    for (int i = 0; i < operator_count; i++) {
        if (strcmp(name, operators[i].name) == 0) {
            op = &operators[i];
            break;
        }
    }
    if (!op) {
        e_error("op_call: bad operator: %s\n", name);
        return;
    }

    unsigned long stk_len = list_length(*stk);
    if (stk_len < op->arity) {
        e_fatal("op_call: stack underflow for %s\n", op->name);
    }

    (*op->fun)(stk);
}
