package main

import (
	"fmt"
	"tinkerforge/io4_bricklet"
	"tinkerforge/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your IO-4 Bricklet.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	io, _ := io4_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	// Set pin 1 to output low
	io.SetConfiguration(1<<1, 'o', false)

	// Set pin 2 and 3 to output high
	io.SetConfiguration((1<<2)|(1<<3), 'o', true)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
