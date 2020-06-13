/* Jonathan Frech, 30th of April, 3rd, 5th of June 2020 */

#include <stdlib.h>
#include <stdio.h>

typedef int color_t;

const char *color_identifiers[8] = {
    "text", "faint", "grayA", "grayB",
    "accentA", "accentB", "accentC", "accentD" };

#define N_SCHEMES 3
const color_t schemes[N_SCHEMES][8] = {
    /* red-yellow */
    { 255, 236, 240, 245,
      160, 202, 208, 178, },

    /* blue-turquise-green */
    { 255, 236, 240, 245,
       26,  30,  76, 118, },

    /* sunny */
    { 255, 240, 166, 172,
      228, 226, 225, 219, },
};

int main(int argc, char **argv) {
    int _s = argc > 1 ? atoi(argv[1]) : 0;
    size_t s = (size_t) (_s < 0 ? 0 : _s > N_SCHEMES-1 ? N_SCHEMES-1 : _s);
    const color_t *scheme = schemes[s];

    for (size_t y = 0; y < 2; y++)
        for (size_t l = 0; l < 2; l++) {
            for (size_t x = 0; x < 4; x++)
                fprintf(stderr, "\33[48;5;%dm    \33[0m", scheme[
                    !y && x < 2 ? l : x +4* y]);
            fprintf(stderr, "\n"); }

    color_t unknown = 14, faintCC = scheme[1] - 1, faintCH = faintCC - 2;
    faintCC = faintCC < 232 ? 232 : faintCC;
    faintCH = faintCH < 232 ? 232 : faintCH;

    printf("sed 's/%%unknown/%d/g'", unknown);
    printf(" | sed 's/%%faintCC/%d/g'", faintCC);
    printf(" | sed 's/%%faintCH/%d/g'", faintCH);
    printf(" | sed 's/%%select/%d/g'", 250);
    for (size_t j = 0; j < 8; j++)
        printf(" | sed 's/%%%s/%d/g'", color_identifiers[j], scheme[j]);
    printf("\n");

    return EXIT_SUCCESS; }
