<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIO4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIO4;

const HOST = 'localhost';
const PORT = 4223;
const UID = '6hY'; // Change to your UID

$ipcon = new IPConnection(); // Create IP connection
$io4 = new BrickletIO4(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Set pin 1 to output low
$io4->setConfiguration(1 << 1, 'o', FALSE);

// Set pin 2 and 3 to output high
$io4->setConfiguration((1 << 2) | (1 << 3), 'o', TRUE);

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
