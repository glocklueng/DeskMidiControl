OS := $(shell uname)

MONITOR_PORT  = /dev/ttyACM0
ARCHITECTURE  = avr
BOARD_SUB     = atmega32u4
BOARD_TAG     = micro

ISP_PROG      = ArduinoISP
ISP_PORT      = /dev/ttyACM0

ARDUINO_VERSION = 10607
CXXFLAGS_STD    = -std=gnu++11
ARDUINO_LIBS  = MIDIUSB Wire

CPPFLAGS += -DARDUINO_AVR_MICRO
CPPFLAGS += '-DUSB_MANUFACTURER="Unknown"' '-DUSB_PRODUCT="Arduino Micro"'
CPPFLAGS += -fno-threadsafe-statics

ifeq ($(OS),Darwin)

ARDUINO_DIR   = /Volumes/HDD/Arduino_Source
ARDMK_DIR     = /usr/local/opt/arduino-mk
AVR_TOOLS_DIR = /usr/local/CrossPack-AVR/

include /usr/local/opt/arduino-mk/Arduino.mk

else

ARDUINO_DIR   = /home/rbarreiros/Projectos/Electronica/Arduino
ARDMK_DIR     = /home/rbarreiros/Projectos/Electronica/Arduino-Makefile

include /home/rbarreiros/Projectos/Electronica/Arduino-Makefile/Arduino.mk

endif
