#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIO4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'h15'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
my $io = BrickletIO4->new(&UID, $ipcon); # Create device object

# Callback function for interrupts
sub cb_interrupt
{
    my ($interrupt_mask, $value_mask) = @_;

    print "\nInterrupt by: ".sprintf('%b', $interrupt_mask);
    print "\nValue: ".sprintf('%b', $value_mask)."\n";
}

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register callback for interrupts
$io->register_callback($io->CALLBACK_INTERRUPT, 'cb_interrupt');

# Enable interrupt on pin 0
$io->set_interrupt(1 << 0);

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

