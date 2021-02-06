add_executable(pwm_sine_wave
    main.c
)

target_link_libraries(pwm_sine_wave
	pico_stdlib
	hardware_pwm
)

pico_add_extra_outputs(pwm_sine_wave)
