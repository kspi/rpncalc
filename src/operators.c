/*
 * operators.c - operatorių aprašai.
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "list.h"
#include "operators.h"
#include "util.h"
#include "numbers.h"


typedef void (*operator_fun_t)(stack_t *stk);

typedef struct {
    char *name;
    int arity;
    operator_fun_t fun;
    const char *description;
} operator_t;



/*
 * DEFOP_1, DEFOP_2 - makrokomandos glaustai apibrėžti operatorius.
 * op_name - funkcijos pavadinimas, o body - ko nors priskyrimas prie
 * result arba {}-blokas.
 */

#define DEFOP_2(op_name, body)                      \
    static void op_name(stack_t *_stk) {            \
        num_t *y = (num_t*)stack_pop(_stk);         \
        num_t *x = (num_t*)stack_pop(_stk);         \
        num_t *result;                              \
        body;                                       \
        num_free(x);                                \
        num_free(y);                                \
        stack_push(result, _stk);                   \
    }

#define DEFOP_1(op_name, body)                  \
    static void op_name(stack_t *_stk) {        \
        num_t *x = (num_t*)stack_pop(_stk);     \
        num_t *result;                          \
        body;                                   \
        num_free(x);                            \
        stack_push(result, _stk);               \
    }

DEFOP_2(op_add, result = num_add(x, y))
DEFOP_2(op_sub, result = num_subtract(x, y))
DEFOP_2(op_mul, result = num_multiply(x, y))
DEFOP_2(op_div, result = num_divide(x, y))
DEFOP_1(op_neg, result = num_negate(x))
DEFOP_1(op_sqrt, result = num_sqrt(x))
DEFOP_1(op_float, result = num_new_real(num_coerce_real(x)))
DEFOP_1(op_round, result = num_new_integer(num_coerce_integer(x)))



/* real_ops.def faile surašyti su double reikšmėmis dirbančių
 * operatorių apibrėžimai op1 ir op2 makrokomandomis. Čia jie
 * paverčiami funkcjiomis.
 */
#define op1(name)                                  \
    static void op_##name (stack_t *_stk) {        \
        num_t *x = (num_t*)stack_pop(_stk);        \
        num_real_t xr = num_coerce_real(x);        \
        num_free(x);                               \
        num_t *result = num_new_real(name(xr));    \
        stack_push(result, _stk);                  \
    }
#define op2(name)                                   \
    static void op_##name (stack_t *_stk) {         \
        num_t *x = (num_t*)stack_pop(_stk);         \
        num_real_t xr = num_coerce_real(x);         \
        num_free(x);                                \
        num_t *y = (num_t*)stack_pop(_stk);         \
        num_real_t yr = num_coerce_real(y);         \
        num_free(y);                                \
        num_t *result = num_new_real(name(yr, xr)); \
        stack_push(result, _stk);                   \
    }
#include "real_ops.def"
#undef op1
#undef op2


/*
 * op_showtype - parodo reikšmės tipą.
 */
static void op_show_type(stack_t *stk) {
    num_t *x = list_first(*stk);
    if (num_typep_integer(x)) {
        printf("integer\n");
    } else if (num_typep_real(x)) {
        printf("real\n");
    } else if (num_typep_fraction(x)) {
        printf("fraction\n");
    } EXHAUSTIVE_IF
}

/*
 * op_show_stack - išveda steko reikšmes nuo naujausios iki
 * seniausios.
 */
static void op_show_stack(stack_t *stk) {
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
static void op_show_last(stack_t *stk) {
    num_print(list_first(*stk));
    printf("\n");
}


static void op_quit(stack_t *stk) {
    exit(EXIT_SUCCESS);
}

static void op_swap(stack_t *stk) {
    void *a = stack_pop(stk);
    void *b = stack_pop(stk);
    stack_push(a, stk);
    stack_push(b, stk);
}

static void op_drop(stack_t *stk) {
    num_free(stack_pop(stk));
}

static void op_dup(stack_t *stk) {
    void *thing = list_first(*stk);
    stack_push(num_copy(thing), stk);
}

static void op_print(stack_t *stk) {
    op_show_last(stk);
    op_drop(stk);
}

static void op_clear(stack_t *stk) {
    while (*stk) {
        op_drop(stk);
    };
}

static void op_help(stack_t *stk);


/*
 * operators - statiškas operatorių aprašymas. Paskutinis narys
 * privalo turėti pavadinimą NULL.
 */
#define OP_SEPARATOR { "\0", 0, NULL, NULL }
const operator_t operators[] = {
    { "+",      2, op_add, "Sudeda skaičius." },
    { "-",      2, op_sub, "Atima skaičius." },
    { "*",      2, op_mul, "Sudaugina skaičius." },
    { "/",      2, op_div, "Padalina skaičius." },
    { "neg",    1, op_neg, "Pakeičia skaičiaus ženklą." },
    { "sqrt",   1, op_sqrt, "Ištraukia šaknį." },
    { "float",  1, op_float, "Paverčia skaičių slankiojančio kablelio skaičiumi." },
    { "round",  1, op_round, "Suapvalina skaičių." },

    OP_SEPARATOR,

#define op1(fun) { #fun, 1, op_##fun, NULL },
#define op2(fun) { #fun, 2, op_##fun, NULL },
#include "real_ops.def"
#undef op1
#undef op2
    
    OP_SEPARATOR,

    { "swap",   2, op_swap, "Sukeičia du viršutinius steko narius vietomis." },
    { "drop",   1, op_drop, "Išima viršutinį steko narį." },
    { "dup",    1, op_dup, "Nukopijuoja viršutinį steko narį." },
    { ".",      1, op_print, "Atspausdina viršutinį steko narį." },
    { "clear",  -1, op_clear, "Ištuština steką." },

    OP_SEPARATOR,

    { "type",   0, op_show_type, "Parodo reikšmės tipą." },
    { "help",   0, op_help, "Parodo operatorių sąrašą su aprašymais." },
    { "stack",  0, op_show_stack, "Parodo steko turinį." },
    { "q",      0, op_quit, "Išjungia programą." },

    OP_SEPARATOR,

    { NULL }
};


static void op_help(stack_t *stk) {
    printf("\nOperatoriai:\n");
    for (int i = 0; operators[i].name; i++) {
        printf("    %s", operators[i].name);

        if (operators[i].arity > 0) {
            printf(" (%d)", operators[i].arity);
        }

        if (operators[i].description) {
            printf(" - %s", operators[i].description);
        }         

        printf("\n");
    }    
}


/*
 * op_call - pagrindinė funkcija čia. Iškviečia operatorių vardu name
 * su steku stk.
 */
bool op_call(const char *name, stack_t *stk) {
    if (*name == '\0') {
        e_fatal("error: op_call: empty operator");
    }
    
    const operator_t *op = NULL;
    for (int i = 0; operators[i].name; i++) {
        if ((*operators[i].name != '\0')
            && (strncmp(name, operators[i].name, MAX_TOKEN_LEN) == 0)) {
            op = &operators[i];
            break;
        }
    }
    if (!op) {
        e_error("op_call: bad operator: '%s'\n", name);
        return false;
    }

    long stk_len = list_length(*stk);
    if (stk_len < op->arity) {
        e_error("op_call: stack underflow for %s\n", op->name);
        return false;
    }

    (*op->fun)(stk);
    return true;
}
