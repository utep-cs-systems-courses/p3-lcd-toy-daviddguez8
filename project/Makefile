# makfile configuration
COMMON_OBJECTS		= ui.o game_state_machine.o switches.o p2_interrupt_handler.o wdtInterruptHandler.o wdt_handler.o led.o buzzer.o button_press.o 
CPU             	= msp430g2553
CFLAGS          	= -mmcu=${CPU} -Os -I../h
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include/ 

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-gcc -mmcu=${CPU} -c

all: moving_demo.elf

#additional rules for files
moving_demo.elf: ${COMMON_OBJECTS} moving_demo.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd 

load: moving_demo.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

ui.o: ui.c ui.h

game_state_machine.o: game_state_machine.c game_state_machine.h ui.h switches.h

switches.o: switches.c switches.h game_state_machine.h

p2_interrupt_handler.o: p2_interrupt_handler.c switches.h

wdtInterruptHandler.o: wdtInterruptHandler.c ui.h

