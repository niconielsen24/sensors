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

    const sensors_feature * feature = NULL;
    const sensors_feature * feature_f = NULL;
    const sensors_feature * feature_b = NULL;
    double feature_value_temp = 0;
    double feature_value_rpm = 0;
    double feature_value_volts = 0;

    bool should_close = FALSE;
    while (!should_close) {
        clear();

        int mid_h = max_h / 2;
        int mid_l = max_l / 2;
        int current_line = 0;

        for (int i = 0; i < chip_count_num; i++){
            feature = get_chip_feature(chips[i], SENSORS_FEATURE_TEMP);
            feature_f = get_chip_feature(chips[i], SENSORS_FEATURE_FAN);
            feature_b = get_chip_feature(chips[i], SENSORS_FEATURE_IN);
            if (feature !=  NULL){
                move(mid_h+current_line,mid_l-17);
                printw("%10s temp :",(chips[i])->prefix);
                sensors_get_value(chips[i], feature->number, &feature_value_temp);
                printw(" %.2f \n",feature_value_temp);
                current_line++;
            }
            if (feature_f !=  NULL) {
               move(mid_h+current_line+3,mid_l-17);
               printw("%11s RPM :",(chips[i])->prefix);
               sensors_get_value(chips[i], feature_f->number, &feature_value_rpm);
               printw(" %.2f \n", feature_value_rpm);
            }
            if (feature_b !=  NULL) {
               move(mid_h+current_line+5,mid_l-17);
               printw("%10s Volt :",(chips[i])->prefix);
               sensors_get_value(chips[i], feature_b->number, &feature_value_volts);
               printw(" %.2f \n", feature_value_volts);
            }
        }

        move(max_h-1,mid_l-9);
        printw("Press 'q' to quit");

        if (getch()== 'q'){
            clear();
            should_close = TRUE;
        }

        usleep(500000);
        refresh();
    }

    free(chips);
    sensors_cleanup();
    endwin(); // and this called enwin????? 
    return EXIT_SUCCESS;
}