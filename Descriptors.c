/*
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2013  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

const USB_Descriptor_HIDReport_Datatype_t PROGMEM JoystickReport[] = {
    HID_RI_USAGE_PAGE(8,1),                         // Generic desktop controls
    HID_RI_USAGE(8,5),                              // Joystick
    HID_RI_COLLECTION(8,1),                         // Application

    // Buttons (2 bytes)
    HID_RI_LOGICAL_MINIMUM(8,0),                    // button off state
    HID_RI_LOGICAL_MAXIMUM(8,1),                    // button on state
    HID_RI_PHYSICAL_MINIMUM(8,0),                   // button off state
    HID_RI_PHYSICAL_MAXIMUM(8,1),                   // button on state
    HID_RI_REPORT_SIZE(8,1),                        // 1 bit per report field
    HID_RI_REPORT_COUNT(8,14),                      // 14 report fields (14 buttons)
    HID_RI_USAGE_PAGE(8,9),                         // Buttons (section 12)
    HID_RI_USAGE_MINIMUM(8,1),
    HID_RI_USAGE_MAXIMUM(8,14),
    HID_RI_INPUT(8,2),                              // Variable input
    HID_RI_REPORT_COUNT(8,2),                       // 2 report fields (empty 2 bits)
    HID_RI_INPUT(8,1),                              // Array input

    // HAT switch
    HID_RI_USAGE_PAGE(8,1),                         // Generic desktop controls
    HID_RI_LOGICAL_MAXIMUM(8,7),                    // 8 valid HAT states, sending 0x08 = nothing pressed
    HID_RI_PHYSICAL_MAXIMUM(16,315),                // HAT "rotation"
    HID_RI_REPORT_SIZE(8,4),                        // 4 bits per report field
    HID_RI_REPORT_COUNT(8,1),                       // 1 report field (a nibble containing entire HAT state)
    HID_RI_UNIT(8,20),                              // unit degrees
    HID_RI_USAGE(8,57),                             // Hat switch (section 4.3)
    HID_RI_INPUT(8,66),                             // Variable input, null state
    HID_RI_UNIT(8,0),                               // No units
    HID_RI_REPORT_COUNT(8,1),                       // 1 report field (empty upper nibble)
    HID_RI_INPUT(8,1),                              // Array input

    // Joystick (4 bytes)
    HID_RI_LOGICAL_MAXIMUM(16,255),                 // 0-255 for analog sticks
    HID_RI_PHYSICAL_MAXIMUM(16,255),
    HID_RI_USAGE(8,48),                             // X (left X)
    HID_RI_USAGE(8,49),                             // Y (left Y)
    HID_RI_USAGE(8,50),                             // Z (right X)
    HID_RI_USAGE(8,53),                             // Rz (right Y)
    HID_RI_REPORT_SIZE(8,8),                        // 1 byte per report field
    HID_RI_REPORT_COUNT(8,4),                       // 4 report fields (left X, left Y, right X, right Y)
    HID_RI_INPUT(8,2),                              // Variable input

    // I think this is the vendor spec byte.
    // On the Pokken pad this is usage page 0xFF00 which is vendor defined.
    // Usage is 0x20 on the Pokken pad, but since the usage page is vendor defined this is kind of meaningless.
    // Seems fine to just leave this byte set to 0.
    HID_RI_REPORT_SIZE(8,8),                        // 1 byte per report field
    HID_RI_REPORT_COUNT(8,1),                       // 1 report field
    HID_RI_INPUT(8,1),                              // Array input

    // On the Pokken pad apparently we also receive a mirror image of the sent inputs,
    // but according to the Hori pad USB descriptors this isn't necessary.
    // The usage page is still vendor defined, so the usage 0x2621 is meaningless to us.
    // On the Pokken pad this is an 8 byte report of dynamic output.

    /* This is where the Hori pad and modified Pokken pad diverge. Commenting out for future reference.
    // HAT Switch (1 nibble)
    HID_RI_USAGE_PAGE(8,1),
    HID_RI_LOGICAL_MAXIMUM(8,7),
    HID_RI_PHYSICAL_MAXIMUM(16,315),
    HID_RI_REPORT_SIZE(8,4),
    HID_RI_REPORT_COUNT(8,1),
    HID_RI_UNIT(8,20),
    HID_RI_USAGE(8,57),
    HID_RI_INPUT(8,66),
    // There's an additional nibble here that's utilized as part of the Switch Pro Controller.
    // I believe this -might- be separate U/D/L/R bits on the Switch Pro Controller, as they're utilized as four button descriptors on the Switch Pro Controller.
    HID_RI_UNIT(8,0),
    HID_RI_REPORT_COUNT(8,1),
    HID_RI_INPUT(8,1),
    // Joystick (4 bytes)
    HID_RI_LOGICAL_MAXIMUM(16,255),
    HID_RI_PHYSICAL_MAXIMUM(16,255),
    HID_RI_USAGE(8,48),
    HID_RI_USAGE(8,49),
    HID_RI_USAGE(8,50),
    HID_RI_USAGE(8,53),
    HID_RI_REPORT_SIZE(8,8),
    HID_RI_REPORT_COUNT(8,4),
    HID_RI_INPUT(8,2),
    // ??? Vendor Specific (1 byte)
    // This byte requires additional investigation.
    HID_RI_USAGE_PAGE(16,65280),
    HID_RI_USAGE(8,32),
    HID_RI_REPORT_COUNT(8,1),
    HID_RI_INPUT(8,2),
    // Output (8 bytes)
    // Original observation of this suggests it to be a mirror of the inputs that we sent.
    // The Switch requires us to have these descriptors available.
    HID_RI_USAGE(16,9761),
    HID_RI_REPORT_COUNT(8,8),
    HID_RI_OUTPUT(8,2),
    */

    HID_RI_END_COLLECTION(0),
};

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
    .Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

    .USBSpecification       = VERSION_BCD(2,0,0),
    .Class                  = USB_CSCP_NoDeviceClass,
    .SubClass               = USB_CSCP_NoDeviceSubclass,
    .Protocol               = USB_CSCP_NoDeviceProtocol,

    .Endpoint0Size          = FIXED_CONTROL_ENDPOINT_SIZE,

    .VendorID               = 0x0F0D,
    .ProductID              = 0x00C1,
    .ReleaseNumber          = VERSION_BCD(5,7,2),

    .ManufacturerStrIndex   = STRING_ID_Manufacturer,
    .ProductStrIndex        = STRING_ID_Product,
    .SerialNumStrIndex      = NO_DESCRIPTOR,

    .NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

            .TotalConfigurationSize = sizeof(USB_Descriptor_Configuration_t),
            .TotalInterfaces        = 1,

            .ConfigurationNumber    = 1,
            .ConfigurationStrIndex  = NO_DESCRIPTOR,

            .ConfigAttributes       = 0x80,

            .MaxPowerConsumption    = USB_CONFIG_POWER_MA(250)
        },

    .HID_Interface =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

            .InterfaceNumber        = INTERFACE_ID_Joystick,
            .AlternateSetting       = 0x00,

            .TotalEndpoints         = 2,

            .Class                  = HID_CSCP_HIDClass,
            .SubClass               = HID_CSCP_NonBootSubclass,
            .Protocol               = HID_CSCP_NonBootProtocol,

            .InterfaceStrIndex      = NO_DESCRIPTOR
        },

    /*
        Reference:
        hid_descriptor = b'\x09\x21\x11\x01\x00\x01\x22\x50\x00'
    */
    .HID_JoystickHID =
        {
            .Header                 = {.Size = sizeof(USB_HID_Descriptor_HID_t), .Type = HID_DTYPE_HID},

            .HIDSpec                = VERSION_BCD(1,1,1),
            .CountryCode            = 0x00,
            .TotalReportDescriptors = 1,
            .HIDReportType          = HID_DTYPE_Report,
            .HIDReportLength        = sizeof(JoystickReport)
        },

    .HID_ReportINEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = JOYSTICK_IN_EPADDR,
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = JOYSTICK_EPSIZE,
            .PollingIntervalMS      = 0x05
        },

    .HID_ReportOUTEndpoint =
        {
            .Header                 = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},

            .EndpointAddress        = JOYSTICK_OUT_EPADDR,
            .Attributes             = (EP_TYPE_INTERRUPT | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
            .EndpointSize           = JOYSTICK_EPSIZE,
            .PollingIntervalMS      = 0x05
        },
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header                 = {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},

	.UnicodeString          = {LANGUAGE_ID_ENG}
};

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header                 = {.Size = USB_STRING_LEN(11), .Type = DTYPE_String},

	.UnicodeString          = L"HORI CO.,LTD."
};

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString =
{
	.Header                 = {.Size = USB_STRING_LEN(13), .Type = DTYPE_String},

	.UnicodeString          = L"HORIPAD S"
};

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
   const uint8_t  DescriptorType   = (wValue >> 8);
    const uint8_t  DescriptorNumber = (wValue & 0xFF);

    const void* Address = NULL;
    uint16_t    Size    = NO_DESCRIPTOR;

    switch (DescriptorType)
    {
        case DTYPE_Device:
            Address = &DeviceDescriptor;
            Size    = sizeof(USB_Descriptor_Device_t);
            break;
        case DTYPE_Configuration:
            Address = &ConfigurationDescriptor;
            Size    = sizeof(USB_Descriptor_Configuration_t);
            break;
        case DTYPE_String:
            switch (DescriptorNumber)
            {
                case STRING_ID_Language:
                    Address = &LanguageString;
                    Size    = pgm_read_byte(&LanguageString.Header.Size);
                    break;
                case STRING_ID_Manufacturer:
                    Address = &ManufacturerString;
                    Size    = pgm_read_byte(&ManufacturerString.Header.Size);
                    break;
                case STRING_ID_Product:
                    Address = &ProductString;
                    Size    = pgm_read_byte(&ProductString.Header.Size);
                    break;
            }

            break;
        case DTYPE_HID:
            Address = &ConfigurationDescriptor.HID_JoystickHID;
            Size    = sizeof(USB_HID_Descriptor_HID_t);
            break;
        case DTYPE_Report:
            Address = &JoystickReport;
            Size    = sizeof(JoystickReport);
            break;
    }

    *DescriptorAddress = Address;
    return Size;
}



