ARDUINO_DIR   = /Volumes/HDD/Arduino_Source
ARDMK_DIR     = /usr/local/opt/arduino-mk
AVR_TOOLS_DIR = /usr/local/CrossPack-AVR/
MONITOR_PORT  = /dev/ttyACM0
BOARD_TAG     = micro
ARDUINO_LIBS  = MIDIUSB Wire
ARDUINO_VERSION = 10607
CXXFLAGS_STD    = -std=gnu++11

CPPFLAGS += -DARDUINO_AVR_MICRO
CPPFLAGS += '-DUSB_MANUFACTURER="Unknown"' '-DUSB_PRODUCT="Arduino Micro"'
CPPFLAGS += -fno-threadsafe-statics

include /usr/local/opt/arduino-mk/Arduino.mk
