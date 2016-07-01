Imports System
Imports Tinkerforge

Module ExampleOutput
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your IO-4 Bricklet

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim io As New BrickletIO4(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Set pin 1 to output low
        io.SetConfiguration(1 << 1, "o"C, False)

        ' Set pin 2 and 3 to output high
        io.SetConfiguration((1 << 2) or (1 << 3), "o"C, True)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
