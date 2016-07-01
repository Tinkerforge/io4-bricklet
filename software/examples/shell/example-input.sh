#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your IO-4 Bricklet

# Get current value as bitmask
tinkerforge call io4-bricklet $uid get-value
