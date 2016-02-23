#ifndef __CONFIGUSB_H__
#define __CONFIGUSB_H__

#include <PluggableUSB.h>

typedef struct
{
  uint8_t cmd;
  uint8_t data[32];
} configPacket_t;

// This is only for ATMega32u4 therefore, ARDUINO_ARCH_AVR
#define EPTYPE_DESCRIPTOR_SIZE  uint8_t
#define EP_TYPE_BULK_IN_CONFIG  EP_TYPE_BULK_IN
#define EP_TYPE_BULK_OUT_CONFIG EP_TYPE_BULK_OUT
#define CONFIG_BUFFER_SIZE      USB_EP_SIZE
#define is_write_enabled(x)     (1)

typedef struct
{
  ConfigDescriptor    Config;
  InterfaceDescriptor VendorInterface;
  EndpointDescriptor  VendorEndpointIn;
  EndpointDescriptor  VendorEndpointOut;
} CONFIGDescriptor;

class ConfigUSB_ : public PluggableUSBModule
{
public:
  ConfigUSB_(void);
  configPacket_t read(void);
  uint32_t available(void);
  void flush(void);
  void send(configPacket_t cfg);
  size_t write(const uint8_t *buffer, size_t size);
  
protected:
  bool setup(USBSetup &setup);
  int getDescriptor(USBSetup &setup);
  int getInterface(uint8_t *interfaceNum);

private:
  void accept(void);
  uint8_t epType[2];
};

extern ConfigUSB_ ConfigUSB;


#endif
