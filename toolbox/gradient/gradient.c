/* Jonathan Frech, 4th of June 2020 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>

#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

void terminal_dimensions(size_t *h, size_t *w) {
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    *h = (size_t) win.ws_row; *w = (size_t) win.ws_col; }

int run_visual(int (*f)()) {
    static struct termios restore, visual;
    tcgetattr(STDIN_FILENO, &restore);
    visual = restore;

    visual.c_lflag &= ~ICANON & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &visual);

    printf("\33[?47h");
    int exit_status = f();
    printf("\33[?47l");

    tcsetattr(STDIN_FILENO, TCSANOW, &restore);
    return exit_status; }

void clear_screen() {
    printf("\33[2J\33[H"); }

typedef int_fast32_t color_t;
typedef struct { size_t h, w; color_t *data; } pixmap_t;

void trisect_color(color_t c, uint8_t *r, uint8_t *g, uint8_t *b) {
    *r = (c >> 16) & 0xff; *g = (c >> 8) & 0xff; *b = c & 0xff; }

void render_pixmap(pixmap_t pixmap) {
    size_t term_h, term_w;
    terminal_dimensions(&term_h, &term_w);

    size_t h = pixmap.h, w = pixmap.w;

    clear_screen();
    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            uint8_t r, g, b;
            trisect_color(pixmap.data[y *pixmap.w+ x], &r, &g, &b);
            printf("\33[48;2;%d;%d;%dm  \33[0m", (int) r, (int) g, (int) b); }
        printf("\n"); } }

pixmap_t gradient() {
    size_t h, w; terminal_dimensions(&h, &w);
    h -= 1; w /= 2;

    pixmap_t pixmap = (pixmap_t) { .h = h, .w = w, .data = NULL };

    pixmap.data = malloc(h * w * sizeof *pixmap.data);
    if (!pixmap.data)
        return pixmap;

    color_t r = rand() & 0xffffff;
    for (size_t y = 0; y < pixmap.h; y++)
        for (size_t x = 0; x < pixmap.w; x++)
            pixmap.data[y *pixmap.w+ x] = (r + x-y) & 0xffffff;

    return pixmap; }


int _main() {
    int c = -1;
    do {
        pixmap_t pixmap = gradient();
        if (!pixmap.data)
            return EXIT_FAILURE;
        render_pixmap(pixmap);
        free(pixmap.data);
    } while ((c = getchar()) != 'q');

    return EXIT_SUCCESS; }

int main() {
    return run_visual(_main); }
