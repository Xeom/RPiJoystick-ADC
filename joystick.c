#include "joystick.h"

int read_joystick_x(void)
{
	return read_adc_clean(X_PORT);
}

int read_joystick_y(void)
{
	return read_adc_clean(Y_PORT);
}

int *read_joystick(void)
{
	int *pos = malloc(2 * sizeof(int));

	pos[0] = read_joystick_x();
	pos[1] = read_joystick_y();

	return pos;
}

int read_select(void)
{
	return digitalRead(BUTN);
}
