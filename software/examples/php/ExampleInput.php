<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIO4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIO4;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your IO-4 Bricklet

$ipcon = new IPConnection(); // Create IP connection
$io = new BrickletIO4(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current value as bitmask
$value_mask = $io->getValue();
echo "Value Mask: " . sprintf("%04b", $value_mask) . "\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
