#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIO4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your IO-4 Bricklet

# Callback subroutine for interrupt callback
sub cb_interrupt
{
    my ($interrupt_mask, $value_mask) = @_;

    print "Interrupt Mask: " . sprintf('%04b', $interrupt_mask) . "\n";
    print "Value Mask: " . sprintf('%04b', $value_mask) . "\n";
    print "\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $io = Tinkerforge::BrickletIO4->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register interrupt callback to subroutine cb_interrupt
$io->register_callback($io->CALLBACK_INTERRUPT, 'cb_interrupt');

# Enable interrupt on pin 0
$io->set_interrupt(1 << 0);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
