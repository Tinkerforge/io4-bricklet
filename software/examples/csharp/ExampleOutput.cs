using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change to your UID

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIO4 io4 = new BrickletIO4(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Set pin 1 to output low
		io4.SetConfiguration(1 << 1, 'o', false);

		// Set pin 2 and 3 to output high
		io4.SetConfiguration((1 << 2) | (1 << 3), 'o', true);

		System.Console.WriteLine("Press enter to exit");
		System.Console.ReadLine();
		ipcon.Disconnect();
	}
}
