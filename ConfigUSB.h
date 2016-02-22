#ifndef __CONFIGUSB_H__
#define __CONFIGUSB_H__

#include "PluggableUSB.h"

class ConfigUSB_ : public PluggableUSBModule
{
public:
  ConfigUSB_(void);

protected:
  bool setup(USBSetup &setup);
  int getDescriptor(USBSetup &setup);
  int getInterface(uint8_t *interfaceNum);

private:
  uint8_t epType[2];
};

extern ConfigUSB_ ConfigUSB;


#endif
