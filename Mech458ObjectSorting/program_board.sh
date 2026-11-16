avrdude -p m2560 -c wiring -P /dev/ttyUSB0 -b 115200 -D -U flash:w:build/firmware.hex:i
