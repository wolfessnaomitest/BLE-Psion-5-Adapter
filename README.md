# BLE-Keyboard-Adapter

An NRF52840 based keyboard controller. This was designed for use with a Psion Series 5mx keyboard.

--------------My Notes---------------
Custom fixes for nice nano ~/.platformio/packages/framework-arduinoadafruitnrf52/variants/nice_nano
Mod for compatibilty of board layout
i have a symlink here on my system for convnience 
/home/wolfessnaomi/Documents/PlatformIO/Projects/psionKeyboardNiceNano/nice_nano: symbolic link to /home/wolfessnaomi/.platformio/packages/framework-arduinoadafruitnrf52/variants/nice_nano/

Keyboard Testing Firmware

pio run -e adafruit_feather_nrf52840

Build a UF2 --this one liner is very hacky and may break ahaha
 
HEX=$(find .pio/build -name '*.hex' | head -n1)
python ~/.platformio/packages/framework-arduinoadafruitnrf52/tools/uf2conv/uf2conv.py \
  -f 0xADA52840 -c -o .pio/build/adafruit_feather_nrf52840/firmware.uf2 "$HEX"


Scan_Pinout Firmware

pio run -e scan_pinout  

HEX=$(find .pio/build/scan_pinout -name '*.hex' | head -n1)
python ~/.platformio/packages/framework-arduinoadafruitnrf52/tools/uf2conv/uf2conv.py \
  -f 0xADA52840 -c -o .pio/build/scan_pinout/firmware.uf2 "$HEX"


## References

- [Original USB Keyboard Adapter](https://github.com/RasmusB/USB-Keyboard-Adapter)
- [NiceNano V2 Documentation](https://nicekeyboards.com/)
- [Arduino Keyboard Library](https://github.com/arduino-libraries/Keyboard)
- [nrf52840 Datasheet](https://infocenter.nordicsemi.com/pdf/nRF52840_PS_v2.0.pdf)

