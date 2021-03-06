#!/usr/bin/env bash
./set_arduino_sketchbook_path.sh && \
arduino --board arduino:avr:nano --port /dev/ttyUSB0 --verify $1