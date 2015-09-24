#!/usr/bin/perl

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIO4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change to your UID

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $io = Tinkerforge::BrickletIO4->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current value as bitmask
my $value_mask = $io->get_value();
print "Value Mask: " . sprintf('%04b', $value_mask) . "\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
