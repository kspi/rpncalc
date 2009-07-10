#include <stdlib.h>
#include <stdio.h>

#include "numbers.h"
#include "list.h"
#include "predicates.h"
#include "operators.h"
#include "util.h"


char *read_token(char **str) {
    char *buf = malloc(MAX_TOKEN_LEN);
    int buf_i = 0;
    char c;

    while (true) {
        c = **str;

        if ((!char_whitespace_p(c)) && (c != '\0')) {
            /* token char */
            
            buf[buf_i] = c;
            buf_i++;
            *str = *str + 1;

            if (buf_i == MAX_TOKEN_LEN) {
                buf[buf_i] = '\0';
                return buf;
            }
        } else if (c == '\0') {
            /* end of input */
            
            buf[buf_i] = '\0';
            return buf;
        } else {
            /* whitespace */
            
            *str = *str + 1;
            if (buf_i != 0) {
                buf[buf_i] = '\0';
                return buf;
            }
        }
    }
}


void eval(char *str, stack_t *stk) {
    char *tok = NULL;

    while (*str != '\0') {
        tok = read_token(&str);
        if (tok_number_p(tok)) {
            stack_push(num_from_str(tok), stk);
        } else {
            op_call(tok, stk);
        }
        free(tok);
    }
}

void eval_file(FILE *file, stack_t *stk) {
    char *buf = malloc(MAX_LINE_LEN);
    char *line;

    while (true) {
        line = fgets(buf, MAX_LINE_LEN, file);
        if (!line) break;
        
        eval(line, stk);
    }

    free(buf);
}
