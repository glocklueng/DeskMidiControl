
#include "ConfigUSB.h"

const char configUsbDescriptor[] = {
  18, // sizeof(configUsbDescriptor)
  1, // USBDESCR_DEVICE
  0x10, 0x01, // USB Version Supported
  0xff, // USB_CFG_DEVICE_CLASS
  0, // USB_CFG_DEVICE_SUBCLASS
  0, // Protocol
  8, // Max Packet size
  0xc0, 0x16, // USB_CFG_VENDOR_ID
  0x08, 0x3e, // USB_CFG_DEVICE_ID
  0x00, 0x01, // USB_CFG_DEVICE_VERSION
  0, // USB_CFG_DESCR_PROPS_STRING_VENDOR
  0, // USB_CFG_DESCR_PROPS_STRING_PRODUCT
  0, // USB_CFG_DESCR_PROPS_STRING_SERIAL_NUMBER
  1
};

ConfigUSB_::ConfigUSB_(void)
  : PluggableUSBModule(2, 2, epType)
{
  epType[0] = EP_TYPE_BULK_OUT;
  epType[1] = EP_TYPE_BULK_IN;
  PluggableUSB().plug(this);
}

bool ConfigUSB_::setup(USBSetup &setup __attribute__((unused)))
{
  return false;
}

int ConfigUSB_::getDescriptor(USBSetup &setup __attribute__((unused)))
{
  return 0;
}

int ConfigUSB_::getInterface(uint8_t *interfaceNum)
{
  interfaceNum[0] += 2;
  return USB_Control(0, )
}
