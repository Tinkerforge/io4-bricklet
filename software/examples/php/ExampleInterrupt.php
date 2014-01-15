<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIO4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIO4;

const HOST = 'localhost';
const PORT = 4223;
const UID = '6hY'; // Change to your UID

// Callback function for interrupts
function cb_interrupt($interruptMask, $valueMask)
{
    echo "Interrupt by: " . decbin($interruptMask) . "\n";
    echo "Value: " . decbin($valueMask) . "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$io4 = new BrickletIO4(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register callback for interrupts
$io4->registerCallback(BrickletIO4::CALLBACK_INTERRUPT, 'cb_interrupt');

// Enable interrupt on pin 0
$io4->setInterrupt(1 << 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
