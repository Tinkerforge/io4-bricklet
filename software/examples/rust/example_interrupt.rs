use std::{io, error::Error};
use std::thread;
use tinkerforge::{ip_connection::IpConnection, 
                  io4_bricklet::*};


const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your IO-4 Bricklet.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let io = Io4Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
    // Don't use device before ipcon is connected.

     let interrupt_receiver = io.get_interrupt_callback_receiver();

        // Spawn thread to handle received callback messages. 
        // This thread ends when the `io` object
        // is dropped, so there is no need for manual cleanup.
        thread::spawn(move || {
            for interrupt in interrupt_receiver {           
                		println!("Interrupt Mask: {:b}", interrupt.interrupt_mask);
		println!("Value Mask: {:b}", interrupt.value_mask);
		println!();
            }
        });

		// Enable interrupt on pin 0
		io.set_interrupt(1 << 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
