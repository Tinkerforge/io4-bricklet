#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your IO-4 Bricklet

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_io4 import BrickletIO4

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    io = BrickletIO4(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Set pin 1 to output low
    io.set_configuration(1 << 1, "o", False)

    # Set pin 2 and 3 to output high
    io.set_configuration((1 << 2) | (1 << 3), "o", True)

    raw_input("Press key to exit\n") # Use input() in Python 3
    ipcon.disconnect()
