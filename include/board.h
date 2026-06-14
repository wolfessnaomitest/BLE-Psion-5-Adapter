/*
 * board.h
 * 
 * Pin configuration for NiceNanoV2 nrf52840 with Psion Keyboard
 * 
 * Matrix: 8 rows x 12 columns
 */

#ifndef BOARD_H
#define BOARD_H

// Matrix dimensions (Psion keyboard is 8 rows x 12 columns)
#define NROWS 8
#define NCOLS 12

// Row pin definitions (nrf52840 GPIO pins)
#define ROW_01 D19
#define ROW_02 D20
#define ROW_03 D17
#define ROW_04 D16
#define ROW_05 D15
#define ROW_06 D13
#define ROW_07 D12
#define ROW_08 D11

// Column pin definitions (nrf52840 GPIO pins)
#define COL_1  D14
#define COL_2  D10
#define COL_3  D9
#define COL_4  D8
#define COL_5  D7
#define COL_6  D6
#define COL_7  D5
#define COL_8  D4
#define COL_9  D3
#define COL_10 D2
#define COL_11 D1
#define COL_12 D0

// Row array
static const int Rows[NROWS] = {
  ROW_01, ROW_02, ROW_03, ROW_04,
  ROW_05, ROW_06, ROW_07, ROW_08
};

// Column array
static const int Cols[NCOLS] = {
  COL_1, COL_2, COL_3, COL_4, COL_5, COL_6,
  COL_7, COL_8, COL_9, COL_10, COL_11, COL_12
};

// row/column labels derived from scan_pinout wiring
static const char* RowNames[NROWS] = {
  "ROW_01", "ROW_02", "ROW_03", "ROW_04",
  "ROW_05", "ROW_06", "ROW_07", "ROW_08"
};

static const char* ColNames[NCOLS] = {
  "COL_1", "COL_2", "COL_3", "COL_4", "COL_5", "COL_6",
  "COL_7", "COL_8", "COL_9", "COL_10", "COL_11", "COL_12"
};

// Status LED
#define LED_STATUS LED_BUILTIN

#endif // BOARD_H
