package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/io4_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
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

	// Get current value as bitmask.
	valueMask, _ := io.GetValue()
	fmt.Printf("Value Mask: %b\n", valueMask)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
