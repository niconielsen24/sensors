#include <sensors/sensors.h>
#include <stdio.h>
#include <stdlib.h>

int chip_count (){
    int count = 0;
    int nr = 0;
    const sensors_chip_name * chip;

    while ((chip = sensors_get_detected_chips(NULL, &nr)) != NULL) {
        count++;
    }

    return count;
}

const sensors_chip_name ** get_chips(){
    int count = chip_count();

    const sensors_chip_name ** chips = calloc(count, sizeof(const sensors_chip_name *));
    if (chips == NULL) {
        fprintf(stderr, "Failed to Allocate memory for 'chips array'\n");
        return NULL;
    }

    int nr = 0;
    int i = 0;
    const sensors_chip_name * chip;

    while ((chip = sensors_get_detected_chips(NULL, &nr)) != NULL) {
        chips[i] = chip;
        i++;
    }

    return chips;
}

const sensors_feature * get_chip_feature(const sensors_chip_name * chip_name, sensors_feature_type type) {
    const sensors_feature * feature; 
    int nr = 0;

    while ((feature = sensors_get_features(chip_name, &nr)) != NULL) {
        if (feature->type == type) {
            break;
        } else {
            feature = NULL;
        }
    }

    return feature;
}