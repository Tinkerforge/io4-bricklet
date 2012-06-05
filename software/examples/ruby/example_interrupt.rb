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

# Enable interrupt on pin 0  
io4.set_interrupt 1 << 0

# Register callback for interrupts
io4.register_callback(BrickletIO4::CALLBACK_INTERRUPT) do |interrupt_mask, value_mask|
  puts "Interrupt by: #{interrupt_mask.to_s 2}"
  puts "Value: #{value_mask.to_s 2}"
end

puts 'Press key to exit'
$stdin.gets
ipcon.destroy
