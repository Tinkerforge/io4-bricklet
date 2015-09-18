using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	// Callback function for interrupt callback
	static void InterruptCB(BrickletIO4 sender, byte interruptMask, byte valueMask)
	{
		Console.WriteLine("Interrupt Mask: " + Convert.ToString(interruptMask, 2));
		Console.WriteLine("Value Mask: " + Convert.ToString(valueMask, 2));
		Console.WriteLine("");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIO4 io = new BrickletIO4(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register interrupt callback to function InterruptCB
		io.Interrupt += InterruptCB;

		// Enable interrupt on pin 0
		io.SetInterrupt(1 << 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
