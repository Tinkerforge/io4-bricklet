function octave_example_interrupt()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "abc"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    io = java_new("com.tinkerforge.BrickletIO4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register callback for interrupts
    io.addInterruptCallback(@cb_interrupt);

    % Enable interrupt on pin 0
    io.setInterrupt(bitshift(1, 0));

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end

% Callback function for interrupts
function cb_interrupt(e)
    fprintf("Interrupt by: %s\n", dec2bin(short2int(e.interruptMask)));
    fprintf("Value: %s\n", dec2bin(short2int(e.valueMask)));
end

function int = short2int(short)
    if compare_versions(version(), "3.8", "<=")
        int = short.intValue();
    else
        int = short;
    end
end
