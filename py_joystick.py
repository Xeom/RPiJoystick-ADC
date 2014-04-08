import ctypes
import os

lib = ctypes.CDLL(os.getcwd()+"/python.so")
lib.setup()

lib._read_joystick = lib.read_joystick
lib.read_joystick = lambda:ctypes.cast(lib._read_joystick(), ctypes.POINTER(ctypes.c_int))[:2]
