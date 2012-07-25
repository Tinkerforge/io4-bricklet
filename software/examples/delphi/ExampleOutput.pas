program ExampleOutput;

{$ifdef MSWINDOWS}{$apptype CONSOLE}{$endif}
{$ifdef FPC}{$mode OBJFPC}{$H+}{$endif}

uses
  SysUtils, IPConnection, BrickletIO4;

type
  TExample = class
  private
    ipcon: TIPConnection;
    io: TBrickletIO4;
  public
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '6hY';

var
  e: TExample;

procedure TExample.Execute;
begin
  { Create IP connection to brickd }
  ipcon := TIPConnection.Create(HOST, PORT);

  { Create device object }
  io := TBrickletIO4.Create(UID);

  { Add device to IP connection }
  ipcon.AddDevice(io);
  { Don't use device before it is added to a connection }

  { Set pin 1 to output low }
  io.SetConfiguration(1 shl 1, 'o', false);

  { Set pin 2 and 3 to output high }
  io.SetConfiguration((1 shl 2) or (1 shl 3), 'o', true);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
