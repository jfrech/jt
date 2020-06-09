/* Jonathan Frech, 9th of June 2020 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


typedef enum { UNKNOWN, AIR, WALL, START, END } tile_t;
typedef struct { size_t w, h; tile_t *data; } maze_t;


maze_t *malloc_maze(size_t w, size_t h) {
    tile_t *data = malloc(w * h * sizeof *data);
    if (!data) return NULL;
    for (size_t j = 0; j < w * h; j++)
        data[j] = UNKNOWN;

    maze_t *maze = malloc(sizeof *maze);
    if (!maze) return free(data), NULL;

    maze->data = data, maze->w = w, maze->h = h;
    return maze; }

void free_maze(maze_t *maze) {
    free(maze->data), free(maze); }

void add_border(maze_t *maze) {
    for (size_t x = 0; x < maze->w; x++)
        maze->data[x + maze->w* 0]
            = maze->data[x + maze->w* (maze->h-1)] = WALL;
    for (size_t y = 0; y < maze->h; y++)
        maze->data[0 + maze->w* y]
            = maze->data[(maze->w-1) + maze->w* y] = WALL; }

size_t add_start_and_end(maze_t *maze) {
    size_t s = rand() % (maze->w-2) + 1;
    size_t e = rand() % (maze->w-2) + 1;
    maze->data[s + maze->w* 0] = START;
    maze->data[e + maze->w* (maze->h-1)] = END;
    return s; }

void print_maze(maze_t *maze) {
    for (size_t y = 0; y < maze->h; y++) {
        for (size_t x = 0; x < maze->w; x++) {
            tile_t t = maze->data[x +maze->w* y];
            if (t == AIR || t == START || t == END)
                printf("\33[47m  \33[0m");
            else if (t == WALL)
                printf("\33[100m  \33[0m");
            /*else if (t == START)
                printf("\33[102ms@\33[0m");
            else if (t == END)
                printf("\33[102m@e\33[0m");*/
            else if (t == UNKNOWN)
                printf("\33[40m? \33[0m");
            else
                printf("\33[101m??\33[0m");
        }
        printf("\n"); } }

void print_maze_ppm(maze_t *maze) {
    printf("P1\n%zu %zu\n", maze->w, maze->h);
    for (size_t y = 0; y < maze->h; y++) {
        for (size_t x = 0; x < maze->w; x++)
            printf("%s%d", x ? " " : "", (maze->data[x +maze->w* y] == WALL));
        printf("\n"); } }

void surrounding(size_t x, size_t y, maze_t *maze,
        tile_t *u, tile_t *d, tile_t *l, tile_t *r) {
    *u = maze->data[ x    + maze->w* (y-1)];
    *d = maze->data[ x    + maze->w* (y+1)];
    *l = maze->data[(x-1) + maze->w*  y   ];
    *r = maze->data[(x+1) + maze->w*  y   ]; }

size_t number_of_surrounding_air(size_t x, size_t y, maze_t *maze) {
    tile_t surrounding[8] = {
        maze->data[ (x-1) + maze->w* (y  )],
        maze->data[ (x+1) + maze->w* (y  )],
        maze->data[ (x  ) + maze->w* (y-1)],
        maze->data[ (x  ) + maze->w* (y+1)],

        maze->data[ (x-1) + maze->w* (y-1)],
        maze->data[ (x-1) + maze->w* (y+1)],
        maze->data[ (x+1) + maze->w* (y-1)],
        maze->data[ (x+1) + maze->w* (y+1)],
    };

    size_t n = 0;
    for (size_t j = 0; j < 8; j++)
        n += surrounding[j] == AIR;
    return n; }

bool does_reach_end(size_t x, size_t y, maze_t *maze) {
    tile_t u, d, l, r;
    surrounding(x, y, maze, &u, &d, &l, &r);
    return u == END || d == END || l == END || r == END; }

