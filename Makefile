################################################################################
#	@file			Makefile
#	@brief		This makefile is for project.
#	@author		llHoYall <HoYa128@gmail.com>
################################################################################
#	@version	v1.0
#	@note
#		- 2018.01.05	Created.
################################################################################

JOB	:= -j$(shell getconf _NPROCESSORS_ONLN)
OPT	:= --no-print-directory

all:
	@make $(JOB) $(OPT) -f projects/stm32f401re-nucleo_uart/Makefile
	@make $(JOB) $(OPT) -f projects/stm32f401re-nucleo_freertos/Makefile

stm32f401re-nucleo_freertos:
	@make $(JOB) $(OPT) -f projects/stm32f401re-nucleo_freertos/Makefile

stm32f401re-nucleo_uart:
	@make $(JOB) $(OPT) -f projects/stm32f401re-nucleo_uart/Makefile

clean:
	@make $(JOB) $(OPT) -f projects/stm32f401re-nucleo_freertos/Makefile clean
	@make $(JOB) $(OPT) -f projects/stm32f401re-nucleo_uart/Makefile clean
