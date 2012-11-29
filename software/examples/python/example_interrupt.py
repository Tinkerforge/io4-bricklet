#!/usr/bin/env python
# -*- coding: utf-8 -*-  

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change to your UID

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_io4 import IO4

# Callback function for interrupts
def cb_interrupt(interrupt_mask, value_mask):
    print('Interrupt by: ' + str(bin(interrupt_mask)))
    print('Value: ' + str(bin(value_mask)))

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    io = IO4(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register callback for interrupts
    io.register_callback(io.CALLBACK_INTERRUPT, cb_interrupt)

    # Enable interrupt on pin 0
    io.set_interrupt(1 << 0)

    raw_input('Press key to exit\n') # Use input() in Python 3
