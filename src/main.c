#include <sensors/sensors.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>

#include "../include/sensor_utils.h"

int main() {
    initscr(); // why is this called initscr??
    cbreak();
    nodelay(stdscr, 1);
    curs_set(0);

    int max_h,max_l;
    getmaxyx(stdscr,max_h,max_l);
    

    sensors_init(NULL);
    int chip_count_num = chip_count();

    const sensors_chip_name ** chips = get_chips();
    if (*chips == NULL) {
        fprintf(stderr, "Failed to get detected Chips");
        free(chips);
        return EXIT_FAILURE;
    }

    while (1) {

        clear();

        int mid_h = max_h / 2;
        int mid_l = max_l / 2;
        int current_line = 0;

        for (int i = 0; i < chip_count_num; i++){
            const sensors_feature * feature = get_chip_feature(chips[i], SENSORS_FEATURE_TEMP);
            if (feature !=  NULL){
                move(mid_h+current_line,mid_l-17);
                printw("%10s temp :",(chips[i])->prefix);
                double temperature;
                sensors_get_value(chips[i], feature->number, &temperature);
                printw(" %.2f \n",temperature);
                current_line++;
            }
        }

        move(max_h-1,mid_l-9);
        printw("Press 'q' to quit");

        if (getch()== 'q'){
            clear();
            break;
        }

        usleep(1000000);
        refresh();
    }

    free(chips);
    sensors_cleanup();
    endwin();
    return EXIT_SUCCESS;
}