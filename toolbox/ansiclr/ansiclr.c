/* Jonathan Frech, 20th of April 2020 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define COLOR_BLOCK(NAMELESS, C, T, F, P) \
    if (NAMELESS) \
        printf("\33[48;5;%dm" T "\33[0m" P, C); \
    else \
        printf("\33[48;5;%dm" F "\33[0m" P, C, C);

void ansi(bool nameless) {
    printf("\n");
    for (int y = 0; y < 4; y++) {
        printf("  ");
        for (int x = 0; x < 8; x++) {
            int c = x +8* !!(y/2);
            printf("\33[1m");
            printf(y / 2 ? "\33[38;5;0m" : "\33[38;5;15m");
            COLOR_BLOCK(y % 2 || nameless, c,
                "            ", "     %2d     ", "       "); }
        printf("\n"); }
    printf("\n");

    for (int r = 0; r < 6; r++)
        for (int y = 0; y < 2; y++) {
            for (int g = 0; g < 6; g++)
                for (int b = 0; b < 6; b++) {
                    int c = 16 + r*6*6 + g*6 + b;
                    printf("\33[1m");
                    printf(g < 3 ? "\33[38;5;15m" : "\33[38;5;0m");
                    COLOR_BLOCK(y || nameless, c, "    ", "%4d", "");
                    if (!((b+1) % 6))
                        printf(" "); }
            printf("\n"); }
    printf("\n");

    for (int y = 0; y < 2; y++) {
        printf("    ");
        for (int k = 0; k < 24; k++) {
            printf("\33[1m");
            printf(k < 12 ? "\33[38;5;15m" : "\33[38;5;0m");
            int c = 16 + 216 + k;
            COLOR_BLOCK(y || nameless, c, "    ", "%4d", "  "); }
        printf("\n"); }
    printf("\n"); }

int main() {
    ansi(false);
    ansi(true); }
