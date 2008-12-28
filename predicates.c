#define _GNU_SOURCE
#include <string.h>
#undef _GNU_SOURCE

#include "util.h"
#include "predicates.h"

bool char_number_p(char c) {
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

bool char_whitespace_p(char c) {
    return ((c == ' ')  ||
            (c == '\t') ||
            (c == '\n') ||
            (c == '\r'));
}

bool char_word_p(char c) {
    return (!char_number_p(c)) && (!char_whitespace_p(c));
}

bool tok_number_p(char *tok) {
    return char_number_p(tok[0]);
}

bool tok_word_p(char *tok) {
    return char_word_p(tok[0]);
}

bool char_in_str_p(char c, char *str) {
    int strlen = strnlen(str, MAX_TOKEN_LEN);
    for (int i = 0; i < strlen; i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}
