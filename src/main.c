#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "./../config.h"
#include "main.h"
#include "utils.h"

volatile sig_atomic_t running;
void handler(int sig_num) {
  running = 0;
}

int main(int argc, char **argv) {
  signal(SIGINT, &handler);
  running = 1;

  int verbose = 0;
  char *userscript_path = NULL;
  if (argc > 1 && argc <= 3) {
    if (strcmp(argv[1], "-v") == 0) {
      verbose = 1;
    } else if (strcmp(argv[1], "-s") == 0) {
      if (argc == 3) {
        userscript_path = argv[2];
      } else {
        printf("ERROR: no Path to the userscript given!\n");
        return EXIT_FAILURE;
      }
    } else if (strcmp(argv[1], "-V") == 0) {
      printf("%s: Version %s\n", argv[0], VERSION);
      return EXIT_SUCCESS;
    } else if (strcmp(argv[1], "-h") == 0) {
      printf("Usage: %s <-v|-V|-h>\n", argv[0]);
      printf("  -v: enables Output\n");
      printf("  -s <path>: when given it enables the userscript Feature\n");
      printf("  -V: shows the Version of %s\n", argv[0]);
      printf("  -h: shows this Help\n");
      return EXIT_SUCCESS;
    }
  }

  accel current, pre;
  int orientation, last;
  char command[COMMAND_LEN];

  pre = getAccel();
  last = getOrientation(pre);

  while (running) {
    current = getAccel();
    if compareAccel (current, pre) {
      orientation = getOrientation(current);
      if (orientation != last) {
        if (orientation != -1) {
          if (verbose == 1)
            printf("Orientation: %s\n", ORIENTATION[orientation]);
          if (snprintf(command, sizeof(command),
                       "xrandr --output " DISPLAY " --rotate %s",
                       ORIENTATION[orientation]) >= 0) {
            // if (snprintf(command, sizeof(command), "screenRotate %s",
            // ORIENTATION[orientation]) >= 0) {
            if (verbose == 1)
              printf("EXECUTING: '%s'\n", command);
            system(command);
          } else if (verbose == 1)
            printf("ERROR: couldnt generate command\n");
        } else {
          if (verbose == 1) {
            printf("ERROR: orientation not defined\n");
            printf("Accel: x:%d y:%d z:%d\n", current.x, current.y, current.z);
          }
        }
      } else if (verbose == 1)
        printf("Same orientation\n");
    }

    pre = current;
    last = orientation;
    sleep(WAIT_ROTATE);
  }

  return EXIT_SUCCESS;
}
