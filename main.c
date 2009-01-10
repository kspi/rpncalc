/*
 * rpncalc - paprastas RPN žymėjimo skaičiuotuvas.
 * 
 * Išleistas į public domain.
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "util.h"
#include "eval.h"


int main(int argc, char **argv)
{
    if (argc < 2) {
        eval(stdin);
    } else {
        FILE* input;
        input = fopen(argv[1], "r");
        if (!input) {
            e_fatal("main: can't open input file '%s': %s\n",
                    argv[1],
                    strerror(errno));
        }
        
        eval(input);
        fclose(input);
    }

    return EXIT_SUCCESS;
}
