#ifndef MAIN_H
#define MAIN_H

#define VERSION "0.1"

#define DEVICE_NAME_LEN 50
#define DEVICE_RESULT_LEN 10
#define COMMAND_LEN 100

typedef struct {
  int x, y, z;
} accel;

enum { NORMAL, LEFT, RIGHT, INVERTED };
static char *ORIENTATION[4] = {"normal", "left", "right", "inverted"};
static char *TRANSMISSION[4] = {
  "1 0 0 0 1 0 0 0 1",
  "0 -1 1 1 0 0 0 0 1",
  "0 1 0 -1 0 1 0 0 1",
  "-1 0 1 0 -1 1 0 0 1",
};

#endif // MAIN_H
