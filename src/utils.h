#ifndef UTILS_H
#define UTILS_H

#include "./../config.h"
#include "main.h"

#define compareAccel(a1, a2)                                                   \
  (!(a1.x == a2.x) || !(a1.y == a2.y) || !(a1.z == a2.z))

#define rangeCheck(orientation)                                                \
  (((current.x >= ranges[orientation][0][0]) &&                                \
    (current.x <= ranges[orientation][0][1])) &&                               \
   ((current.y >= ranges[orientation][1][0]) &&                                \
    (current.y <= ranges[orientation][1][1])) &&                               \
   ((current.z >= ranges[orientation][2][0]) &&                                \
    (current.z <= ranges[orientation][2][1])))

/**
 * @brief get the current Value from the given dimension
 *
 * @param dimension the dimension to get the Value from
 * @return the Vaule from the given dimension
 */
int getDimension(const char *dimension);

/**
 * @brief get the x,y,z dimensions
 *
 * @return the current values
 */
accel getAccel();

/**
 * @brief checks the given value in which state the pc is
 *
 * @param current the current values
 * @return returns the orientation
 */
int getOrientation(accel current);

/**
 * @brief Rotate the Screen and runs extra Commands
 *
 * @param orientation the Orientation to Rotate to
 * @param verbose the state of verbosity
 * @param usr_scr path to the userscript
 */
void rotate(int orientation, int verbose, char *usr_scr);

#endif // UTILS_H
