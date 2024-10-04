#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include "delay.h"
#include "usb_serial.h"

/* preprocessor macros: */
#define SYS_CLOCK_MHZ (96U) // possible options (84U), (96U), (100U)  NOTE: 100MHz does not support USB

/* function prototypes: */
static void clock_setup(void);
static void gpio_setup(void);


int main(void)
{
	clock_setup();
	gpio_setup();
	delay_init(SYS_CLOCK_MHZ);

	/* enable LED (GPIOC, GPIO13) to show the entry of main: */
	gpio_clear(GPIOC, GPIO13);

	/* initialize USB serial: */
	USB_Serial_init();

	/* disable LED to show that USB serial initialized successfully: */
	gpio_set(GPIOC, GPIO13);

	/* test functions of USB serial write: */
	USB_Serial_write("Hello world!\n");

	char test[] = {"\nThis is a test to check if splitting into several tx-packages is working properly!\n"};
	USB_Serial_write(test);

	USB_Serial_write("\nTest of USB_Serial_write_u32:\n");
	USB_Serial_write_u32((uint32_t)123456);
	USB_Serial_write_u32(123456U);
	USB_Serial_write_u32(10U);
	USB_Serial_write_u32(1);
	USB_Serial_write_u32(-1);
	USB_Serial_write_u32((uint8_t)10);
	uint8_t test2 = 7;
	USB_Serial_write_u32(test2);
	USB_Serial_write_u32(7.77);

	USB_Serial_write("\nTest of USB_Serial_write_i32:\n");
	USB_Serial_write_i32((int32_t)123456);
	USB_Serial_write_i32((uint32_t)123456);
	USB_Serial_write_i32((int32_t)-123456);
	USB_Serial_write_i32(-123456);
	USB_Serial_write_i32(10U);
	USB_Serial_write_i32(1);
	USB_Serial_write_i32(-1);
	USB_Serial_write_i32((int8_t)-10);
	int8_t test3 = -7;
	USB_Serial_write_i32(test3);
	USB_Serial_write_i32(7.77);

	USB_Serial_write("\nTest of USB_Serial_write_float:\n");
	USB_Serial_write_float((float)1.1111111111);
	USB_Serial_write_float((float)-1.1111111111);
	USB_Serial_write_float(2.1111111111);
	USB_Serial_write_float(-2.1111111111);
	USB_Serial_write_float((int32_t)-123456);
	USB_Serial_write_float((uint32_t)123456);
	float test4 = -7.1111111111;
	USB_Serial_write_float(test4);
	USB_Serial_write_float((float)1.123456789);
	USB_Serial_write_float((float)-1.987654321);

	/* test functions of USB serial read: */
	USB_Serial_write("\nEnter your name: ");
	char *input1;
	input1 = USB_Serial_read();
	USB_Serial_write("\nYou have entered: ");
	USB_Serial_write(input1);

	USB_Serial_write("\nEnter a unsigned number: ");
	uint32_t input_number_1 = USB_Serial_read_u32();
	USB_Serial_write("\nYou have entered: ");
	USB_Serial_write_u32(input_number_1);

	USB_Serial_write("\nEnter a signed number: ");
	int32_t input_number_2 = USB_Serial_read_i32();
	USB_Serial_write("\nYou have entered: ");
	USB_Serial_write_i32(input_number_2);

	USB_Serial_write("\nEnter a float number: ");
	float input_number_3 = USB_Serial_read_float();
	USB_Serial_write("\nYou have entered: ");
	USB_Serial_write_float(input_number_3);

	/* blink LED to indicate that everything finished: */
	USB_Serial_write("\nTest finished -> start blinking...");
	while (1)
	{
		gpio_toggle(GPIOC, GPIO13);
		delay_ms(300);
	}

	return 0;
}


static void clock_setup(void)
{
	#if (SYS_CLOCK_MHZ == (100U))
		const struct rcc_clock_scale rcc_hse_25mhz_3v3_100MHz = {
			.pllm = 12,
			.plln = 96,
			.pllp = 2,
			.pllq = 4,
			.pllr = 0,
			.pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
			.hpre = RCC_CFGR_HPRE_DIV_NONE,
			.ppre1 = RCC_CFGR_PPRE_DIV_2,
			.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
			.voltage_scale = PWR_SCALE1,
			.flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_3WS,
			.ahb_frequency  = 100000000,
			.apb1_frequency = 50000000,
			.apb2_frequency = 100000000
		};
		/* set STM32 to 100 MHz: */
		rcc_clock_setup_pll(&rcc_hse_25mhz_3v3_100MHz);

	#elif (SYS_CLOCK_MHZ == (96U))
		const struct rcc_clock_scale rcc_hse_25mhz_3v3_96MHz = {
			.pllm = 25,
			.plln = 192,
			.pllp = 2,
			.pllq = 4,
			.pllr = 0,
			.pll_source = RCC_CFGR_PLLSRC_HSE_CLK,
			.hpre = RCC_CFGR_HPRE_DIV_NONE,
			.ppre1 = RCC_CFGR_PPRE_DIV_2,
			.ppre2 = RCC_CFGR_PPRE_DIV_NONE,
			.voltage_scale = PWR_SCALE1,
			.flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_3WS,
			.ahb_frequency  = 96000000,
			.apb1_frequency = 48000000,
			.apb2_frequency = 96000000
		};
		/* set STM32 to 100 MHz: */
		rcc_clock_setup_pll(&rcc_hse_25mhz_3v3_96MHz);

	#elif (SYS_CLOCK_MHZ == (84U))
		/* set STM32 to 84 MHz: */
		rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

	#else
		#error "wrong SYS_CLOCK_MHZ selected"

	#endif

	/* enable GPIO clock: */
	rcc_periph_clock_enable(RCC_GPIOC); // PORT C for LED
	rcc_periph_clock_enable(RCC_GPIOA); // PORT A for USB

	/* set clock source for systick counter: */
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);

	/* enable clock for USB: */
	rcc_periph_clock_enable(RCC_OTGFS);
}


static void gpio_setup(void)
{
	/* configure LED pin: */
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);

	/* configure USB pins */
	gpio_mode_setup(GPIOA,  GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11|GPIO12);
    gpio_set_af(GPIOA, GPIO_AF10, GPIO11|GPIO12);
}
