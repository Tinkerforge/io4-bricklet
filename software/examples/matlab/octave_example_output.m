function octave_example_output()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your IO-4 Bricklet

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    io = javaObject("com.tinkerforge.BrickletIO4", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Set pin 1 to output low
    io.setConfiguration(bitshift(1, 1), "o", false);

    % Set pin 2 and 3 to output high
    io.setConfiguration(bitor(bitshift(1, 2), bitshift(1, 3)), "o", true);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
