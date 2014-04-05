#include "setup.h"

int setup(void)
{
	/*If wiringPi has an error, return it*/ 
	if (wiringPiSetup() == -1)
		return -1;

	/*Set up CLK, MOSI and SS pins to output*/
	pinMode(CLK,  OUTPUT);
	pinMode(MOSI, OUTPUT);
	pinMode(SS,   OUTPUT);

	/*Set up MISO for input*/
	pinMode(MISO, INPUT);

	/*Set up BUTN for input*/
	pinMode(BUTN, INPUT);

	return 0;
}
