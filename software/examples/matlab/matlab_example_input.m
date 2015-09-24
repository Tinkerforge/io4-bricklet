function matlab_example_input()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletIO4;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change to your UID

    ipcon = IPConnection(); % Create IP connection
    io = BrickletIO4(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current value as bitmask
    valueMask = io.getValue();
    fprintf('Value Mask: %s\n', dec2bin(valueMask));

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
