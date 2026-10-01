// /* ##################################################################
// # MILESTONE: 2
// # PROGRAM: 1
// # PROJECT: Lab2 Demo
// # GROUP: 2
// # NAME 1: Khephren, Gould, V01012827
// # NAME 2: Clifton, Tollefson, V01004341
// # DESC: This program implements knight rider with a custom timer as well as an LCD display 
// # DATA
// # REVISED ############################################################### */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "mtimer.h"
#include "mgpio.h"
#include "lcd.h"

#define KNIGHTRIDER_PERIOD (50)
void msysInit(void){
	//set system clock to 8MHz
	CLKPR = _BV(CLKPCE);
	CLKPR = _BV(CLKPS0);
}
int main(int argc,char*argv[]) {
	msysInit();
	// Sets all pins on PORTL to output
	DDRL = 0xFF; 
	// initialize pins to high to turn on LEDs (2 Yel & 2 Grn)
	PORTL = 0xF0; 
	// initialize port C pins to output
	DDRC = 0xFF; 
	//Initialize LCD module
	InitLCD(LS_BLINK|LS_ULINE);
	//Clear the screen
	LCDClear();
	//Simple string printing
	LCDWriteString("Congrats ");

	//A string on line 2
	LCDWriteStringXY(0,1,"Loading ");
	//Print some numbers
	for (i=0;i<99;i+=1)
	{
		LCDWriteIntXY(9,1,i,3);
		LCDWriteStringXY(12,1,"%");
		mTimer(1000);
	}
	//Clear the screen
	LCDClear();
	//Some more text
	LCDWriteString("Hello world");
	LCDWriteStringXY(0,1,"By me");
	//Wait ~ 5 secs
	mTimer(5000);
	//Some More ......
	LCDClear();
	LCDWriteString("    eXtreme");
	LCDWriteStringXY(0,1,"  Electronics");



	mTimer(KNIGHTRIDER_PERIOD);
	while(1){
		PORTC = 0b11000000;
		mTimer(KNIGHTRIDER_PERIOD);
	 	PORTC = 0b11100000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b11110000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b01111000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00111100;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00011110;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00001111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00000111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00000011;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00000111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00001111;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00011110;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b00111100;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b01111000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b11110000;
		mTimer(KNIGHTRIDER_PERIOD);
		PORTC = 0b11100000;
		mTimer(KNIGHTRIDER_PERIOD);

	}	

	return (0); 
	
}

