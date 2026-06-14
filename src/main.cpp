#include <Arduino.h>
#include <bluefruit.h>
#include "board.h"
#include "PsionKeymapUSB.h"

// Max number of scans/second
#define MAX_SCAN_RATE 200
#define PAIRING_LED_INTERVAL 250

// BLE objects
BLEDis bledis;
BLEHidAdafruit blehid;
BLEUart bleuart;

// Connection state
static bool bleConnected = false;
static bool keyPressedPreviously = false;

// Key state tracking
static uint8_t keypressArrayCurrent[NROWS][NCOLS];
static uint8_t keypressArrayPrevious[NROWS][NCOLS];

// Timing
static unsigned long previousTime = 0;
static unsigned int minDelay;
static unsigned long pairingPrevious = 0;
static bool pairingLedState = false;


// Forward declarations
int scanKeyboard(uint8_t keyArray[][NCOLS]);
void sendBleKeyReport(uint8_t pressedArray[][NCOLS], uint8_t previousArray[][NCOLS]);
void startAdv(void);

void connect_callback(uint16_t conn_handle) {
  (void) conn_handle;
  bleConnected = true;
  digitalWrite(LED_STATUS, HIGH);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  (void) conn_handle;
  (void) reason;
  bleConnected = false;
  digitalWrite(LED_STATUS, LOW);
}

void setup() {
  // Initialize timing
  previousTime = 0;
  minDelay = 1000 / MAX_SCAN_RATE;

  // Initialize LED
  pinMode(LED_STATUS, OUTPUT);
  digitalWrite(LED_STATUS, LOW);

  // Initialize keyboard matrix - rows as inputs (high-Z)
  for (int i = 0; i < NROWS; i++) {
    pinMode(Rows[i], INPUT);
  }

  // Initialize columns as inputs
  for (int i = 0; i < NCOLS; i++) {
    pinMode(Cols[i], INPUT);
  }

  // Clear key arrays
  memset(keypressArrayCurrent, 0, sizeof(keypressArrayCurrent));
  memset(keypressArrayPrevious, 0, sizeof(keypressArrayPrevious));

  // Initialize BLE HID
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("NiceNano");
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  bledis.setManufacturer("nice!");
  bledis.setModel("NiceNano");
  bledis.begin();
  blehid.begin();
  // BLE UART for debug logging
  bleuart.begin();
  startAdv();
}

void loop() {

  // Throttle scanning to MAX_SCAN_RATE
  if ((millis() - previousTime) >= minDelay) {
    // Scan the keyboard matrix
    scanKeyboard(keypressArrayCurrent);

    if (bleConnected) {
      digitalWrite(LED_STATUS, HIGH);
    } else {
      if (millis() - pairingPrevious >= PAIRING_LED_INTERVAL) {
        pairingPrevious = millis();
        pairingLedState = !pairingLedState;
        digitalWrite(LED_STATUS, pairingLedState ? HIGH : LOW);
      }
    }

    if (bleConnected) {
      sendBleKeyReport(keypressArrayCurrent, keypressArrayPrevious);
    } else {
      keyPressedPreviously = false;
    }

    // Save current state for next iteration
    memcpy(keypressArrayPrevious, keypressArrayCurrent, sizeof(keypressArrayCurrent));

    previousTime = millis();
  }
}

void startAdv(void) {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

/**
 * Scan the keyboard matrix and populate the keyArray
 * Returns the number of keys currently pressed
 */
int scanKeyboard(uint8_t keyArray[][NCOLS]) {
  int nKeysPressed = 0;

  // Clear the key array
  memset(keyArray, 0, sizeof(uint8_t) * NROWS * NCOLS);

  // For each row
  for (int row = 0; row < NROWS; row++) {

    // Activate all column pull-ups before selecting the row
    for (int col = 0; col < NCOLS; col++) {
      pinMode(Cols[col], INPUT_PULLUP);
    }

    // Set this row to OUTPUT LOW (active) - sink current
    pinMode(Rows[row], OUTPUT);
    digitalWrite(Rows[row], LOW);

    // Delay to let the signal settle and the matrix lines stabilize
    delayMicroseconds(1000);

    // Read all columns for the active row
    for (int col = 0; col < NCOLS; col++) {
      if (keyScancode[row][col] != 0) {
        int firstRead = digitalRead(Cols[col]);
        delayMicroseconds(5);
        int secondRead = digitalRead(Cols[col]);

        if (firstRead == LOW && secondRead == LOW) {
          keyArray[row][col] = 1;
          nKeysPressed++;
        } else {
          keyArray[row][col] = 0;
        }
      }
    }

    // Deactivate the row and release the columns
    pinMode(Rows[row], INPUT);
    for (int col = 0; col < NCOLS; col++) {
      pinMode(Cols[col], INPUT);
    }

    // Delay to allow the matrix to fully settle before the next row scan
    delayMicroseconds(2000);
  }

  return nKeysPressed;
}

void sendBleKeyReport(uint8_t pressedArray[][NCOLS], uint8_t previousArray[][NCOLS]) {
  uint8_t modifier = 0;
  uint8_t keycode[6] = { 0 };
  uint8_t keyIndex = 0;

  for (int row = 0; row < NROWS && keyIndex < 6; row++) {
    for (int col = 0; col < NCOLS && keyIndex < 6; col++) {
      if (keyScancode[row][col] != 0 && pressedArray[row][col] > 0) {
        uint8_t code = keyScancode[row][col];
        // If this is a new press (was not pressed previously), log over BLE UART
        if (previousArray[row][col] == 0 && bleConnected) {
          // Format: P 0xHH
          char buf[32];
          snprintf(buf, sizeof(buf), "P 0x%02X", code);
          bleuart.println(buf);
        }
        switch (code) {
          case 0xE0: modifier |= HID_MOD_LCTRL; break;
          case 0xE1: modifier |= HID_MOD_LSHIFT; break;
          case 0xE2: modifier |= HID_MOD_LALT; break;
          case 0xE5: modifier |= HID_MOD_RSHIFT; break;
          case 0xE6: modifier |= HID_MOD_RALT; break;
          default:
            keycode[keyIndex++] = code;
            break;
        }
      }
    }
  }

  if (bleConnected) {
    blehid.keyboardReport(modifier, keycode);
  }
}