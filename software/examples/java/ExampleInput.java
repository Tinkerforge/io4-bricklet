import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletIO4;

public class ExampleInput {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;
	private static final String UID = "XYZ"; // Change to your UID

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIO4 io = new BrickletIO4(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current value as bitmask
		short valueMask = io.getValue(); // Can throw com.tinkerforge.TimeoutException
		System.out.println("Value Mask: " + Integer.toBinaryString(valueMask));

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
