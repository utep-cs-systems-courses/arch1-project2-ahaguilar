To compile this program use make all, then use make load to load the program
into the MSP430



On this project I programmed a MSP430 to play a song and use the LEDS in two
ways, make a binary counter from 0 to 3 and display a light dimming with the
same function of an interrupt. The program turns leds on/off, and make sounds
with the buzzer by using the buttons on the MSP430.



I use a switch button from the MSP430 on Port 2 to play a different note of a
song.



Button 1 does a blinking binary counter. Button S2 plays the Star Wars Force song. Button
S4 stop the program and turn on and then dimming the red led indicating that
the toy is "off".


To clean project use make clean.
