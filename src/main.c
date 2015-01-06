#include <stdio.h>
#include <stdint.h>

#include "stm32f4xx_conf.h"
#include "stm32f4xx.h"
#include "main.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"
#include "usb_transport.h"
#include "tn_package_name_test_types.h"

// Private variables
volatile uint32_t time_var1, time_var2;
__ALIGN_BEGIN USB_OTG_CORE_HANDLE  USB_OTG_dev __ALIGN_END;

// Private function prototypes
void Delay(volatile uint32_t nCount);
void init();

int main(void) {
	init();

	GPIO_SetBits(GPIOD, GPIO_Pin_13);

	tn_error_t error = T_ERR_OK;
	tn_package_name_structa_t *msg = tn_package_name_structa_create(&error);
	if( error != T_ERR_OK ) {
		printf("Failed to create msg %i\n", error);
		return error;
	}
	tn_protocol_t *protocol = tn_protocol_compact_create(&error);
	if( error != T_ERR_OK ) {
		printf("Failed to create protocol %i\n", error);
		return error;
	}
	tn_transport_t *transport = tn_transport_usb_create(&error);
	if( error != T_ERR_OK ) {
		printf("Failed to create transport %i\n", error);
		return error;
	}

	for(;;) {
		tn_struct_read(msg, protocol, transport, &error);
		if (error != T_ERR_OK) {
			printf("Failed to read message %i\n", error);
		} else {
			tn_struct_write(msg, protocol, transport, &error);
			if (error != T_ERR_OK) {
				printf("Failed to read message %i\n", error);
			}
		}
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		Delay(500);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		Delay(500);
	}

	return 0;
}

void init() {
	GPIO_InitTypeDef  GPIO_InitStructure;

	// ---------- SysTick timer -------- //
	if (SysTick_Config(SystemCoreClock / 1000)) {
		// Capture error
		while (1){};
	}

	// ---------- GPIO -------- //
	// GPIOD Periph clock enable
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	// Configure PD12, PD13, PD14 and PD15 in output pushpull mode
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// ------------- USB -------------- //
	USBD_Init(&USB_OTG_dev,
	            USB_OTG_FS_CORE_ID,
	            &USR_desc,
	            &USBD_CDC_cb,
	            &USR_cb);

	// ------------- TN -------------- //
	tn_init();
}

/*
 * Called from systick handler
 */
void timing_handler() {
	if (time_var1) {
		time_var1--;
	}

	time_var2++;
}

/*
 * Delay a number of systick cycles (1ms)
 */
void Delay(volatile uint32_t nCount) {
	time_var1 = nCount;
	while(time_var1){};
}

/*
 * Dummy function to avoid compiler error
 */
void _init() {

}

