# TSW RailDriver Emulator

This project emulates the RailDriver controller device for use with Train Sim World (TSW), supported from TSW 2 onwards. It is written primarily in C and intended as a drop-in replacement for the `PieHid64.dll` used by TSW to interact with RailDriver hardware.

## Features

- **Emulates RailDriver hardware:** Allows users to simulate RailDriver input and output without the actual device.
- **Drop-in replacement:** Simply substitute your original `PieHid64.dll` with this emulator.
- **Logging and debugging:** Outputs logs for troubleshooting and monitoring emulator activity.
- **7 Segment Display emulation:** Creates a file reflecting the Display state that the real RailDriver would show.

## Installation

1. **Backup your original DLL:**  
   Navigate to your TSW installation directory and back up the original DLL:
   ```
   <steamapps/common>/Train Sim World 5/WindowsNoEditor/TS2Prototype/Binaries/ThirdParty/PieHid/Binaries/PieHid64.dll
   ```

2. **Replace DLL:**  
   Copy the emulator DLL from this project to the same location, replacing the original `PieHid64.dll`.

3. **Run the game:**  
   Start Train Sim World. The emulator will now be active.

## Usage

After launching Train Sim World with the emulator DLL in place, the following files will be created in:
```
<steamapps/common>/Train Sim World 5/WindowsNoEditor/TS2Prototype/Binaries/Win64/
```
- `raildriver_input`: Allows you to change the emulator output. You can overwrite this file to modify RailDriver input.  
  **Data structure details:** [Collem.nl RailDriver input file format](https://www.collem.nl/x-keys/non-PC/rdreport.htm)
- `raildriver_emulator_log.txt`: Contains debug and info output for troubleshooting.
- `raildriver_leds.txt`: Shows either "---" or the current speed of your train, as the real RailDriver LED display would.

## Troubleshooting

- Check `raildriver_emulator_log.txt` for debug and info logs if the emulator is not functioning as expected.
- Make sure Train Sim World is fully closed before replacing the DLL.

## License

This project is licensed under the [MIT License](LICENSE).


## Disclaimer

This project is not affiliated with or endorsed by Dovetail Games or the makers of Train Sim World. Use at your own risk.