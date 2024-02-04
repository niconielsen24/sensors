#include <sensors/sensors.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>

#include "../include/sensor_utils.h"
#include "../include/resize_uitls.h"

volatile __sig_atomic_t resized_flag = 0;

void handle_resize(int _signo) {
    resized_flag = 1;
}

int main() {
    initscr(); // why is this called initscr??
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    curs_set(0);

    int max_h,max_l;
    getmaxyx(stdscr,max_h,max_l);
    WINDOW * window = newwin(max_h/2, max_l/2, max_h/4, max_l/4);
    signal(SIGWINCH, handle_resize);
    nodelay(window, TRUE);

    sensors_init(NULL);
    int chip_count_num = chip_count();  
    const sensors_chip_name ** chips = get_chips();
    if (*chips == NULL) {
        fprintf(stderr, "Failed to get detected Chips");
        free(chips);
        return EXIT_FAILURE;
    }

    const sensors_feature * feature = NULL;
    const sensors_feature * feature_f = NULL;
    const sensors_feature * feature_v = NULL;
    double feature_value_temp = 0;
    double feature_value_rpm = 0;
    double feature_value_volts = 0;

    bool should_continue = TRUE;
    int current_line;
    while (should_continue) {
        current_line = 0;
        wclear(window);

        if (resized_flag) {
            resize(window, &resized_flag);
        }

        box(window, 0, 0);

        for (int i = 0; i < chip_count_num; i++) {
            feature = get_chip_feature(chips[i], SENSORS_FEATURE_TEMP);
            feature_f = get_chip_feature(chips[i], SENSORS_FEATURE_FAN);
            feature_v = get_chip_feature(chips[i], SENSORS_FEATURE_IN);

            if (feature != NULL) {
                sensors_get_value(chips[i], feature->number, &feature_value_temp);
                mvwprintw(window, 2+current_line, 2, "%10s temp : %.2f", chips[i]->prefix, feature_value_temp);
                current_line++;
            }
            if (feature_f != NULL) {
                sensors_get_value(chips[i], feature_f->number, &feature_value_rpm);
                mvwprintw(window, 2+current_line, 2, "%11s RPM : %.2f", chips[i]->prefix, feature_value_rpm);
                current_line++;
            }
            if (feature_v != NULL) {
                sensors_get_value(chips[i], feature_v->number, &feature_value_volts);
                mvwprintw(window, 2+current_line, 2, "%13s V : %.2f", chips[i]->prefix, feature_value_volts);
                current_line++;
            }

        }

        if (getch() == 'q'){
            wclear(window);
            should_continue = FALSE;
        }

        usleep(500000);
        wrefresh(window);
    }

    free(chips);
    sensors_cleanup();
    endwin(); // and this called endwin????? 
    return EXIT_SUCCESS;
}