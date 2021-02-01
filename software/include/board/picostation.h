#ifndef _BOARD_PICOSTATION_H
#define _BOARD_PICOSTATION_H

// Note this file is pulled in to all files which include pico.h, via the
// PICO_BOARD build config. This ensures things like default UART pin
// configuration propagate to where they are needed in the SDK

// ----------------------------------------------------------------------------
// Standard SDK defines

#ifndef PICO_DEFAULT_UART
#define PICO_DEFAULT_UART 1
#endif

#ifndef PICO_DEFAULT_UART_TX_PIN
#define PICO_DEFAULT_UART_TX_PIN 12
#endif

#ifndef PICO_DEFAULT_UART_RX_PIN
#define PICO_DEFAULT_UART_RX_PIN 13
#endif

#ifndef PICO_DEFAULT_LED_PIN
#define PICO_DEFAULT_LED_PIN 10
#endif

// W25Q128
#define PICO_FLASH_SIZE_BYTES (16 * 1024 * 1024)

// ----------------------------------------------------------------------------
// Board-specific defines

// SD card
#define PICOSTATION_SD_CLK_PIN 1
#define PICOSTATION_SD_CMD_PIN 0
#define PICOSTATION_SD_DAT0_PIN 2

// Two SNES controller ports
#define PICOSTATION_CTRL_LAT_PIN 6
#define PICOSTATION_CTRL_CLK_PIN 7
#define PICOSTATION_CTRL_DAT0_PIN 8
#define PICOSTATION_CTRL_DAT1_PIN 9

// PWM audio
#define PICOSTATION_AUDIO_PWM_L_PIN 14
#define PICOSTATION_AUDIO_PWM_R_PIN 11

// Still yet to do anything with this, but it could be fun :)
#define PICOSTATION_DVI_CEC_PIN 15

// GFX bus
#define PICOSTATION_GFX_D0_PIN 17
#define PICOSTATION_GFX_CLK_PIN 25
#define PICOSTATION_GFX_HOK_PIN 26
#define PICOSTATION_GFX_DOK_PIN 27
#define PICOSTATION_GFX_IRQ_PIN 28

// FPGA configuration interface (note this overlaps with GFX)
#define PICOSTATION_FPGA_CRESET_PIN 16
#define PICOSTATION_FPGA_CDONE_PIN 19
#define PICOSTATION_FPGA_SPI_SI_PIN PICOSTATION_GFX_HOK_PIN
#define PICOSTATION_FPGA_SPI_SCK_PIN PICOSTATION_GFX_IRQ_PIN
#define PICOSTATION_FPGA_SPI_SS_PIN PICOSTATION_GFX_DOK_PIN

#endif
