# Scan Pinout Helper

This helper project is based on the ScanTheMatrix approach from:
https://github.com/RasmusB/USB-Keyboard-Adapter/tree/master/ScanTheMatrix

## Purpose

Use this sketch to derive and verify your keyboard pinout by scanning for direct connections between the pins used by your keyboard matrix.

## Build and upload

From the project root:

```bash
pio run -e scan_pinout -t upload
```

## Serial output

Open a serial monitor at `9600` baud. The sketch prints the current pin mapping when any character is received on the serial port.

When keys are pressed one at a time, the sketch reports lines like:

```text
Found connection, pins 3 (COL_09) and 19 (ROW_01)
```

## Pin definitions

The `include/board.h` file lists the 20 NiceNano pins connected to the keyboard.
Update `Pin[]` and `pinName[]` if your wiring changes.
