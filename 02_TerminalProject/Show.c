#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        return 1;
    }

    initscr();
    curs_set(0);
    noecho();

    printw("%s", argv[1]);
    refresh();

    WINDOW *win = newwin(LINES - 1, COLS, 1, 0);
    keypad(win, TRUE);
    scrollok(win, TRUE);

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        return 1;
    }

    char **file_lines = malloc(1000 * sizeof(char *));
    size_t line_num = 0, max_line_num = 1000, line_size, last_line = LINES - 3;

    wprintw(win, "42\n");
    while (getline(&file_lines[line_num], &line_size, file) != -1) {
        if (line_num < last_line) {
            wprintw(win, "  %d  %s", line_num, file_lines[line_num]);
        }
        line_num++;
        if (line_num == max_line_num) {
            file_lines = realloc(file_lines, max_line_num * 2 * sizeof(char *));
            max_line_num *= 2;
        }
    }
    box(win, 0, 0);
    wrefresh(win);

    fclose(file);

    while (1) {
        int key = wgetch(win);
        if (key == 32) {
            if (last_line >= line_num) {
                continue;
            }
            wprintw(win, "  %d  %s", last_line, file_lines[last_line]);
            last_line++;
            box(win, 0, 0);
            wrefresh(win);
        }
        if (key == 27) {
            break;
        }
    }

    for (int i = 0; i < line_num; i++) {
        free(file_lines[i]);
    }
    free(file_lines);

    endwin();

    return 0;
}
