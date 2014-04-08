SLAVE = gcc
OBJ = adc.o setup.o joystick.o

%.o: %.c %.h
	$(SLAVE) -c -std=gnu99 -lrt -o $@ $<

all:main.out
python:python.so

main.out:$(OBJ)
	$(SLAVE) -std=gnu99 -lrt -lwiringPi -o main.out $(OBJ) main.o

python.so: adc.c
	$(SLAVE) -shared -lwiringPi -Wl,-soname,adc_python -fPIC --std=gnu99 -o python.so $(OBJ)

