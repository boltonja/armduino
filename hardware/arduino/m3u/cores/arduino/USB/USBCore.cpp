// Copyright (c) 2010, Peter Barrett
/*
** Permission to use, copy, modify, and/or distribute this software for
** any purpose with or without fee is hereby granted, provided that the
** above copyright notice and this permission notice appear in all copies.
**
** THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
** WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
** WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR
** BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
** OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
** WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
** ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
** SOFTWARE.
*/

#include "Arduino.h"
#include "USBAPI.h"
#include "Reset.h"
#include <stdio.h>
#include "USBCore.h"
//#define TRACE_CORE(x)	x
#define TRACE_CORE(x)

static const uint32_t EndPoints[] =
{
	3,

#ifdef CDC_ENABLED
	4,           // CDC_ENDPOINT_ACM
	5,               // CDC_ENDPOINT_OUT
	6,                // CDC_ENDPOINT_IN
#endif

#ifdef HID_ENABLED
	7        // HID_ENDPOINT_INT
#endif
};

/** Pulse generation counters to keep track of the number of milliseconds remaining for each pulse type */
#define TX_RX_LED_PULSE_MS 100
volatile uint8_t TxLEDPulse; /**< Milliseconds remaining for data Tx LED pulse */
volatile uint8_t RxLEDPulse; /**< Milliseconds remaining for data Rx LED pulse */
static char isRemoteWakeUpEnabled = 0;
static char isEndpointHalt = 0;
//==================================================================
//==================================================================

extern const uint16_t STRING_LANGUAGE[];
extern const uint16_t STRING_IPRODUCT[];
extern const uint16_t STRING_IMANUFACTURER[];
extern const DeviceDescriptor USB_DeviceDescriptor;
extern const DeviceDescriptor USB_DeviceDescriptorA;

const uint16_t STRING_LANGUAGE[2] = {
	(3<<8) | (2+2),
	0x0409	// English
};

const uint16_t STRING_IPRODUCT[17] = {
	(3<<8) | (2+2*16),
#if USB_PID == USB_PID_LEONARDO
	'A','r','d','u','i','n','o',' ','L','e','o','n','a','r','d','o'
#elif USB_PID == USB_PID_MICRO
	'A','r','d','u','i','n','o',' ','M','i','c','r','o',' ',' ',' '
#elif USB_PID == USB_PID_DUE
	'A','r','d','u','i','n','o',' ','D','u','e',' ',' ',' ',' ',' '
#else
	'A','r','d','u','i','n','o',' ','D','u','e',' ',' ',' ',' ',' '
#endif
};

const uint16_t STRING_IMANUFACTURER[12] = {
	(3<<8) | (2+2*11),
	'A','r','d','u','i','n','o',' ','L','L','C'
};

#ifdef CDC_ENABLED
#define DEVICE_CLASS 0x02
#else
#define DEVICE_CLASS 0x00
#endif

// fixme [silabs]: usb manufacturer and product ids
#define IMANUFACTURER 01
#define IPRODUCT 02
//	DEVICE DESCRIPTOR
const DeviceDescriptor USB_DeviceDescriptor =
	D_DEVICE(0x00,0x00,0x00,64,USB_VID,USB_PID,0x100,IMANUFACTURER,IPRODUCT,0,1);

const DeviceDescriptor USB_DeviceDescriptorA =
	D_DEVICE(DEVICE_CLASS,0x00,0x00,64,USB_VID,USB_PID,0x100,IMANUFACTURER,IPRODUCT,0,1);

const DeviceDescriptor USB_DeviceQualifier =
	D_QUALIFIER(0x00,0x00,0x00,64,1);

//! 7.1.20 Test Mode Support
static const unsigned char test_packet_buffer[] = {
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,                // JKJKJKJK * 9
    0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,                     // JJKKJJKK * 8
    0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,0xEE,                     // JJJJKKKK * 8
    0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // JJJJJJJKKKKKKK * 8
    0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,                          // JJJJJJJK * 8
    0xFC,0x7E,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0x7E                 // {JKKKKKKK * 10}, JK
};

//==================================================================
//==================================================================

volatile uint32_t _usbConfiguration = 0;
volatile uint32_t _usbInitialized = 0;
uint32_t _usbSetInterface = 0;
uint32_t _cdcComposite = 0;

//==================================================================
//==================================================================

#define USB_RECV_TIMEOUT
class LockEP
{
	uint8_t flags;
public:
	LockEP(uint32_t ep)
	{
	}
	~LockEP()
	{

	}
};

//	Number of bytes, assumes a rx endpoint
uint32_t USBD_Available(uint32_t ep)
{
	LockEP lock(ep);
	return 1;
}

//	Non Blocking receive
//	Return number of bytes read
uint32_t USBD_Recv(uint32_t ep, void* d, uint32_t len)
{
    return 0;
}

//	Recv 1 byte if ready
uint32_t USBD_Recv(uint32_t ep)
{
    return 0;
}

//	Space in send EP
//uint32_t USBD_SendSpace(uint32_t ep)
//{
	//LockEP lock(ep);
////	if (!UDD_ReadWriteAllowed(ep & 0xF))
    ////{
        ////printf("pb "); // UOTGHS->UOTGHS_DEVEPTISR[%d]=0x%X\n\r", ep, UOTGHS->UOTGHS_DEVEPTISR[ep]);
		////return 0;
    ////}

    //if(ep==0) return 64 - UDD_FifoByteCount(ep & 0xF);  // EP0_SIZE  jcb
    //else return 512 - UDD_FifoByteCount(ep & 0xF);  // EPX_SIZE  jcb
//}

//	Blocking Send of data to an endpoint
uint32_t USBD_Send(uint32_t ep, const void* d, uint32_t len)
{
    return 0;
}

int _cmark;
int _cend;

void USBD_InitControl(int end)
{
	_cmark = 0;
	_cend = end;
}

//	Clipped by _cmark/_cend
int USBD_SendControl(uint8_t flags, const void* d, uint32_t len)
{
    return 0;
}

//	Does not timeout or cross fifo boundaries
//	Will only work for transfers <= 64 bytes
//	TODO
int USBD_RecvControl(void* d, uint32_t len)
{
    return 0;
}

//	Handle CLASS_INTERFACE requests
bool USBD_ClassInterfaceRequest(Setup& setup)
{

	return false;
}

int USBD_SendInterfaces(void)
{
    return 0;
}

int USBD_SendOtherInterfaces(void)
{
    return 0;
}

//	Construct a dynamic configuration descriptor
//	This really needs dynamic endpoint allocation etc
//	TODO
static bool USBD_SendConfiguration(int maxlen)
{

	return true;
}

static bool USBD_SendOtherConfiguration(int maxlen)
{

	return true;
}

static bool USBD_SendDescriptor(Setup& setup)
{

	return true;
}


static void USB_SendZlp( void )
{

}


static void Test_Mode_Support( uint8_t wIndex )
{

}


//unsigned int iii=0;
//	Endpoint 0 interrupt
static void USB_ISR(void)
{

}

void USBD_Flush(uint32_t ep)
{

}

//	VBUS or counting frames
//	Any frame counting?
uint32_t USBD_Connected(void)
{
	return 0;
}


//=======================================================================
//=======================================================================

USBDevice_ USBDevice;

USBDevice_::USBDevice_()
{

}

bool USBDevice_::attach(void)
{
	return true;
}

bool USBDevice_::detach(void)
{
    return false;
}

//	Check for interrupts
//	TODO: VBUS detection
bool USBDevice_::configured()
{
	return _usbConfiguration;
}

void USBDevice_::poll()
{
}
