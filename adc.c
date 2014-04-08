#include "adc.h"

#define MAJORITY (OCD >> 1) + (OCD & 1)

#if IS_BI
#define COMMAND 0b10
#else
#define COMMAND 0b11
#endif

void pulse_clock(void)
{
	/*Set clock to high*/
	digitalWrite(CLK, 1);

	/*Fuck around for a bit*/
	for(int c = 0; c < WAIT; ++c){}

	/*Lower clock*/
	digitalWrite(CLK, 0);
}

int get_msb(int n)
{
	int c = 0;

	while (n)
	{
		n >>= 1;
		++c;
	}

	return c;
}

int read_adc(int chan)
{
	/*Return error if channel is invalid*/
	if (chan < 0 || chan > CHANNUM)
		return -1;

	/*Ensure clock is low and slave select is high, then select*/
	digitalWrite(SS,  1);
	digitalWrite(CLK, 0);
	digitalWrite(SS,  0);

	/*Get the size of the volitile data, and total packet*/
	size_t dataSize = get_msb(CHANNUM - 1);
	size_t pcktSize = dataSize + COMMANDLEN;

	/*Initialise the static part of the packet*/
	int cmd  = COMMAND;

	/*Make space for the volitile part of the packet and OR it in*/
	cmd    <<= dataSize;
	cmd     |= chan;

	/*Make a mask of the bit to the left of the first command bit*/
	int mask = 1 << pcktSize;

	for (int c = 0; c < pcktSize; ++c)
	{
		/*Shift command up*/
		cmd <<= 1;

		/*Write the masked bit to MOSI*/
		digitalWrite(MOSI, (cmd & mask) > 0);

		/*Pulse CLK*/
		pulse_clock();
	}

	/*Initialise an integer to receive into*/
	int recv = 0;

	/*The size of the received packet is the bits + one null and one empty bit*/
	size_t recvSize = BITS + 2;

	for (int c = 0; c < recvSize; ++c)
	{
		/*Shift received packet up*/
		recv <<= 1;

		/*Pulse CLK*/
		pulse_clock();

		/*Set the first bit of the received packet to MISO*/
		recv |= digitalRead(MISO);
	}
	/*Return the first 10 bits of the received packet*/
	return (recv >> 1) & 1023;
}

int read_adc_clean(int chan)
{
	/*The largest yet value, and its count*/
	int largestv = -1;
	int largestc = 0;

	/*The current chained value and its chain count*/
	int chainv   = -1;
	int chainc   = 0;

	/*Lists for every value and its count*/
	int readingsc[OCD] = {-1};
	int readingsv[OCD] = {-1};


	for(int c = 0; c < OCD; ++c)
	{
		/*Get new value from ADC*/
		int next = read_adc(chan);

		if (next == -1)
			return -1;

		/*If this is the last iteration, and values are chained, increment the chain counter*/
		if (next == chainv && c == (OCD - 1))
			++chainc;

		/*If the values' chain is broken, or it's the last iteration, do a load of things*/
		if (next != chainv || c == (OCD - 1))
		{
			for(int i = 0; i < OCD; ++i)
			{
				/*If we've gone off the end of values we've had before, make a new one*/
				if (readingsv[i] == -1)
				{
					readingsv[i] = chainv;
					readingsc[i] = chainc;
					break;

				}
				/*If we've seen this value before, increment it in the lists*/
				else if(readingsv[i] == chainv)
				{
					readingsc[i] += chainc;
					/*Update chainc to the total occorances of this value, ever*/
					chainc = readingsc[i];
					break;
				}
			}

			/*The total occorances of this value are greater than the required amount for a majority*/
			if (chainc >= MAJORITY)
				return chainv;

			/*The total occorances of this value are greatest yet*/
			if (chainc > largestc)
			{
				largestv = chainv;
				largestc = chainc;
			}

			/*Reset chainc and chainv*/
			chainc = 1;
			chainv = next;
		}
		/*This value is the same as the last*/
		else
		{
			/*Increment the chain*/
			++chainc;

			/*If the chain is greater than the required amount for a majority, return it.*/
			if (chainc >= MAJORITY)
				return chainv;
		}
	}

	/*Return the running largest value if it was not returned before all 16 reads*/
	return largestv;

}
