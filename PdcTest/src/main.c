/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#define USART_SERIAL_BAUDRATE        115200
#define USART_RXD0 PIO_PA10A_RXD0
#define USART_TXD0 PIO_PA11A_TXD0
#define USART_PERIPHERAL PIOA

int main (void)
{
	sysclk_init();

	board_init();
						
	USART_PERIPHERAL->PIO_IDR = USART_RXD0;		// Interrupt disable register
	USART_PERIPHERAL->PIO_IDR = USART_TXD0;
	USART_PERIPHERAL->PIO_PDR = USART_RXD0;		// Disable input/output which enables peripheral mode
	USART_PERIPHERAL->PIO_PDR = USART_TXD0;
	USART_PERIPHERAL->PIO_ABSR &= ~USART_RXD0;	// Enable Peripheral A (USART)
	USART_PERIPHERAL->PIO_ABSR &= ~USART_TXD0;

	const sam_usart_opt_t usart_console_settings = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.char_length = US_MR_CHRL_8_BIT,
		.parity_type = US_MR_PAR_NO,
		.stop_bits = US_MR_NBSTOP_1_BIT,
		.channel_mode = US_MR_CHMODE_NORMAL,
		.irda_filter = 0
	};

	pmc_enable_periph_clk(ID_USART0);

	usart_init_rs232(USART0, &usart_console_settings, sysclk_get_cpu_hz());
	usart_enable_rx(USART0);
	usart_enable_tx(USART0);
// 	usart_putchar(USART0, 'a');
// 	usart_write_line(USART0, "Hello world");

	uint8_t send[4] = {'a', 'b', 'c', 'd'};
	
	pdc_packet_t PdcPacket = {
		.ul_addr = &send,
		.ul_size = 4
	};

	Pdc *PdcInterface = usart_get_pdc_base(USART0);

	pdc_tx_init(PdcInterface, &PdcPacket, NULL);
	pdc_enable_transfer(PdcInterface, PERIPH_PTCR_TXTEN);




	while(1)
	{
		//usart_putchar(USART0, 'a');
	}
	/* Insert application code here, after the board has been initialized. */
}
