#ifndef __USB_TRANSPORT_H_
#define __USB_TRANSPORT_H_

#include <thrift-nano/thrift_nano.h>

typedef struct tn_transport_led_t
{
	tn_transport_t parent;
	tn_transport_t *next;
	uint16_t pin;
} tn_transport_led_t;
tn_transport_t* tn_transport_led_init(tn_transport_led_t *self, tn_transport_t *next, uint16_t pin, tn_error_t *error);
tn_transport_t* tn_transport_led_create(tn_transport_t *next, uint16_t pin, tn_error_t *error);

typedef struct tn_transport_usb_t
{
	tn_transport_t parent;
} tn_transport_usb_t;
tn_transport_t* tn_transport_usb_init(tn_transport_usb_t *self, tn_error_t *error);
tn_transport_t* tn_transport_usb_create(tn_error_t *error);

#endif //__USB_TRANSPORT_H_
