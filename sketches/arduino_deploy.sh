#!/usr/bin/env bash
./set_arduino_sketchbook_path.sh && \
arduino --board arduino:avr:mega --port /dev/ttyACM0 --upload $1
