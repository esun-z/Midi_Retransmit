# Midi Retransmit

Retransmit midi messages from a device to another.

## Function

- Retransmit midi messages
- Transpose during the retransmission
- Add a latency during the retransmission

## Platform

Windows X86 (Win 32)

The GUI part is made with QT 5.15.1 (msvc2015_x64)

## Usage

Download a release and run "MidiRetransmitGUI.exe".

- First run:
  
  Make sure your devices have been connected to your PC before you run the program.
  
  Type numbers to select input and output devices and to set the transpose value and latency value.
  
  Click the button "Run".
  
  Then enjoy.
  
  (If the console program is not running correctly, you might need to check your settings including input device, output device, transpose value and latency value.)
  
- Second run:

  You can run the "MidiRetransmitGUI.exe" just like you have done before.

  Or you run "MidiRetransmit.exe", and your last setting (“MTRconfig.ini”) will be read. Check the names of input and output devices.

  - Correct devices: 

    Press enter to continue.

  - Incorrect devices: 

    Press any other key to reselect devices in the console, or close the window and run "MidiRetransmitGUI.exe" to reselect devices.

  Then enjoy.

## Included Library

- portmidi (static)
- QT