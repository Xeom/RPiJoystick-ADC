#include <wiringPi.h>

#include "adc.h"

#define BUTN   10
#define X_PORT  1
#define Y_PORT  2

/*
 *Read the joystick's x position
 */
int read_joystick_x(void);

/*
 *Read the joystick's y position
 */
int read_joystick_y(void);

/*
 *Read the position of the joystick
 */
int *read_joystick(void);

/*
 *Check if the select button is pressed
 */
int read_select(void);
