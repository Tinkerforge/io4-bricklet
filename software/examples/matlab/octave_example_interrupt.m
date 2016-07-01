function octave_example_interrupt()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your IO-4 Bricklet

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    io = java_new("com.tinkerforge.BrickletIO4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register interrupt callback to function cb_interrupt
    io.addInterruptCallback(@cb_interrupt);

    % Enable interrupt on pin 0
    io.setInterrupt(bitshift(1, 0));

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for interrupt callback
function cb_interrupt(e)
    fprintf("Interrupt Mask: %s\n", dec2bin(java2int(e.interruptMask)));
    fprintf("Value Mask: %s\n", dec2bin(java2int(e.valueMask)));
    fprintf("\n");
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
