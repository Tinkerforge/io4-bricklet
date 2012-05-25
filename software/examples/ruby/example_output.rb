#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_io4'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = '6hY' # Change to your UID

ipcon = IPConnection.new HOST, PORT # Create IP connection to brickd
io4 = BrickletIO4.new UID # Create device object
ipcon.add_device io4 # Add device to IP connection
# Don't use device before it is added to a connection

# Set pin 1 to output low
io4.set_configuration 1 << 1, 'o', false

# Set pin 2 and 3 to output high
io4.set_configuration((1 << 2) | (1 << 3), 'o', true)

puts 'Press key to exit'
$stdin.gets
ipcon.destroy
