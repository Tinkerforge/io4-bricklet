#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# set pin 1 to output low: (1 << 1) = 2
tinkerforge call io4-bricklet $uid set-configuration 2 output false

# set pin 2 and 3 to output high: (1 << 2) | (1 << 3) = 12
tinkerforge call io4-bricklet $uid set-configuration 12 output true
