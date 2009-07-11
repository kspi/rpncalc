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



void print_usage(const char *name) {
    printf(
        "Naudojimas: \n"
        "    %s [BYLA1] [BYLA2] ...\n"
        "    %s --help\n"
        "    %s --version\n"
        "\n"
        "BYLA gali būti -, tada skaitoma iš stdin. Jei neduota nei viena byla,\n"
        "tai paleidžiamas interaktyvus režimas.\n",
        name, name, name);
    exit(0);
}


void print_version() {
    printf("rpncalc " RPNCALC_VERSION "\n");
    exit(0);
}


const char *stdin_filename = "<stdin>";

int main(int argc, char **argv)
{
    char *line = NULL;
    stack_t *stk = stack_new();

    if (argc > 1) {
        if (argc == 2) {
            if (strcmp("--help", argv[1]) == 0) {
                print_usage(argv[0]);
            } else if (strcmp("--version", argv[1]) == 0) {
                print_version();
            }
        }
        
        while (argc > 1) {
            FILE *input;
            char *filename;

            if (strncmp(argv[1], "-", 2) == 0) {
                input = stdin;
                filename = (char *)stdin_filename;
            } else {
                filename = argv[1];
                input = fopen(argv[1], "r");
            }
            
            if (!input) {
                e_fatal("main: can't open input file '%s': %s\n",
                        argv[1],
                        strerror(errno));
            }
            eval_file(input, filename, stk);
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
                eval("stack", stk);
                free(line);
            }
        } else {
            eval_file(stdin, stdin_filename, stk);
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
