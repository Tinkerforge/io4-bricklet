#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change to your UID

# Enable interrupt on pin 0: 1 << 0 = 1
tinkerforge call io4-bricklet $uid set-interrupt 1

# Handle incoming interrupt callbacks
tinkerforge dispatch io4-bricklet $uid interrupt
