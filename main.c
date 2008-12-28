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

#define MAX_TOKEN_LEN 255

typedef int bool;
#define true 1
#define false 0


bool number_char_p(char c) {
    return ((c == '0') ||
            (c == '1') ||
            (c == '2') ||
            (c == '3') ||
            (c == '4') ||
            (c == '5') ||
            (c == '6') ||
            (c == '7') ||
            (c == '8') ||
            (c == '9'));
}

bool whitespace_char_p(char c) {
    return ((c == ' ')  ||
            (c == '\t') ||
            (c == '\n') ||
            (c == '\r'));
}

bool token_char_p(char c) {
    return (!number_char_p(c)) && (!whitespace_char_p(c));
}

list* read_tokens(FILE* stream)
{
    list* tokens = LIST_END;
    char* token = malloc(MAX_TOKEN_LEN);
    int c_read;
    char c;

    token_pos = 0;
    memset(token, 0, MAX_TOKEN_LEN);

    for (;;) {
        c_read = fgetc(stream);
        if (c_read == EOF) {
            return tokens;
        }
        c = (char)c_read;

        if (!whitespace_char_p) {
            token[token_pos] = c;
            token_pos++;
        } 
    }
}

int main(int argc, char **argv)
{
    int x = 1;
    int y = 2;
    int z = 5;
    list *l = list_cons(&x,
                        list_cons(&y,
                                  list_cons(&z,
                                            LIST_END)));
    
    LIST_PRINT(int, "%d\n", l);

    list_free(l);
    
    return EXIT_SUCCESS;
}
