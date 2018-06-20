#define NO_SERIAL
#define DEAD_ZONE 7500
/**
   You should have a LUFAConfig.h for this to work.
*/
#include "LUFAConfig.h"

/**
   Include LUFA.h after LUFAConfig.h
*/
#include <LUFA.h>

/**
   Finally include the LUFA device setup header
*/
#include "Controller.h"


#define NO_SERIAL
#include <XBOXUSB.h>
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
XBOXUSB Xbox(&Usb);

USB_JoystickReport_Input_t buffer;
USB_JoystickReport_Input_t defaultBuf;


void setup()
{

  memset(&defaultBuf, 0, sizeof(USB_JoystickReport_Input_t));
  defaultBuf.LX = STICK_CENTER;
  defaultBuf.LY = STICK_CENTER;
  defaultBuf.RX = STICK_CENTER;
  defaultBuf.RY = STICK_CENTER;
  defaultBuf.HAT = HAT_CENTER;
  memcpy(&buffer, &defaultBuf, sizeof(USB_JoystickReport_Input_t));



  SetupHardware(); // ask LUFA to setup the hardware

  GlobalInterruptEnable(); // enable global interrupts

  Usb.Init();

  Xbox.setLedOn(LED1);
}

void loop()
{
  Usb.Task();

  HID_Task();
  // We also need to run the main USB management task.
  USB_USBTask();
}


//nach controller verfrachten
void HID_Task(void) {
  // If the device isn't connected and properly configured, we can't do anything here.
  if (USB_DeviceState != DEVICE_STATE_Configured)
    return;
  if (! Xbox.Xbox360Connected)
    return;
  // We'll start with the OUT endpoint.
  Endpoint_SelectEndpoint(JOYSTICK_OUT_EPADDR);
  // We'll check to see if we received something on the OUT endpoint.
  if (Endpoint_IsOUTReceived())
  {
    // If we did, and the packet has data, we'll react to it.
    if (Endpoint_IsReadWriteAllowed())
    {
      // We'll create a place to store our data received from the host.
      USB_JoystickReport_Output_t JoystickOutputData;

      // We'll then take in that data, setting it up in our storage.
      while (Endpoint_Read_Stream_LE(&JoystickOutputData, sizeof(JoystickOutputData), NULL) != ENDPOINT_RWSTREAM_NoError);

      // At this point, we can react to this data.

      // However, since we're not doing anything with this data, we abandon it.
    }
    // Regardless of whether we reacted to the data, we acknowledge an OUT packet on this endpoint.
    Endpoint_ClearOUT();
  }

  // We'll then move on to the IN endpoint.
  Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);
  // We first check to see if the host is ready to accept data.
  if (Endpoint_IsINReady())
  {
    // We'll create an empty report.
    USB_JoystickReport_Input_t JoystickInputData;

    defaultBuf.LX = STICK_CENTER;
    defaultBuf.LY = STICK_CENTER;
    defaultBuf.RX = STICK_CENTER;
    defaultBuf.RY = STICK_CENTER;

    int temp = Xbox.getAnalogHat(LeftHatX);
    if (temp > DEAD_ZONE || temp < -DEAD_ZONE) {
      defaultBuf.LX = temp / 256 + 128;
    } else {
      defaultBuf.LX = STICK_CENTER;
    }
    temp = Xbox.getAnalogHat(LeftHatY);
    if (temp > DEAD_ZONE || temp < -DEAD_ZONE) {
      defaultBuf.LY = (-temp / 256) + 127;
    } else {
      defaultBuf.LY = STICK_CENTER;
    }

    temp = Xbox.getAnalogHat(RightHatX);
    if (temp > DEAD_ZONE || temp < -DEAD_ZONE) {
      defaultBuf.RX = temp / 256 + 128;
    } else {
      defaultBuf.RX = STICK_CENTER;
    }

    temp = Xbox.getAnalogHat(RightHatY);
    if (temp > DEAD_ZONE || temp < -DEAD_ZONE) {
      defaultBuf.RY = (-temp / 256) + 127;
    } else {
      defaultBuf.RY = STICK_CENTER;
    }

    if (Xbox.getButtonPress(UP)) {
      if (Xbox.getButtonPress(RIGHT)) {
        defaultBuf.HAT = 0x01;
      } else if (Xbox.getButtonPress(LEFT)) {
        defaultBuf.HAT = 0x07;
      } else {
        defaultBuf.HAT = 0x00;
      }
    } else {
      if (Xbox.getButtonPress(RIGHT)) {
        if (Xbox.getButtonPress(DOWN)) {
          defaultBuf.HAT = 0x03;
        } else {
          defaultBuf.HAT = 0x02;
        }
      } else {
        if (Xbox.getButtonPress(DOWN)) {
          if (Xbox.getButtonPress(LEFT)) {
            defaultBuf.HAT = 0x05;
          } else {
            defaultBuf.HAT = 0x04;
          }
        } else {
          if (Xbox.getButtonPress(LEFT)) {
            defaultBuf.HAT = 0x06;
          } else {
            defaultBuf.HAT = HAT_CENTER;
          }
        }
      }
    }

    defaultBuf.Button = 0x0;

    if (Xbox.getButtonPress(Y)) {
      defaultBuf.Button |= SWITCH_X;
    }
    if (Xbox.getButtonPress(B)) {
      defaultBuf.Button |= SWITCH_A;
    }
    if (Xbox.getButtonPress(A)) {
      defaultBuf.Button |= SWITCH_B;
    }
    if (Xbox.getButtonPress(X)) {
      defaultBuf.Button |= SWITCH_Y;
    }
    if (Xbox.getButtonPress(L1)) {
      defaultBuf.Button |= SWITCH_L;
    }
    if (Xbox.getButtonPress(R1)) {
      defaultBuf.Button |= SWITCH_R;
    }
    if (Xbox.getButtonPress(L2)) {
      defaultBuf.Button |= SWITCH_ZL;
    }
    if (Xbox.getButtonPress(R2)) {
      defaultBuf.Button |= SWITCH_ZR;
    }
    if (Xbox.getButtonPress(BACK)) {
      defaultBuf.Button |= SWITCH_MINUS;
    }
    if (Xbox.getButtonPress(START)) {
      defaultBuf.Button |= SWITCH_PLUS;
    }
    if (Xbox.getButtonPress(XBOX)) {
      defaultBuf.Button |= SWITCH_HOME;
    }
    if (Xbox.getButtonPress(L3)) {
      defaultBuf.Button |= SWITCH_LCLICK;
    }
    if (Xbox.getButtonPress(R3)) {
      defaultBuf.Button |= SWITCH_RCLICK;
    }

    // We'll then populate this report with what we want to send to the host.
    memcpy(&JoystickInputData, &defaultBuf, sizeof(USB_JoystickReport_Input_t));

    // Once populated, we can output this data to the host. We do this by first writing the data to the control stream.
    while (Endpoint_Write_Stream_LE(&JoystickInputData, sizeof(JoystickInputData), NULL) != ENDPOINT_RWSTREAM_NoError);

    // We then send an IN packet on this endpoint.
    Endpoint_ClearIN();
  }
}

