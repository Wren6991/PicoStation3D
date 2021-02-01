add_executable(blinky
    main.c
)

target_link_libraries(blinky
	pico_stdlib
)

pico_add_extra_outputs(blinky)
