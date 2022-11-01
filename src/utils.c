#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./../config.h"
#include "main.h"
#include "utils.h"

int getDimension(const char *dimension) {
  FILE *dim;
  char dev_dimension[DEVICE_NAME_LEN];
  char result[DEVICE_RESULT_LEN];
  int ret;
  snprintf(dev_dimension, sizeof(dev_dimension), DEVICE "%s", dimension);

  dim = fopen(dev_dimension, "r");

  if (!dim) {
    fprintf(stderr, "ERROR: Cant open Accelerator: %s\n", dev_dimension);
    exit(EXIT_FAILURE);
  }

  if (fgets(result, sizeof(result), dim) == NULL) {
    fprintf(stderr, "ERROR: Cant read from Accelerator: %s\n",
            dev_dimension);
    exit(EXIT_FAILURE);
  }

  result[strlen(result) - 1] = 0;
  ret = atoi(result);
  if ((ret == 0) && strcmp(result, "0") != 0) {
    fprintf(stderr, "ERROR: Couldnt convert '%s'\n", result);
    exit(EXIT_FAILURE);
  }

  fclose(dim);
  return ret;
}

accel getAccel() {
  accel a;
  a.x = getDimension("in_accel_x_raw");
  a.y = getDimension("in_accel_y_raw");
  a.z = getDimension("in_accel_z_raw");
  return a;
}

int getOrientation(accel current) {
  if rangeCheck (NORMAL) {
    return NORMAL;
  } else if rangeCheck (LEFT) {
    return LEFT;
  } else if rangeCheck (RIGHT) {
    return RIGHT;
  } else if rangeCheck (INVERTED) {
    return INVERTED;
  }

  return -1;
}

void rotate(int orientation, int verbose, char *usr_scr) {
  char command[COMMAND_LEN];
  char *transmission;

  if (snprintf(command, sizeof(command), "xrandr --output %s --rotate %s",
               DISPLAY, ORIENTATION[orientation]) >= 0) {
    system(command);
  } else if (verbose == 1)
    fprintf(stderr,
            "ERROR: Couldnt generate rotation Command for Display: " DISPLAY
            "\n");

  transmission = TRANSMISSION[orientation];

  for (int i = 0; devices_input[i] != NULL; i++) {
    if (snprintf(command, sizeof(command), "xinput --set-prop '%s' 163 %s",
                 devices_input[i], transmission) >= 0) {
      system(command);
    } else if (verbose == 1)
      fprintf(stderr, "ERROR: Couldnt generate Command for Device: %s\n",
              devices_input[i]);
  }

  if (usr_scr) {
    if (snprintf(command, sizeof(command), "sh '%s' %s", usr_scr,
                 ORIENTATION[orientation]) >= 0) {
      system(command);
    } else if (verbose == 1)
      fprintf(stderr,
              "ERROR: Couldnt generate Command for Userscript path: %s\n",
              usr_scr);
  }
}

void set_device(int state, int verbose) {
  char command[COMMAND_LEN];
  char *state_command;

  if (state == ENABLE)
    state_command = "enable";
  else
    state_command = "disable";

  for (int i = 0; devices_state[i] != NULL; i++) {
    if (snprintf(command, sizeof(command), "xinput %s '%s'", state_command,
                 devices_state[i]) >= 0) {
      system(command);
    } else if (verbose == 1)
      fprintf(stderr, "ERROR: Couldnt generate Command for Device: %s\n",
              devices_state[i]);
  }
}
