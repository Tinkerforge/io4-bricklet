<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletIO4.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletIO4;

$host = 'localhost';
$port = 4223;
$uid = '6hY'; // Change to your UID

// Callback function for interrupts
function cb_interrupt($interruptMask, $valueMask)
{
    echo "Interrupt by: " . decbin($interruptMask) . "\n";
    echo "Value: " . decbin($valueMask) . "\n";
}

$ipcon = new IPConnection($host, $port); // Create IP connection to brickd
$io4 = new BrickletIO4($uid); // Create device object

$ipcon->addDevice($io4); // Add device to IP connection
// Don't use device before it is added to a connection

// Enable interrupt on pin 0  
$io4->setInterrupt(1 << 0);

// Register callback for interrupts
$io4->registerCallback(BrickletIO4::CALLBACK_INTERRUPT, 'cb_interrupt');

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
