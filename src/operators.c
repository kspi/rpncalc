/*
 * operators.c - operatorių aprašai.
 */

#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "operators.h"
#include "util.h"
#include "numbers.h"


typedef void (*operator_fun_t)(stack_t *stk);

typedef struct {
    char *name;
    int arity;
    operator_fun_t fun;
} operator_t;



/*
 * DEFOP_1, DEFOP_2 - makrokomandos glaustai apibrėžti operatorius.
 * op_name - funkcijos pavadinimas, o body - ko nors priskyrimas prie
 * result arba {}-blokas.
 */

#define DEFOP_2(op_name, body)                  \
    void op_name(stack_t *_stk) {               \
        num_t *y = (num_t*)stack_pop(_stk);     \
        num_t *x = (num_t*)stack_pop(_stk);     \
        num_t *result;                          \
        body;                                   \
        num_free(x);                                \
        num_free(y);                                \
        stack_push(result, _stk);               \
    }

#define DEFOP_1(op_name, body)                  \
    void op_name(stack_t *_stk) {               \
        num_t *x = (num_t*)stack_pop(_stk);     \
        num_t *result;                          \
        body;                                   \
        num_free(x);                                \
        stack_push(result, _stk);               \
    }

DEFOP_2(op_add, result = num_add(x, y))
DEFOP_2(op_sub, result = num_subtract(x, y))
DEFOP_2(op_mul, result = num_multiply(x, y))
DEFOP_2(op_div, result = num_divide(x, y))
DEFOP_1(op_neg, result = num_negate(x))
DEFOP_1(op_sqrt, result = num_sqrt(x))


/*
 * op_show_stack - išveda steko reikšmes nuo naujausios iki
 * seniausios.
 */
void op_show_stack(stack_t *stk) {
    printf("stack: ");
    list_t *list = list_reverse(*stk);
    LIST_FOREACH(xs, list) {
        num_print(list_first(xs));
        printf(" ");
    }
    list_free(list);
    printf("\n");
}


/*
 * op_show_last - išveda naujausią steko reikšmę.
 */
void op_show_last(stack_t *stk) {
    num_print(list_first(*stk));
    printf("\n");
}


void op_quit(stack_t *stk) {
    exit(EXIT_SUCCESS);
}


void op_nothing(stack_t *stk) {}


void op_drop(stack_t *stk) {
    num_free(stack_pop(stk));
}

void op_dup(stack_t *stk) {
    void *thing = list_first(*stk);
    stack_push(num_copy(thing), stk);
}

void op_print(stack_t *stk) {
    op_show_last(stk);
    op_drop(stk);
}


/*
 * operators - statiškas operatorių aprašymas. Paskutinis narys
 * privalo turėti pavadinimą NULL.
 */
const operator_t operators[] = {
    { "+", 2, op_add },
    { "-", 2, op_sub },
    { "*", 2, op_mul },
    { "/", 2, op_div },
    { "neg", 1, op_neg },
    { "sqrt", 1, op_sqrt },

    { "drop", 0, op_drop },
    { "dup", 1, op_dup },

    { "=", 1, op_show_last },
    { ".", 1, op_print },
    { "stack", 0, op_show_stack },
    { "q", 0, op_quit },
    { "", 0, op_nothing },

    { NULL, 0, NULL }
};


/*
 * op_call - pagrindinė funkcija čia. Iškviečia operatorių vardu name
 * su steku stk.
 */
void op_call(const char* name, stack_t *stk) {
    const operator_t *op = NULL;
    for (int i = 0; operators[i].name; i++) {
        if (strncmp(name, operators[i].name, MAX_TOKEN_LEN) == 0) {
            op = &operators[i];
            break;
        }
    }
    if (!op) {
        e_error("op_call: bad operator: '%s'\n", name);
        return;
    }

    long stk_len = list_length(*stk);
    if (stk_len < op->arity) {
        e_fatal("op_call: stack underflow for %s\n", op->name);
    }

    (*op->fun)(stk);
}
