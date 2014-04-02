#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIO4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'h15'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $io = Tinkerforge::BrickletIO4->new(&UID, $ipcon); # Create device object

# Callback function for interrupts
sub cb_interrupt
{
    my ($interrupt_mask, $value_mask) = @_;

    print "Interrupt by: ".sprintf('%b', $interrupt_mask)."\n";
    print "Value: ".sprintf('%b', $value_mask)."\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register callback for interrupts
$io->register_callback($io->CALLBACK_INTERRUPT, 'cb_interrupt');

# Enable interrupt on pin 0
$io->set_interrupt(1 << 0);

print "Press any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

