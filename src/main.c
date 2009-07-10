/*
 * rpncalc - paprastas RPN žymėjimo skaičiuotuvas.
 * 
 * Išleistas pagal GNU General Public License licenzijos trečią
 * versiją.
 *
 * Released under the GNU General Public License version 3.
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "util.h"
#include "eval.h"
#include "predicates.h"
#include "list.h"



int main(int argc, char **argv)
{
    char *line = NULL;
    stack_t *stk = stack_new();

    if (argc > 1) {
        while (argc > 1) {
            FILE *input;

            if (strncmp(argv[1], "-", 2) == 0) {
                input = stdin;
            } else {
                input = fopen(argv[1], "r");
            }
            
            if (!input) {
                e_fatal("main: can't open input file '%s': %s\n",
                        argv[1],
                        strerror(errno));
            }
            eval_file(input, stk);
            fclose(input);
            
            argc--;
            argv++;
        }
    } else {
        if (isatty(0)) {        /* 0 - fd of stdin */
            while(true) {
                line = readline("> ");
                if (line == NULL) {
                    return EXIT_SUCCESS;
                }
                eval(line, stk);
                add_history(line);
                free(line);
            }
        } else {
            eval_file(stdin, stk);
        }
    }
        
    /* CLEANUP */
    LIST_FOREACH(xs, *stk) {
        free(list_first(xs));
    }
    list_free(*stk);
    free(stk);

    return EXIT_SUCCESS;
}
