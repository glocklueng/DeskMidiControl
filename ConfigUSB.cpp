
#include "ConfigUSB.h"

#define CONFIG_INTERFACE      pluggedInterface

#define CONFIG_FIRST_ENDPOINT pluggedEndpoint
#define CONFIG_ENDPOINT_OUT   pluggedEndpoint
#define CONFIG_ENDPOINT_IN    pluggedEndpoint+1

#define CONFIG_RX CONFIG_ENDPOINT_OUT
#define CONFIG_TX CONFIG_ENDPOINT_IN

struct ring_bufferConfig
{
  configPacket_t cfg[CONFIG_BUFFER_SIZE];
  volatile uint32_t head;
  volatile uint32_t tail;
};

ring_bufferConfig cfg_rx_buffer = {0};

ConfigUSB_ ConfigUSB;

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

  CONFIGDescriptor cfgInterface =
  {
    D_INTERFACE(CONFIG_INTERFACE, 2, 0xFF, 0xFF, 0xFF),
    D_ENDPOINT(USB_ENDPOINT_IN(pluggedEndpoint+1), USB_ENDPOINT_TYPE_BULK, CONFIG_BUFFER_SIZE, 0x05),
    D_ENDPOINT(USB_ENDPOINT_OUT(pluggedEndpoint), USB_ENDPOINT_TYPE_BULK, CONFIG_BUFFER_SIZE, 0x05)
  };
  
  return USB_SendControl(0, &cfgInterface, sizeof(cfgInterface));
}

configPacket_t ConfigUSB_::read(void)
{
  configPacket_t c;
  ring_bufferConfig *buffer = &cfg_rx_buffer;

  if(((uint32_t)(CONFIG_BUFFER_SIZE + buffer->head - buffer->tail) % CONFIG_BUFFER_SIZE) > 0)
  {
    c = buffer->cfg[buffer->tail];
  } else {
    if (USB_Available(CONFIG_RX)) {
      accept();
      c = buffer->cfg[buffer->tail];
    } else {
      c.cmd = 0;
      c.data1 = 0;
      c.data2 = 0;
      c.data3 = 0;
    }
  }
  // if the head isn't ahead of the tail, we don't have any characters
  if (buffer->head != buffer->tail)
  {
    buffer->tail = (uint32_t)(buffer->tail + 1) % CONFIG_BUFFER_SIZE;
  }
  return c;
}

uint32_t ConfigUSB_::available(void)
{
  ring_bufferConfig *buffer = &cfg_rx_buffer;
  return (uint32_t)(CONFIG_BUFFER_SIZE + buffer->head - buffer->tail) % CONFIG_BUFFER_SIZE;
}

void ConfigUSB_::flush(void)
{
  USB_Flush(CONFIG_TX);
}

size_t ConfigUSB_::write(const uint8_t *buffer, size_t size)
{
  /* only try to send bytes if the high-level MIDI connection itself
     is open (not just the pipe) - the OS should set lineState when the port
     is opened and clear lineState when the port is closed.
     bytes sent before the user opens the connection or after
     the connection is closed are lost - just like with a UART. */

  // TODO - ZE - check behavior on different OSes and test what happens if an
  // open connection isn't broken cleanly (cable is yanked out, host dies
  // or locks up, or host virtual serial port hangs)

  // first, check the TX buffer to see if it's ready for writing.
  // USB_Send() may block if there's no one listening on the other end.
  // in that case, we don't want to block waiting for someone to connect,
  // because that would freeze the whole sketch
  // instead, we'll just drop the packets and hope the caller figures it out.
  if (is_write_enabled(CONFIG_TX))
  {
    int r = USB_Send(CONFIG_TX, buffer, size);

    if (r > 0)
    {
      return r;
    } else
    {
      return 0;
    }
  }
  return 0;
}

void ConfigUSB_::send(configPacket_t cfg)
{
  uint8_t data[4];
  data[0] = cfg.cmd;
  data[1] = cfg.data1;
  data[2] = cfg.data2;
  data[3] = cfg.data3;

  write(data, 4);
}

void ConfigUSB_::accept(void)
{
  ring_bufferConfig *buffer = &cfg_rx_buffer;
  uint32_t i = (uint32_t)(buffer->head+1) % CONFIG_BUFFER_SIZE;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  while (i != buffer->tail)
  {
    int c;
    configPacket_t cfg;

    c = USB_Recv(CONFIG_RX, &cfg, sizeof(cfg) );

    //CFG packet has to be 33 bytes
    if(c < 33)
      return;

    buffer->cfg[buffer->head] = cfg;
    buffer->head = i;

    i = (i + 1) % CONFIG_BUFFER_SIZE;
  }
}