void swap(char *arr, size_t j, size_t i) {
    char tmp = arr[j]; arr[j] = arr[i]; arr[i] = tmp; }
void shuffle(char *arr, size_t len) {
    for (size_t j = 0; j < len; j++)
        swap(arr, j, j + rand() % (len - j)); }

bool FOUND = false;
bool walk(size_t x, size_t y, maze_t *maze) {
    maze->data[x +maze->w* y] = AIR;

    if (does_reach_end(x, y, maze))
        return FOUND = true;

    char dirs[4] = { 'u', 'd', 'l', 'r' };
    shuffle(dirs, 4);
    for (size_t j = 0; j < 4; j++) {
        size_t x_ = x, y_ = y, n = 0;
        switch (dirs[j]) {
            case 'u':
                y_--;
                n += maze->data[ (x_-1) +maze->w* (y_+1)] == AIR;
                n += maze->data[ (x_  ) +maze->w* (y_+1)] == AIR;
                n += maze->data[ (x_+1) +maze->w* (y_+1)] == AIR;
                break;
            case 'd':
                y_++;
                n += maze->data[ (x_-1) +maze->w* (y_-1)] == AIR;
                n += maze->data[ (x_  ) +maze->w* (y_-1)] == AIR;
                n += maze->data[ (x_+1) +maze->w* (y_-1)] == AIR;
                break;
            case 'l':
                x_--;
                n += maze->data[ (x_+1) +maze->w* (y_-1)] == AIR;
                n += maze->data[ (x_+1) +maze->w* (y_  )] == AIR;
                n += maze->data[ (x_+1) +maze->w* (y_+1)] == AIR;
                break;
            case 'r':
                x_++;
                n += maze->data[ (x_-1) +maze->w* (y_-1)] == AIR;
                n += maze->data[ (x_-1) +maze->w* (y_  )] == AIR;
                n += maze->data[ (x_-1) +maze->w* (y_+1)] == AIR;
                break;
        }
        if (maze->data[x_ +maze->w* y_] != UNKNOWN)
            continue;
        if (number_of_surrounding_air(x_, y_, maze) - n == 0) {
            if (walk(x_, y_, maze))
                break; }
    }

    return false; }

void mystify_air(maze_t *maze) {
    for (size_t y = 0; y < maze->h; y++)
        for (size_t x = 0; x < maze->w; x++)
            if (maze->data[x +maze->w* y] == AIR)
                maze->data[x +maze->w* y] = UNKNOWN; }

void turn_unknowns_into_walls(maze_t *maze) {
    for (size_t j = 0; j < maze->w*maze->h; j++)
        if (maze->data[j] == UNKNOWN)
            maze->data[j] = WALL; }

void print_usage() {
    printf("Usage: maze [--ppm] <w> <h>\n");}

int main(int argc, char **argv) {
    if (argc < 2) return print_usage(), EXIT_FAILURE;
    bool ppm = strcmp(argv[1], "--ppm") == 0;
    long w_, h_;
    if (ppm) {
        if (argc != 4) return print_usage(), EXIT_FAILURE;
        w_ = atol(argv[2]), h_ = atol(argv[3]); }
    else {
        if (argc != 3) return print_usage(), EXIT_FAILURE;
        w_ = atol(argv[1]), h_ = atol(argv[2]); }
    if (w_ < 3 || h_ < 3)
        return print_usage(), EXIT_FAILURE;
    size_t w = (size_t) w_, h = (size_t) h_;

    srand(time(NULL));

    maze_t *maze = malloc_maze(w, h);
    add_border(maze);
    size_t s = add_start_and_end(maze);
    do {
        mystify_air(maze);
        walk(s, 1, maze);
    } while (!FOUND);
    turn_unknowns_into_walls(maze);

    if (ppm)
        print_maze_ppm(maze);
    else
        print_maze(maze);

    free_maze(maze);

    return EXIT_SUCCESS; }
