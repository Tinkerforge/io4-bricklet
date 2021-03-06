#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_io4'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your IO-4 Bricklet

ipcon = IPConnection.new # Create IP connection
io = BrickletIO4.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Set pin 1 to output low
io.set_configuration 1 << 1, 'o', false

# Set pin 2 and 3 to output high
io.set_configuration((1 << 2) | (1 << 3), 'o', true)

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
