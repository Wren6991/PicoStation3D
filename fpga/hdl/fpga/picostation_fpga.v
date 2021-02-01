`default_nettype none

module picostation_fpga (
	// Graphics parallel bus from host (note gfx_clk is also our primary clock input)
	input  wire       gfx_clk,
	input  wire       gfx_hok,
	output wire       gfx_dok,
	output wire       gfx_irq,
	inout  wire [7:0] gfx_dq,

	output wire       led,

	// HyperRAM directly connected to FPGA
	output wire       hram_clk,
	output wire       hram_cs_n,
	output wire       hram_rst_n,
	inout  wire       hram_rwds,
	inout  wire [7:0] hram_dq,

	// DVI-D connected directly to HDMI socket. Lane order {CK, D2, D1, D0}
	output wire [3:0] dvi_p,
	output wire [3:0] dvi_n
);

blinky #(
	.CLK_HZ (25_200_000),
	.BLINK_HZ (1)
) led_blinky (
	.clk   (gfx_clk),
	.blink (led)
);

endmodule
