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
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include "LUFAConfig.h"

		#include <avr/pgmspace.h>

		#include <LUFA/Drivers/USB/USB.h>

	/* Macros: */
    #define JOYSTICK_IN_EPADDR  (ENDPOINT_DIR_IN  | 1)
    #define JOYSTICK_OUT_EPADDR (ENDPOINT_DIR_OUT | 2)
    // HID Endpoint Size
    // The Switch -needs- this to be 64.
    // The Wii U is flexible, allowing us to use the default of 8 (which did not match the original Hori descriptors).
    #define JOYSTICK_EPSIZE           64
    // Descriptor Header Type - HID Class HID Descriptor
    #define DTYPE_HID                 0x21
    // Descriptor Header Type - HID Class HID Report Descriptor
    #define DTYPE_Report              0x22
    // Joystick endpoint polling interval (in ms). It looks like any value set here renders in a timing multiple of 8 ms.
    #define POLLING_MS 8

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t    Config;

      // Joystick HID Interface
      USB_Descriptor_Interface_t            HID_Interface;
      USB_HID_Descriptor_HID_t              HID_JoystickHID;
      USB_Descriptor_Endpoint_t             HID_ReportOUTEndpoint;
      USB_Descriptor_Endpoint_t             HID_ReportINEndpoint;
		} USB_Descriptor_Configuration_t;


    // Device Interface Descriptor IDs
    enum InterfaceDescriptors_t
    {
      INTERFACE_ID_Joystick = 0, /**< Joystick interface descriptor ID */
    };
		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 *  have a unique ID index associated with it, which can be used to refer to the string from
		 *  other descriptors.
		 */
		enum StringDescriptors_t
		{
		    STRING_ID_Language      = 0, /**< Supported Languages string descriptor ID (must be zero) */
		    STRING_ID_Manufacturer  = 1, /**< Manufacturer string ID */
		    STRING_ID_Product       = 2, /**< Product string ID */
		};

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif


