/* Jonathan Frech, 17th and 18th of April 2020 */
/* Displays the 7-bit ASCII table.
   Options include width, base mode and table transposition. */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void usage() {
    fprintf(stderr, "Usage: ascii [-wN] [-hbd] [-t]\n"); }

int main(int argv, char **argc) {
    size_t w = 0; char m = '\0'; bool t = false;
    for (size_t v = 1; v < argv; v++) {
        char *arg = argc[v], *arh, *ari; size_t tp = 1;
        if (*arg++ != '-')
            return usage(), EXIT_FAILURE;
        for (; *arg; arg++) {
            if (!w && *arg == 'w') {
                for (arh = ++arg; '0' <= *arg && *arg <= '9'; arg++)
                    ;
                if (arg == arh)
                    return usage(), EXIT_FAILURE;
                for (ari = --arg; arg >= arh; arg--)
                    w += (*arg - '0') * tp, tp *= 10;
                arg = ari; }
            else if (!m && (*arg == 'h' || *arg == 'b' || *arg == 'd'))
                m = *arg;
            else if (!t && *arg == 't')
                t = true;
            else
                return printf("?%c\n", *arg), usage(), EXIT_FAILURE; } }
    w = w ? w : 8; m = m ? m : 'h';
    size_t h = 0x80 / w + !!(0x80 % w);

    char ascii_names[3 * 0x80], numeric[7] = { '\0' };
    memcpy(ascii_names, "NULSOHSTXETXEOTENQACKBELBS HT LF VT FF CR SO SI DLEDC1"
        "DC2DC3DC4NAKSYNETBCANEM SUBESCFS GS RS US SP ",
        3 * 0x21 * sizeof (char));
    for (char c = 0x21; c < 0x7f; c++) {
        ascii_names[3*c + 0] = ascii_names[3*c + 2] = '\x20';
        ascii_names[3*c + 1] = c; }
    memcpy(ascii_names + 3 * 0x7f, "DEL", 3 * sizeof (char));

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            size_t c = t ? y*w+x : y+h*x, base = 16, basep = 1, pad = 2;
            if (m == 'b')
                base = 2, pad = 7;
            else if (m == 'd')
                base = 10, pad = 3;
            for (size_t j = 0; j < pad; j++) {
                size_t n = (c / basep) % base; basep *= base;
                numeric[pad-1-j] = '0' + (n > 9 ? n + 7 : n); }

            if (c > 0x7f)
                printf("  %*c   ", (int) (pad-1), ' ');
            else
                printf("%s\33[2m%.7s\33[0m %.3s", x ? "  " : "", numeric,
                    ascii_names + 3*c); }
        printf("\n"); }

    return EXIT_SUCCESS; }
