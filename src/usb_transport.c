#include "usb_transport.h"
#include "usbd_cdc_vcp.h"

const static int TN_FT_MAX_CHUNK_SIZE = 256;

static void
tn_transport_led_destroy(tn_object_t *t)
{
	tn_object_destroy(((tn_transport_led_t *)t)->next);
	tn_free(t);
}
static size_t
tn_transport_led_read(tn_transport_t *self, void *buf, size_t len, tn_error_t *error)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tn_transport_t *next = ((tn_transport_led_t *)self)->next;
	size_t ret = next->tn_read(next, buf, len, error);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	return ret;
}
static size_t
tn_transport_led_write(tn_transport_t *self, void *buf, size_t len, tn_error_t *error)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tn_transport_t *next = ((tn_transport_led_t *)self)->next;
	size_t ret = next->tn_write(next, buf, len, error);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	return ret;
}
static size_t
tn_transport_led_skip(tn_transport_t *self, size_t len, tn_error_t *error)
{
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	tn_transport_t *next = ((tn_transport_led_t *)self)->next;
	size_t ret = next->tn_skip(next, len, error);
	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	return ret;
}
tn_transport_t *
tn_transport_led_init(tn_transport_led_t *s, tn_transport_t *next, uint16_t pin, tn_error_t *error)
{
	tn_transport_t *self = (tn_transport_t*) s;
	tn_transport_init(self, error);
	self->parent.tn_destroy = &tn_transport_led_destroy;
	self->tn_read = &tn_transport_led_read;
	self->tn_write = &tn_transport_led_write;
	self->tn_skip = &tn_transport_led_skip;
	s->next = next;
	s->pin = pin;
	return self;
}
tn_transport_t*
tn_transport_led_create(tn_transport_t *next, uint16_t pin, tn_error_t *error)
{
	tn_transport_led_t *t = tn_alloc(sizeof(tn_transport_led_t), error);
	if( *error != 0 ) return NULL;
	return tn_transport_led_init(t, next, pin, error);
}

static void
tn_transport_usb_destroy(tn_object_t *t)
{
	tn_free(t);
}
static size_t
tn_transport_usb_read(tn_transport_t *self, void *buf, size_t len, tn_error_t *error)
{
	uint8_t  *b = (uint8_t *) buf;
	size_t cd = len;
	do {
		while( VCP_get_char(b + len - cd) == 0 );
	} while (--cd);
	if( cd != 0 ) *error = T_ERR_BUFFER_UNDERFLOW;
	return len - cd;
}
static size_t
tn_transport_usb_write(tn_transport_t *self, void *buf, size_t len, tn_error_t *error)
{
	uint8_t *b = (uint8_t *) buf;
	VCP_send_buffer(b, len);
	return len;
}
static size_t
tn_transport_usb_skip(tn_transport_t *self, size_t len, tn_error_t *error)
{
	// fd might not support seek...try to read chunks
	const char cbuf[TN_FT_MAX_CHUNK_SIZE];
	void *buf = (void*) &cbuf;
	size_t total = 0;
	while( (total += tn_transport_usb_read(self, buf, MIN(total-len, TN_FT_MAX_CHUNK_SIZE), error)) < len )
	{
		if( *error != 0 )
		{
			break;
		}
	}

	return total;
}
tn_transport_t *
tn_transport_usb_init(tn_transport_usb_t *s, tn_error_t *error)
{
	tn_transport_t *self = (tn_transport_t*) s;
	tn_transport_init(self, error);
	self->parent.tn_destroy = &tn_transport_usb_destroy;
	self->tn_read = &tn_transport_usb_read;
	self->tn_write = &tn_transport_usb_write;
	self->tn_skip = &tn_transport_usb_skip;
	return self;
}
tn_transport_t*
tn_transport_usb_create(tn_error_t *error)
{
	tn_transport_usb_t *t = tn_alloc(sizeof(tn_transport_usb_t), error);
	if( *error != 0 ) return NULL;
	return tn_transport_usb_init(t, error);
}
