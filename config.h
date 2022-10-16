#ifndef CONFIG_H
#define CONFIG_H

// How long to wait until the next check is performed
#define WAIT_ROTATE 2

// the Device to read the Data from
// to see all available: ls /sys/bus/iio/devices/
#define DEVICE "/sys/bus/iio/devices/iio:device0/"

// the Display to rotate
#define DISPLAY "eDP"

// the ranges for each Orientation
static int ranges[4][3][2] = {
    //  x         y          z
    {{-4, 5}, {-10,  0}, {-12, 5}}, // normal
    {{ 0, 9}, { -4,  5}, {-13, 4}}, // left
    {{-9, 0}, { -4,  3}, {-11, 2}}, // right
    {{-3, 1}, {  0, 10}, {-10, 2}}, // inverted
};

#endif // CONFIG_H
