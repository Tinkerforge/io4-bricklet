function octave_example_output()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "abc"; % Change to your UID

    ipcon = java_new("com.tinkerforge.IPConnection"); % Create IP connection
    io = java_new("com.tinkerforge.BrickletIO4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set pin 1 to output low
    io.setConfiguration(bitshift(1, 1), "o", true);

    % Set pin 2 and 3 to output high
    io.setConfiguration(bitor(bitshift(1, 2), bitshift(1, 3)), "o", true);

    input("Press any key to exit...\n", "s");
    ipcon.disconnect();
end
