#!/usr/bin/perl  

use Tinkerforge::IPConnection;
use Tinkerforge::BrickletIO4;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'h15'; # Change to your UID

my $ipcon = IPConnection->new(); # Create IP connection
my $io = BrickletIO4->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Set pin 1 to output low
$io->set_configuration(1 << 1, 'o', 0);

# Set pin 2 and 3 to output high
$io->set_configuration((1 << 2) | (1 << 3), 'o', 1);

print "\nPress any key to exit...\n";
<STDIN>;
$ipcon->disconnect();

