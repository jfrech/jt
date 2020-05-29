/* Jonathan Frech, 15th, 17th of April 2020 */
/* fclr -- Finds and displays color definitions of the form `#rrggbb`. */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    if (isatty(STDIN_FILENO))
        return printf("Not processing stdin from a terminal.\n"), EXIT_FAILURE;

    char buffer[6] = { 0 };
    for (int c; (c = getchar()) != EOF; ) {
        for (size_t j = 0; j < 6-1; j++)
            buffer[j] = buffer[j+1];
        buffer[5] = c;

        bool defines_color = true;
        int_fast32_t color = 0;
        for (size_t j = 0; j < 6; j++) {
            c = buffer[j] >= 'a' ? buffer[j] - 32 : buffer[j];
            defines_color &= ('0' <= c && c <= '9') || ('A' <= c && c <= 'F');
            color <<= 4; color |= c > '9' ? c - 'A' + 10 : c - '0'; }
        if (defines_color)
            printf("#%.6s: \33[48;2;%d;%d;%dm      \33[0m\n", buffer,
                (int) ((color >> 16) & 0xff),
                (int) ((color >>  8) & 0xff),
                (int) ((color >>  0) & 0xff)); }

    return EXIT_SUCCESS; }
