function matlab_example_interrupt()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletIO4;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'abc'; % Change to your UID
    
    ipcon = IPConnection(); % Create IP connection
    io = BrickletIO4(UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register callback for interrupts
    set(io, 'InterruptCallback', @(h, e) cb_interrupt(e));

    % Enable interrupt on pin 0
    io.setInterrupt(bitshift(1, 0));

    input('Press any key to exit...\n', 's');
    ipcon.disconnect();
end

% Callback function for interrupts
function cb_interrupt(e)
    fprintf('Interrupt by: %s\n', dec2bin(e.interruptMask));
    fprintf('Value: %s\n', dec2bin(e.valueMask));
end
