#ifndef include_buttons

#define include_buttons



#define buttons (S1|S2|S3|S4)

#define S1 BIT0

#define S2 BIT1

#define S3 BIT2

#define S4 BIT3



void switch_handler();

void switch_init();



#define LED_RED BIT0               // P1.0

#define LED_GREEN BIT6             // P1.6

#define LEDS (BIT0 | BIT6)



extern unsigned char red_on, green_on;

extern unsigned char led_changed;



void led_init();

void led_update();



extern char play;             //Song choice



#endif
