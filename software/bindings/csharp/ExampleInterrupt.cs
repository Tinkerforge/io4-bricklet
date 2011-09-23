using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "ABC"; // Change to your UID

	// Callback function for interrupts
	static void InterruptCB(byte interruptMask, byte valueMask)
	{
		string interruptBinary = System.Convert.ToString(interruptMask, 2);
		string valueBinary = System.Convert.ToString(valueMask, 2);

		System.Console.WriteLine("Interrupt by: " + interruptBinary);
		System.Console.WriteLine("Value: " + valueBinary);
	}

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickletIO4 io4 = new BrickletIO4(UID); // Create device object
		ipcon.AddDevice(io4); // Add device to ip connection
		// Don't use device before it is added to a connection

		// Enable interrupt on pin 0
		io4.SetInterrupt(1 << 0);

		// Register callback for interrupts
		io4.RegisterCallback(new BrickletIO4.Interrupt(InterruptCB));

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
    }
}
