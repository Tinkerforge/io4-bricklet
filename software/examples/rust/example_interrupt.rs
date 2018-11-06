use std::{error::Error, io, thread};
use tinkerforge::{io4_bricklet::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your IO-4 Bricklet

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let io4_bricklet = IO4Bricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for interrupt events.
    let interrupt_listener = io4_bricklet.get_interrupt_receiver();
    // Spawn thread to handle received events. This thread ends when the io4_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in interrupt_listener {
            println!("Interrupt Mask: {:b}", event.interrupt_mask);
            println!("Value Mask: {:b}", event.value_mask);
            println!();
        }
    });

    // Enable interrupt on pin 0
    io4_bricklet.set_interrupt(1 << 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
