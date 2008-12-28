/*
 * rpncalc - a simple rpn calculator.
 * 
 * Released into the public domain.
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "predicates.h"
#include "operators.h"

#define MAX_TOKEN_LEN 255

char *read_token(FILE* stream) {
    char *buf = malloc(MAX_TOKEN_LEN);
    int buf_i = 0;
    
    int c_read;
    char c;

    for (;;) {
        c_read = fgetc(stream);
        if (c_read == EOF) {
            free(buf);
            return NULL;
        }
        c = (char)c_read;

        if (!char_whitespace_p(c)) {
            buf[buf_i] = c;
            buf_i++;

            if (buf_i == MAX_TOKEN_LEN) {
                buf[buf_i] = '\0';
                return buf;
            }
        } else {
            if (buf_i != 0) {
                buf[buf_i] = '\0';
                return buf;
            }
        }
    }
}

void eval(FILE* stream) {
    list_t *stk = LIST_END;

    char *tok = read_token(stdin);
    while (tok) {
        if (tok_number_p(tok)) {
            long *v = malloc(sizeof(long));
            (*v) = strtol(tok, NULL, 10);
            stack_push(v, &stk);
        } else {
            op_call(tok, &stk);
        }
        free(tok);
        tok = read_token(stdin);
    }
    LIST_PRINT(long, "%d\n", stk);
    LIST_FOREACH(xs, stk) {
        free(list_first(xs));
    }
    list_free(stk);
}

int main(int argc, char **argv)
{
    eval(stdin);
    
    return EXIT_SUCCESS;
}
