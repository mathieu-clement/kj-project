#ifndef SIMPLE_CAMERA_SETTINGS_WITH_TV_REMOTE_H
#define SIMPLE_CAMERA_SETTINGS_WITH_TV_REMOTE_H

void cs_init(void);
void cs_reset_tv_remote(void);

int1 cs_exp_time_up(void);
int1 cs_exp_time_down(void;

int1 cs_power_button(void);

/**
 * Step to increment or decrement when user presses the "Threshold UP" or 
 * "Threshold DOWN" key on the TV remote control
 */
#define CS_THRESHOLD_INCREMENT 20

int1 cs_threshold_up(void);
int1 cs_threshold_down(void);

void cs_set_camera_with_tv_remote(void);

#include "simple_camera_settings_with_tv_remote.c"

#endif