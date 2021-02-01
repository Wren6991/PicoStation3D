CHIPNAME=picostation
DOTF=$(HDL)/fpga/picostation_fpga.f

DEVICE=up5k
PACKAGE=sg48
SYNTH_OPT=-retime
PNR_OPT=--pre-pack picostation_prepack.py --timing-allow-fail


include $(SCRIPTS)/synth_ice40.mk

header: bit
	xxd -i $(CHIPNAME).bin > $(CHIPNAME)_bitstream.h
