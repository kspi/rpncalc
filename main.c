/*
 * rpncalc - paprastas RPN žymėjimo skaičiuotuvas.
 * 
 * Išleistas į public domain.
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "predicates.h"
#include "operators.h"
#include "util.h"
#include "numbers.h"


/*
 * read_token - perskaito iš stream vieną žodį (žodžiai skiriami
 * whitespace, žr. predicates.c, char_whitespace_p), ir jį grąžina.
 * Vietą alokuoja pati.
 */
char *read_token(FILE* stream) {
    char *buf = malloc(MAX_TOKEN_LEN); int buf_i = 0;
    
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

/*
 * eval - iš stream skaito žodžius ir, jei jie skaičiai, įdeda į
 * steką, o priešingu atveju bando kviesti atitinkamą operatorių.
 */
void eval(FILE* stream) {
    list_t *stk = LIST_END;

    char *tok = read_token(stdin);
    while (tok) {
        if (tok_number_p(tok)) {
            stack_push(num_from_str(tok), &stk);
        } else {
            op_call(tok, &stk);
        }
        free(tok);
        tok = read_token(stdin);
    }
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
