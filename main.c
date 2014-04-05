#include "setup.h"
#include "joystick.h"
#include "adc.h"

int main(void)
{
	setup();

	int *pos = read_joystick();

	printf("%d,%d\n", pos[0], pos[1]);
}
