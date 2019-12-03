/* This file contains includes and prototypes for the main command line UI
*
* Author: Josh McIntyre
*/
#include <stdio.h>
#include <calc.h>

// Keysizes to test for real computations
const int REAL_KEYSIZES_LENGTH = 5;
const short REAL_KEYSIZES[] = { 8, 12, 16, 18, 20 };

// Keysizes to calculate by estimation (will take too long for real computation)
const int EST_KEYSIZES_LENGTH = 12;
short EST_KEYSIZES[] = { 24, 28, 32, 36, 40, 44, 48, 52, 64, 128, 192, 256 };

// Presentation sizes
const double SECONDS_PER_MINUTE = 60.0;
const double SECONDS_PER_HOUR = 3600.0;
const double SECONDS_PER_DAY = 86400.0;
const double SECONDS_PER_YEAR = 31557600.0;
