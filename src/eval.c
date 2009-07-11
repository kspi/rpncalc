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
            if (*buf == '\0') {
                free(buf);
                return NULL;
            } else {
                return buf;
            }
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


bool eval(char *str, stack_t *stk) {
    char *tok = NULL;

    while (*str != '\0') {
        tok = read_token(&str);
        if (!tok) break;
        
        if (tok_number_p(tok)) {
            stack_push(num_from_str(tok), stk);
        } else {
            if (!op_call(tok, stk)) {
                free(tok);
                return false;
            }
        }
        free(tok);
    }

    return true;
}

void eval_file(FILE *file, const char *filename, stack_t *stk) {
    char *buf = malloc(MAX_LINE_LEN);
    char *line;
    int linenr = 1;

    while (true) {
        line = fgets(buf, MAX_LINE_LEN, file);
        if (!line) break;
        
        if (!eval(line, stk)) {
            e_fatal("error in input at %s:%d\n", filename, linenr);
        }
        
        linenr++;
    }

    free(buf);
}
