#pragma once

/*
 board.h

 List all the pins that are connected to your keyboard.
*/

#define NPINS 20    // Number of pins connected to the keyboard.

// This is a list of all pins that are connected to the keyboard.
const int Pin[NPINS] = {
  D0,  D1,  D2,  D3,  D4,
  D5,  D6,  D7,  D8,  D9,
  D10, D11, D12, D13, D14,
  D15, D16, D17, D19, D20
};

// Names for the physical board pins used by the keyboard.
// Update these labels if your wiring changes.
const char* pinName[] = {
  "COL_12", // 0
  "COL_11", // 1
  "COL_10", // 2
  "COL_09", // 3
  "COL_08", // 4
  "COL_07", // 5
  "COL_06", // 6
  "COL_05", // 7
  "COL_04", // 8
  "COL_03", // 9
  "COL_02", // 10
  "ROW_08", // 11
  "ROW_07", // 12
  "ROW_06", // 13
  "COL_01", // 14
  "ROW_05", // 15
  "ROW_04", // 16
  "ROW_03", // 17
  "-",      // 18
  "ROW_01", // 19
  "ROW_02", // 20
  "-",      // 21
  "-",      // 22
  "-",      // 23
  "-",      // 24
  "-",      // 25
  "-",      // 26
  "-",      // 27
  "-",      // 28
  "-",      // 29
  "-"       // 30
};
