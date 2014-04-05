SLAVE = gcc
OBJ = adc.o setup.o joystick.o main.o

%.o: %.c %.h
	$(SLAVE) -c -std=gnu99 -lrt -o $@ $<

all:main

main:$(OBJ)
	$(SLAVE) -std=gnu99 -lrt -lwiringPi -o main $(OBJ)

adc_python.so: adc.c
	$(SLAVE) -shared -lwiringPi -Wl,-soname,adc_python -fPIC --std=gnu99 -o adc_python.so adc.c
