#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your IO-4 Bricklet

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_io4 import BrickletIO4

# Callback function for interrupt callback
def cb_interrupt(interrupt_mask, value_mask):
    print("Interrupt Mask: " + format(interrupt_mask, "04b"))
    print("Value Mask: " + format(value_mask, "04b"))
    print("")

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    io = BrickletIO4(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register interrupt callback to function cb_interrupt
    io.register_callback(io.CALLBACK_INTERRUPT, cb_interrupt)

    # Enable interrupt on pin 0
    io.set_interrupt(1 << 0)

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
