// /* ##################################################################
// # MILESTONE: 1
// # PROGRAM: 1
// # PROJECT: Lab1 Demo
// # GROUP: X
// # NAME 1: Khephren, Gould, V01012827
// # NAME 2: Clifton, Tollefson, V01004341
// # DESC: This program implements the Knight Rider LED project for Lab 1 of Mech 458
// # DATA
// # REVISED ############################################################### */
// #include <stdlib.h> // the header of the general-purpose standard library of C programming language
// #include <avr/io.h>// the header of I/O port
// #include <util/delay_basic.h>// the header for delay functions
// 
// #define DELAY = 250
// 
// void delaynus(int n) // delay microsecond
// {
// 	int k;
// 	for(k=0;k<n;k++)
// 	_delay_loop_1(1);
// }
// void delaynms(int n) // delay millisecond
// {
// 	int k;
// 	for(k=0;k<n;k++)
// 	delaynus(1000);
// }
// 
// /* ################## MAIN ROUTINE ################## */
// int main(int argc, char *argv[]){
// 	DDRL = 0b11111111; // Sets all pins on PORTL to output
// 	PORTL = 0b11110000; // initialize pins to high to turn on LEDs (2 Yel & 2 Grn)
// 	DDRC = 0xFF; // initialize port C pins to output 
// 	PORTC = 0b11111111; //initialize pins to high to turn on LEDs (8 Red)
// 	delaynms(DELAY);
// 	while(1){
// 		PORTL = 0b00000000;
// 		PORTC = 0b11000000;
// 		delaynms(DELAY);
// 		PORTC = 0b11100000;
// 		delaynms(DELAY);
// 		PORTC = 0b11110000;
// 		delaynms(DELAY);
// 		PORTC = 0b01111000;
// 		delaynms(DELAY);
// 		PORTC = 0b00111100;
// 		delaynms(DELAY);
// 		PORTC = 0b00011110;
// 		delaynms(DELAY);
// 		PORTC = 0b00001111;
// 		delaynms(DELAY);
// 		PORTC = 0b00000111;
// 		delaynms(DELAY);
// 		PORTC = 0b00000011;
// 		delaynms(DELAY);
// 		PORTC = 0b00000111;
// 		delaynms(DELAY);
// 		PORTC = 0b00001111;
// 		delaynms(DELAY);
// 		PORTC = 0b00011110;
// 		delaynms(DELAY);
// 		PORTC = 0b00111100;
// 		delaynms(DELAY);
// 		PORTC = 0b01111000;
// 		delaynms(DELAY);
// 		PORTC = 0b11110000;
// 		delaynms(DELAY);
// 		PORTC = 0b11100000;
// 		delaynms(DELAY);
// 
// 	}
// 	return (0); // This line returns a 0 value to the calling program
// 	// generally means no error was returned
// }