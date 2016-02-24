#include <Arduino.h>
#include <MIDIUSB.h>

//#include "ConfigUSB.h"
#include "bombatuino_MIDI.h"
#include "bombatuino_INPUT_74HC4051.h"
#include "bombatuino_INPUT_MCP23017.h"
#include "bombatuino_ROTARY_ENCODER.h"

// Globals
//MIDI Midi; // Uses Serial ?!
// Input 74hc4051 array
//INPUT_74HC4051 gPotMux[4];
// Input MCP array
//INPUT_MCP23017 gButtonMux[4];
// Encoders MCP - 2 Encoders each MCP
//INPUT_MCP23017 gEncoder[2];

// Rotary Encoders
/*
void rotaryEncoder1Inc(void);
void rotaryEncoder1Dec(void);
void rotaryEncoder2Inc(void);
void rotaryEncoder2Dec(void);
void rotaryEncoder3Inc(void);
void rotaryEncoder3Dec(void);
void rotaryEncoder4Inc(void);
void rotaryEncoder4Dec(void);

ROTARY_ENCODER rotaryEncoder1(rotaryEncoder1Inc, rotaryEncoder1Dec); //input_MCP23017_1 pins 6 and 7
ROTARY_ENCODER rotaryEncoder2(rotaryEncoder2Inc, rotaryEncoder2Dec); //input_MCP23017_3 pins 9 and 1
ROTARY_ENCODER rotaryEncoder3(rotaryEncoder3Inc, rotaryEncoder3Dec); //input_MCP23017_3 pins 5 and 6
ROTARY_ENCODER rotaryEncoder4(rotaryEncoder4Inc, rotaryEncoder4Dec); //input_MCP23017_3 pins 5 and 6
*/

void setupUSB() __attribute__((weak));
void setupUSB() { }

int midiChannel = 1;

// Callbacks

void analogCallback(int id, int pin, int value)
{

  // MIDI event, MIDI Event | Midi Channel, CC number, CC value
  midiEventPacket_t evt = { MIDI_CONTROL_CHANGE,
                            (uint8_t)(MIDI_CONTROL_CHANGE | midiChannel),
                            (uint8_t)((id-A0) * 8 + pin),
                            (uint8_t)value};
  MidiUSB.sendMIDI(evt);

}

void buttonCallBack(int id, int pin, int value)
{
  /*
  uint8_t note;
  if(value == HIGH)
    note = MIDI_NOTE_ON;
  else
    note = MIDI_NOTE_OFF;

  midiEventPacket_t evt = { note, (uint8_t)(note | midiChannel),
                            (uint8_t)(id * 16 + pin), MIDI_MAX_DATA };
  MidiUSB.sendMIDI(evt);
  */
}

void encoderCallback1(int id, int pin, int value)
{

}

void encoderCallback2(int id, int pin, int value)
{

}

void rotaryEncoder1Inc(void)
{

}

void rotaryEncoder1Dec(void)
{

}

void rotaryEncoder2Inc(void)
{

}

void rotaryEncoder2Dec(void)
{

}

void rotaryEncoder3Inc(void)
{

}

void rotaryEncoder3Dec(void)
{

}

void rotaryEncoder4Inc(void)
{

}

void rotaryEncoder4Dec(void)
{

}

// Setup
/*
void setupPotentiometers(void)
{
  gPotMux[0].begin(A0, 7, 8, 9, analogCallback);
  gPotMux[1].begin(A1, 7, 8, 9, analogCallback);
  gPotMux[2].begin(A2, 7, 8, 9, analogCallback);
  gPotMux[3].begin(A3, 7, 8, 9, analogCallback);
}

void setupButtons(void)
{
  gButtonMux[0].begin(0, buttonCallBack);
  gButtonMux[1].begin(1, buttonCallBack);
  gButtonMux[2].begin(2, buttonCallBack);
  gButtonMux[3].begin(3, buttonCallBack);
}

void setupEncoders(void)
{
  gEncoder[0].begin(6, encoderCallback1);
  gEncoder[1].begin(7, encoderCallback2);
}
*/

int main(void)
{
  init();
  
#if defined(USBCON)
  USBDevice.attach();
#endif

  // Setup Serial
  Serial.begin(115200);
  
  Serial.println("Setting up potentiometers");
  //setupPotentiometers();
  Serial.println("Setting up buttons");
  //setupButtons();
  
  Serial.println("Setup done");
  
  //configPacket_t cfg = {0};
  //cfg.cmd = 0x00;
  
  for (;;) {
    //for(int i = 0; i < 4; i++) gPotMux[i].loop();
    //for(int i = 0; i < 4; i++) gButtonMux[i].loop();
    
    //cfg.cmd++;
    //ConfigUSB.send(cfg);
    //Serial.print("Sent ");
    //Serial.println(cfg.cmd);
    
    //configPacket_t cfg = ConfigUSB.read();
    /*
      do
      {
      Serial1.println("Received USB Data");
      Serial1.print("Command: ");
      Serial1.println(cfg.cmd, HEX);
      Serial1.print("Data: ");
      for(int i = 0; i < 32; i++)
      {
      Serial1.print(cfg.data[i], HEX);
      Serial1.print(" ");
      }
      Serial1.println("");
      } while(cfg.cmd != 0);
    */
    
    if (serialEventRun) serialEventRun();
  }
  
  return 0;
}
