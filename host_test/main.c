#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>

#define VID 0x2341
#define PID 0x8037

void
show_usb_error ( int e )
{
  if ( e == LIBUSB_ERROR_IO )
    printf ("USB error: IO\n" );
  else if ( e == LIBUSB_ERROR_BUSY )
    printf ("USB error: BUSY\n" );
  else if ( e == LIBUSB_ERROR_TIMEOUT )
    printf ("USB error: TIMEOUT\n" );
  else
    printf ("USB error: %d\n", e );
}

int main(void)
{
  libusb_device_handle *uh;

  libusb_init(NULL);
  libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_DEBUG);
  
  uh = libusb_open_device_with_vid_pid(NULL, VID, PID);
  if(!uh)
  {
    printf("Device %04x:%04x not found\n", VID, PID);
    libusb_exit(NULL);
    return -1;
  }

  // Claim Interface
  if (libusb_kernel_driver_active(uh, 2) == 1 )
  {
    printf("Found kernel driver active on device %04x:%04x\n", VID, PID );
    
    if (libusb_detach_kernel_driver (uh, 2) != 0 )
    {
      printf ( "Unable to detach kernel driver\n" );
    }
  }

  if (libusb_claim_interface(uh, 2 ) < 0 )
  {
    libusb_close (uh);
    printf("Unable to claim interface\n");
    libusb_exit(NULL);
    return -1;
  }

  unsigned char buff[4];
  int cnt = 0;
  int err = libusb_bulk_transfer(uh, 0x85, buff, 4, &cnt, 20);
  printf ("Interrupt read to %02x returns %d, received %d bytes\n", 0x85, err, cnt);

  if(err < 0)
    show_usb_error(err);

  
  
  
  libusb_exit(NULL);

  return 0;
}
