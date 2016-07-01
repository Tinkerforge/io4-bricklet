#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your IO-4 Bricklet

# Set pin 1 to output low: 1 << 1 = 2
tinkerforge call io4-bricklet $uid set-configuration 2 out false

# Set pin 2 and 3 to output high: (1 << 2) | (1 << 3) = 12
tinkerforge call io4-bricklet $uid set-configuration 12 out true
