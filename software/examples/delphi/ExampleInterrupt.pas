program ExampleInterrupt;

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
    procedure InterruptCB(sender: TBrickletIO4; const interruptMask: byte; const valueMask: byte);
    procedure Execute;
  end;

const
  HOST = 'localhost';
  PORT = 4223;
  UID = '6hY'; { Change to your UID }

var
  e: TExample;

{ Callback function for interrupts }
procedure TExample.InterruptCB(sender: TBrickletIO4; const interruptMask: byte; const valueMask: byte);
begin
  WriteLn(Format('Interrupt by: %d', [interruptMask]));
  WriteLn(Format('Value: %d', [valueMask]));
end;

procedure TExample.Execute;
begin
  { Create IP connection }
  ipcon := TIPConnection.Create;

  { Create device object }
  io := TBrickletIO4.Create(UID, ipcon);

  { Connect to brickd }
  ipcon.Connect(HOST, PORT);
  { Don't use device before ipcon is connected }

  { Register callback for interrupts }
  io.OnInterrupt := {$ifdef FPC}@{$endif}InterruptCB;

  { Enable interrupt on pin 0 }
  io.SetInterrupt(1 shl 0);

  WriteLn('Press key to exit');
  ReadLn;
  ipcon.Destroy;
end;

begin
  e := TExample.Create;
  e.Execute;
  e.Destroy;
end.
