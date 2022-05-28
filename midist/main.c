#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOB);
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO9);
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
}

int main(void) {
	rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);

	gpio_setup();
	gpio_toggle(GPIOC, GPIO13);

	while (1) {
		gpio_toggle(GPIOB, GPIO9);  /* LED on/off */
		gpio_toggle(GPIOC, GPIO13); /* LED on/off */
		for (int i = 0; i < 84000000; i++) { /* Wait a bit. */
			__asm__("nop");
		}
	}
	return 1;
}
