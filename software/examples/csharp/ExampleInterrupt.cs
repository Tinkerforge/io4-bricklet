using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "ABC"; // Change to your UID

	// Callback function for interrupts
	static void InterruptCB(BrickletIO4 sender, byte interruptMask, byte valueMask)
	{
		string interruptBinary = System.Convert.ToString(interruptMask, 2);
		string valueBinary = System.Convert.ToString(valueMask, 2);

		System.Console.WriteLine("Interrupt by: " + interruptBinary);
		System.Console.WriteLine("Value: " + valueBinary);
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIO4 io4 = new BrickletIO4(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register callback for interrupts
		io4.Interrupt += InterruptCB;

		// Enable interrupt on pin 0
		io4.SetInterrupt(1 << 0);

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
