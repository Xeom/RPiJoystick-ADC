#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>
#include <wiringPi.h>

#define CHANNUM    8 /*The number of channels on the ADC*/
#define BITS      10 /*The accuracy of the ADC*/

#define CLK        0 /*The pin connected to the ADC's CLK*/
#define MOSI       3 /*The pin connected to the ADC's DIN*/
#define MISO       2 /*The pin connected to the ADC's DOUT*/
#define SS         6 /*The pin connected to the ADC's SHDN*/

#define IS_BI      0 /*Whether to use bi pairings*/
#define COMMANDLEN 2 /*The amount of bits the command is*/

#define OCD       16 /*The OCD of the reader*/
#define WAIT     100 /*The amount of time to fuck around*/

/*
 * Sets up the pins and wiringPi
 * for operation - Returns -1 on error
 */
int setup_adc(void);

/*
 * Pulses the clock pin
 */
void pulse_clock(void);

/*
 * Gets the location of the MSB
 * of n
 */
int get_msb(int n);

/*
 * Reads data from the ADC,
 * requesting a values from
 * a specific channel(chan)
 */
int read_adc(int chan);

/*
 *Reads OCD times from the ADC,
 *then takes the most occuring value
 *this eliminates almost all errors.
 */
int read_adc_clean(int chan);
