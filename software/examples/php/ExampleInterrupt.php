<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIO4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIO4;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your IO-4 Bricklet

// Callback function for interrupt callback
function cb_interrupt($interrupt_mask, $value_mask)
{
    echo "Interrupt Mask: " . sprintf("%04b", $interrupt_mask) . "\n";
    echo "Value Mask: " . sprintf("%04b", $value_mask) . "\n";
    echo "\n";
}

$ipcon = new IPConnection(); // Create IP connection
$io = new BrickletIO4(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register interrupt callback to function cb_interrupt
$io->registerCallback(BrickletIO4::CALLBACK_INTERRUPT, 'cb_interrupt');

// Enable interrupt on pin 0
$io->setInterrupt(1 << 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
