/* Jonathan Frech, 2020-04-08, 2020-04-17, 2020-04-18, 2020-11-04 */
/* Builds a zsh prompt. */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int rainbow[] = { 196, 202, 208, 214, 220, 226, 190, 154, 118, 82, 46, 47,
    48, 49, 50, 51, 45, 39, 33, 27, 21, 57, 93, 129, 165, 201, 200, 199, 198,
    197, 196 };
const size_t rainbow_n = sizeof (rainbow) / sizeof (int);

const int pwdLength = 3;

bool streq(char *s, char *z) {
    return *s ? *s == *z && streq(++s, ++z) : !*z ; }

int main(int argc, char **argv) {
    bool flagCloud = false, flagMinimal = false;
    for (size_t j = 1; j < argc; ++j) {
        char *arg = argv[j];

        flagCloud |= streq("--cloud", arg);
        flagMinimal |= streq("--minimal", arg);
    }

    #define BULLET printf(" \xe2\x80\xa2 ")

    if (flagCloud)
        printf("%%{\33[38;5;%dm%%}\xf0\x9f\x8c\xa9 %%{\33[m%%} ", 202);

    if (!flagMinimal) {
        time_t _time = time(NULL);
        struct tm *time = localtime(&_time);

        const char *now_fmt = "%H:%M:%S";
        char now[8 + 1];
        strftime(now, sizeof (now), now_fmt, time);

        size_t rainbow_shift = time->tm_sec;
        printf("%%{\33[1m%%}");
        for (size_t j = 0; j < sizeof (now) - 1; j++)
            printf("%%{\33[38;5;%dm%%}%c",
                rainbow[(j + rainbow_shift) % rainbow_n], now[j]);
        printf("%%{\33[m%%}");
        BULLET;
    }

    if (!flagMinimal) {
        printf("%%n@%%M"); BULLET;
        printf("%%%d~", pwdLength); BULLET;
    }

    printf("%%{%%(?.\33[38;5;154m.\33[38;5;196m)%%}%%?%%{\33[m%%}"); BULLET;

    #undef BULLET

    printf("%%{%%(!.\33[1m\33[38;5;163m.)%%}%%#%%{\33[m%%} %%E");

    return EXIT_SUCCESS;
}
