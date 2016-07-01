import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletIO4;

public class ExampleInterrupt {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your IO-4 Bricklet
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletIO4 io = new BrickletIO4(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add interrupt listener
		io.addInterruptListener(new BrickletIO4.InterruptListener() {
			public void interrupt(short interruptMask, short valueMask) {
				System.out.println("Interrupt Mask: " + Integer.toBinaryString(interruptMask));
				System.out.println("Value Mask: " + Integer.toBinaryString(valueMask));
				System.out.println("");
			}
		});

		// Enable interrupt on pin 0
		io.setInterrupt((short)(1 << 0));

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
