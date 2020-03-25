# makfile configuration
COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I../demos/h
LDFLAGS         = -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: starWars.elf

#additional rules for files
starWars.elf: ${COMMON_OBJECTS} main.o buzzer.o note_interrupt_handler.o warsBuzz.o buttons.o ../demos/lib/libTimer.a
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

clean:
	rm -f *.o *.elf

load: starWars.elf
	mspdebug rf2500 "prog $^"

main.o: buzzer.h
buzzer.c: buzzer.h
buttons.o: buttons.h buzzer.h warsBuzz.h
warsBuzz.o:warsBuzz.h buzzer.h
note_interrupt_handler.o: warsBuzz.h
