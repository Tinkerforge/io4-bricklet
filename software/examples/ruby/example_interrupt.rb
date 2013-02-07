#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_io4'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = '6hY' # Change to your UID

ipcon = IPConnection.new # Create IP connection
io4 = BrickletIO4.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Register callback for interrupts
io4.register_callback(BrickletIO4::CALLBACK_INTERRUPT) do |interrupt_mask, value_mask|
  puts "Interrupt by: #{interrupt_mask.to_s 2}"
  puts "Value: #{value_mask.to_s 2}"
end

# Enable interrupt on pin 0
io4.set_interrupt 1 << 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
