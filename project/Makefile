# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../demos/h
LDFLAGS         = -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: project2.elf

#additional rules for files
project2.elf: ${COMMON_OBJECTS} main.o buzzer.o p2_interrupt_handler.o state_machine.o toggle.o led.o switches.o  ../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

clean:
	rm -f *.o *.elf

load: project2.elf
	mspdebug rf2500 "prog $^"

