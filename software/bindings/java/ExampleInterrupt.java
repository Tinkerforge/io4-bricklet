import com.tinkerforge.BrickletIO4;
import com.tinkerforge.IPConnection;

public class ExampleInterrupt {
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
		

		// Enable interrupt on pin 0
		io4.setInterrupt((short)(1 << 0));

		// Add and implement listener for interrupt (called if pin 0 changes)
		io4.addListener(new BrickletIO4.InterruptListener() {
			public void interrupt(short interruptMask, short valueMask) {
				System.out.println("Interrupt by: " + Integer.toBinaryString(interruptMask));
				System.out.println("Value: " + Integer.toBinaryString(valueMask));
			}
		});
		
		System.out.println("Press ctrl+c to exit");
		ipcon.joinThread();
	}
}
