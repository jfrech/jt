/* Jonathan Frech, 8th, 17th and 18th of April 2020 */
/* Displays the current time in a colorful way using ANSI escape codes, which
   all get wrapped in `%{...}`.
   Intended to be prepended to a prompt, i.e.
       export PROMPT='$(~/.jprompt/jprompt) %M@%n %5~ %# %E'
   when using zsh. */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int rainbow[] = { 196, 202, 208, 214, 220, 226, 190, 154, 118, 82, 46, 47,
    48, 49, 50, 51, 45, 39, 33, 27, 21, 57, 93, 129, 165, 201, 200, 199, 198,
    197, 196 };
const size_t rainbow_n = sizeof (rainbow) / sizeof (int);

int main() {
    time_t _time = time(NULL);
    struct tm *time = localtime(&_time);

    const char *now_fmt = "%H:%M:%S";
    char now[8 + 1];
    strftime(now, sizeof (now), now_fmt, time);

    size_t rainbow_shift = time->tm_sec;
    printf("%%{\33[1m\33[48;5;232m%%}");
    for (size_t j = 0; j < sizeof (now) - 1; j++)
        printf("%%{\33[38;5;%dm%%}%c", rainbow[(j + rainbow_shift) % rainbow_n],
            now[j]);
    printf("%%{\33[0m%%}");

    return EXIT_SUCCESS; }
