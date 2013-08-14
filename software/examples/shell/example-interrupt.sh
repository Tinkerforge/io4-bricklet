#!/bin/sh
# connects to localhost:4223 by default, use --host and --port to change it

# change to your UID
uid=XYZ

# enable interrupt on pin 0: (1 << 0) = 1
tinkerforge call io4-bricklet $uid set-interrupt 1

# handle incoming interrupt callbacks
tinkerforge dispatch io4-bricklet $uid interrupt
