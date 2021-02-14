#include "pico/stdlib.h"
#include "hardware/vreg.h"

#include "bitstream_blinky.h"
#include "fpga_spi_config.pio.h"

void __not_in_flash_func(load_bitstream)(const uint8_t *bits, size_t len) {
	// We're going to use a PIO SM for loading the bitstream, because it keeps
	// consistent time, and just does what we tell it to (also lets us assign
	// pins arbitrarily, which is important because we've bent round the IO
	// assignment here to reuse these pins for the graphics bus later)


#if 1
	uint rst_n = PICOSTATION_FPGA_CRESET_PIN;
	uint cs_n  = PICOSTATION_FPGA_SPI_SS_PIN;
	uint si    = PICOSTATION_FPGA_SPI_SI_PIN;
	uint sck   = PICOSTATION_FPGA_SPI_SCK_PIN;
	uint cdone = PICOSTATION_FPGA_CDONE_PIN;
#else
	uint rst_n = 2;
	uint cs_n  = 3;
	uint si    = 4;
	uint sck   = 5;
	uint cdone = 6;
#endif

	// FPGA enters slave configuration mode when it is brought out of reset with
	// SPI_SS_N asserted

	gpio_pull_up(cdone);
	gpio_init(cdone);

	gpio_init(rst_n);
	gpio_put(rst_n, 0);
	gpio_set_dir(rst_n, GPIO_OUT);
	busy_wait_us_32(10); // minimum 200 ns

	// SCK frequency of clk_sys / (2 * 20.f) -> 6.3 MHz. Max is 25 MHz, min is 1 MHz
	fpga_spi_config_init(pio0, 0, si, sck, 20.f);

	gpio_init(cs_n);
	gpio_put(cs_n, 0);
	gpio_set_dir(cs_n, GPIO_OUT);
	busy_wait_us_32(10);

	gpio_put(rst_n, 1);
	busy_wait_us_32(10);
	// Minimum 1200us after releasing reset (wait for FPGA to clear its CRAM)
	busy_wait_us_32(2000);

	// Deassert chip select, 8 dummy clocks, reassert.
	gpio_put(cs_n, 1);
	fpga_spi_config_put(pio0, 0, 0);
	fpga_spi_config_flush_fifo(pio0, 0);
	gpio_put(cs_n, 0);

	// Start shovelling
	for (size_t i = 0; i < len; ++i)
		fpga_spi_config_put(pio0, 0, bits[i]);
	// At least 49 dummy clocks at the end 
	for (int i = 0; i < 7; ++i)
		fpga_spi_config_put(pio0, 0, 0);
	fpga_spi_config_flush_fifo(pio0, 0);
}

void sw_blinky(void);

int main() {
	// Increase core voltage to 1.2V (core regulator is shared with FPGA)
	vreg_set_voltage(VREG_VOLTAGE_1_20);
	sleep_ms(10);
	// Set system clock to 10x pixel clock (252 MHz @ VGA60)
	set_sys_clock_khz(252 * 1000, true);

	stdio_init_all();

	load_bitstream(picostation_bin, picostation_bin_len);

	sw_blinky();
}

void sw_blinky() {
	const uint led = PICO_DEFAULT_LED_PIN;
	const uint clk = PICOSTATION_GFX_CLK_PIN;

    gpio_init(led);
    gpio_set_dir(led, GPIO_OUT);
    gpio_init(clk);
    gpio_set_dir(clk, GPIO_OUT);

    uint ctr = 0;
    while (true) {
    	bool blink_blonk = ++ctr > 1000 * 1000 * 10;
    	if (blink_blonk)
    		ctr = 0;
        gpio_xor_mask((1u << clk) | ((blink_blonk ? 1u : 0u) << led));
        asm volatile ("nop \n nop \n nop");
    }
}
