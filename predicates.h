#ifndef __predicates_h__
#define __predicates_h__

typedef int bool;
#define true 1
#define false 0

bool char_number_p(char c);
bool char_word_p(char c);
bool char_whitespace_p(char c);

bool tok_number_p(char *tok);
bool tok_word_p(char *tok);

#endif
