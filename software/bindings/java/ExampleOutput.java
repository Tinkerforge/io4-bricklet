import com.tinkerforge.BrickletIO4;
import com.tinkerforge.IPConnection;

public class ExampleOutput {
	private static final String host = new String("localhost");
	private static final int port = 4223;
	private static final String UID = new String("ABC"); // Change to your UID
	
	// Note: To make the example code cleaner we do not handle exceptions. Exceptions you
	//       might normally want to catch are described in the commnents below
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(host, port); // Create connection to brickd (Can throw IOException)

		BrickletIO4 io4 = new BrickletIO4(UID); // Create device object
		ipcon.addDevice(io4); // Add device to ip connection (Can throw IPConnection.TimeoutException)
		// Don't use device before it is added to a connection
		

		// Set pin 1 output low
		io4.setConfiguration((short)(1 << 1), 'o', false);

		// Set pin 2 and 3 to output high
		io4.setConfiguration((short)((1 << 2) | (1 << 3)), 'o', true);
		
		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
