#include <curses.h>

void resize(WINDOW * window, volatile __sig_atomic_t * resized_flag){
    int max_h,max_l;
    endwin();
    refresh();
    clear();
    getmaxyx(stdscr, max_h, max_l);
    wresize(window, max_h / 2, max_l / 2);
    mvwin(window, max_h / 4, max_l / 4);
    box(window, 0, 0);
    *resized_flag = 0;
    refresh();
};