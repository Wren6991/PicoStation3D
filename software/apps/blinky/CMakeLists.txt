add_executable(blinky
    main.c
)

target_link_libraries(blinky
	pico_stdlib
	hardware_pio
)

pico_generate_pio_header(blinky ${CMAKE_CURRENT_LIST_DIR}/fpga_spi_config.pio)


pico_add_extra_outputs(blinky)
