using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "ABC"; // Change to your UID

	static void Main() 
	{
		IPConnection ipcon = new IPConnection(HOST, PORT); // Create connection to brickd
		BrickletIO4 io4 = new BrickletIO4(UID); // Create device object
		ipcon.AddDevice(io4); // Add device to ip connection
		// Don't use device before it is added to a connection


		// Set pin 1 to output low
		io4.SetConfiguration(1 << 1, 'o', false);

		// Set pin 2 and 3 to output high
		io4.SetConfiguration((1 << 2) | (1 << 3), 'o', true);

		System.Console.WriteLine("Press ctrl+c to exit");
		ipcon.JoinThread();
    }
}
