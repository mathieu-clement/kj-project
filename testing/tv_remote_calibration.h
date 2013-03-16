#ifndef CALIBRATION_DD
#define CALIBRATION_DD
#include "tv_remote_calibration.h"
#include "core.h"
#include "../basic_functions.h"
#include "../tv_remote_utils.h"
#include "find_barcode.h"



/**
 * Init program to read camera settings from TV remote and set them.
 */
void calibrate_thresholds(void);
void calibrate_camera(void);
void calibrate_rotations(void);

#include "tv_remote_calibration.c"
#endif
