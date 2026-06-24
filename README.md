# BLE-Keyboard-Adapter

An NRF52840 based keyboard controller. This was designed for use with a Psion Series 5mx keyboard.

Keyboard Firmware

```
pio run -e adafruit_feather_nrf52840
```

Build a UF2 --this one liner is very hacky and may break ahaha

``` 
HEX=$(find .pio/build -name '*.hex' | head -n1)
python ~/.platformio/packages/framework-arduinoadafruitnrf52/tools/uf2conv/uf2conv.py \
  -f 0xADA52840 -c -o .pio/build/adafruit_feather_nrf52840/firmware.uf2 "$HEX"
```

Scan_Pinout Firmware

```
cd scan_pinout
pio run -escan_pinout
```

```
HEX=$(find .pio/build/scan_pinout -name '*.hex' | head -n1)
python ~/.platformio/packages/framework-arduinoadafruitnrf52/tools/uf2conv/uf2conv.py \
  -f 0xADA52840 -c -o .pio/build/scan_pinout/firmware.uf2 "$HEX"
```


## References

- [Original USB Keyboard Adapter](https://github.com/RasmusB/USB-Keyboard-Adapter)
- [NiceNano V2 Documentation](https://nicekeyboards.com/)
- [NiceNano In PlatformIO with Adafruit Stuff](https://github.com/selimmeric/Adafruit_nRF52_Arduino_Nice-NanoV2)
- [Adafruit nRFCrypto](https://github.com/adafruit/Adafruit_nRFCrypto)
- [nrf52840 Datasheet](https://infocenter.nordicsemi.com/pdf/nRF52840_PS_v2.0.pdf)

  ## I dont really know how github works very well but hey here is some useless uncompressed images of my build

  <img src="https://github.com/wolfessnaomitest/BLE-Psion-5-Adapter/blob/master/IMG_20260622_143010299.jpg">
  <img src="https://github.com/wolfessnaomitest/BLE-Psion-5-Adapter/blob/master/IMG_20260622_140712224.jpg">

