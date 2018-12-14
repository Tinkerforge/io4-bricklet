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

	io.RegisterInterruptCallback(func(interruptMask uint8, valueMask uint8) {
		fmt.Printf("Interrupt Mask: %b\n", interruptMask)
		fmt.Printf("Value Mask: %b\n", valueMask)
		fmt.Println()
	})

	// Enable interrupt on pin 0
	io.SetInterrupt(1 << 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
