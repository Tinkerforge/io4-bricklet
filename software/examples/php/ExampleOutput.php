<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIO4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIO4;

$host = 'localhost';
$port = 4223;
$uid = '6hY'; // Change to your UID

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$io4 = new BrickletIO4($uid); // Create device object

$ipcon->addDevice($io4); // Add device to IP connection
// Don't use device before it is added to a connection

// Set pin 1 to output low
$io4->setConfiguration(1 << 1, 'o', FALSE);

// Set pin 2 and 3 to output high
$io4->setConfiguration((1 << 2) | (1 << 3), 'o', TRUE);

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->destroy();

?>
