function octave_example_interrupt
    more off;
    
    HOST = "localhost";
    PORT = 4223;
    UID = "abc"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    io = java_new("com.tinkerforge.BrickletIO4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register callback for interrupts
    io.addInterruptListener("cb_interrupt");

    % Enable interrupt on pin 0
    io.setInterrupt(bitshift(1, 0));

    input("\nPress any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for interrupts
function cb_interrupt(interrupt_mask, value_mask)
    interrupt_mask = str2num(interrupt_mask.toString());
    value_mask = str2num(value_mask.toString());
    fprintf("Interrupt by: %s\n", dec2bin(interrupt_mask));
    fprintf("Value: %s\n", dec2bin(value_mask));
end
