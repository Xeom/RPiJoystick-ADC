#include "setup.h"
#include "joystick.h"
#include "adc.h"

int main(int argc, char *argv[])
{
	setup();

	if (argc == 1)
	{
		int *pos = read_joystick();

		printf("%d,%d\n", pos[0], pos[1]);
	}

	else if (argv[1][0] == 'x')
		printf("%d\n", read_joystick_x());

	else if (argv[1][0] == 'y')
		printf("%d\n", read_joystick_y());

	else
		printf("NO");
}
