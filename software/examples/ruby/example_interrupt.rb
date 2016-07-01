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

# Register interrupt callback
io.register_callback(BrickletIO4::CALLBACK_INTERRUPT) do |interrupt_mask, value_mask|
  puts "Interrupt Mask: #{'%04b' % interrupt_mask}"
  puts "Value Mask: #{'%04b' % value_mask}"
  puts ''
end

# Enable interrupt on pin 0
io.set_interrupt 1 << 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
