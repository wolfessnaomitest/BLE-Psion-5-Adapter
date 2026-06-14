#include <Arduino.h>
#include <bluefruit.h>
#include "board.h"

#define LED_PIN LED_BUILTIN
#define PAIRING_LED_INTERVAL 250

BLEDis bledis;
BLEHidAdafruit blehid;
BLEUart bleuart;

static bool bleConnected = false;
static unsigned long pairingPrevious = 0;
static bool pairingLedState = false;

void connect_callback(uint16_t conn_handle) {
  (void) conn_handle;
  bleConnected = true;
  digitalWrite(LED_PIN, HIGH);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  (void) conn_handle;
  (void) reason;
  bleConnected = false;
  digitalWrite(LED_PIN, LOW);
}

void startAdv(void) {
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_GENERIC_COMPUTER);
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void printPinMapping(void) {
  bleuart.println("Pin mapping:");
  for (int i = 0; i <= 30; i++) {
    bleuart.print(i);
    bleuart.print(": ");
    bleuart.println(pinName[i]);
  }
  while (bleuart.available()) {
    bleuart.read();
  }
  bleuart.println("--------");
}

void scanMatrix(void) {
  // Reset all pins to INPUT (high-Z)
  for (int i = 0; i < NPINS; i++) {
    pinMode(Pin[i], INPUT);
  }
  delayMicroseconds(100);

  // Temporary storage for found connections
  const int MAX_FOUND = 256;
  int foundSense[MAX_FOUND];
  int foundSelect[MAX_FOUND];
  int foundCount = 0;

  // Main scan - collect connections into arrays (no UART prints here)
  for (int i = 0; i < NPINS; i++) {
    pinMode(Pin[i], INPUT_PULLUP);
    delayMicroseconds(50);

    for (int j = 0; j < NPINS; j++) {
      if (i == j) continue;

      // If sense pin is already LOW it's an error; skip this pair
      if (digitalRead(Pin[i]) == LOW) {
        continue;
      }

      pinMode(Pin[j], OUTPUT);
      digitalWrite(Pin[j], LOW);
      delayMicroseconds(50);

      // Debounced read
      if (digitalRead(Pin[i]) == LOW) {
        delayMicroseconds(10);
        if (digitalRead(Pin[i]) == LOW && Pin[i] > Pin[j]) {
          if (foundCount < MAX_FOUND) {
            foundSense[foundCount] = Pin[i];
            foundSelect[foundCount] = Pin[j];
            foundCount++;
          }
        }
      }

      pinMode(Pin[j], INPUT);
      delayMicroseconds(20);
    }

    pinMode(Pin[i], INPUT);
    delayMicroseconds(20);
  }

  // Only report results when at least one connection was found
  if (foundCount > 0 && bleConnected) {
    // Send a short header first
    char head[32];
    snprintf(head, sizeof(head), "CONN:%d", foundCount);
    bleuart.println(head);

    // Send connection data in small chunks to avoid BLE notification fragmentation/truncation
    const int CHUNK_SIZE = 100;
    char chunk[CHUNK_SIZE];
    int cpos = 0;

    for (int k = 0; k < foundCount; k++) {
      char entry[64];
      int en = snprintf(entry, sizeof(entry), "%d(%s),%d(%s);",
                        foundSense[k], pinName[foundSense[k]],
                        foundSelect[k], pinName[foundSelect[k]]);
      if (en <= 0) continue;

      // If entry doesn't fit into remaining chunk space, flush current chunk
      if (cpos + en + 1 >= CHUNK_SIZE) {
        chunk[cpos] = '\0';
        bleuart.println(chunk);
        cpos = 0;
      }

      // Append entry to chunk
      memcpy(chunk + cpos, entry, (size_t)en);
      cpos += en;
    }

    // Flush remaining chunk
    if (cpos > 0) {
      chunk[cpos] = '\0';
      bleuart.println(chunk);
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  for (int i = 0; i < NPINS; i++) {
    pinMode(Pin[i], INPUT);
  }

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("ScanPinout");
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  bledis.setManufacturer("nice!");
  bledis.setModel("ScanPinout");
  bledis.begin();
  blehid.begin();
  bleuart.begin();
  startAdv();
}

void loop() {
  if (bleConnected) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    if (millis() - pairingPrevious >= PAIRING_LED_INTERVAL) {
      pairingPrevious = millis();
      pairingLedState = !pairingLedState;
      digitalWrite(LED_PIN, pairingLedState ? HIGH : LOW);
    }
  }

  static unsigned long lastScan = 0;
  if (millis() - lastScan >= 100) {
    lastScan = millis();
    scanMatrix();
  }
}