// /* ##################################################################
// # MILESTONE: 5
// # PROGRAM: 1
// # PROJECT: Final Demo
// # GROUP: 2
// # NAME 1: Khephren, Gould, V01012827
// # NAME 2: Clifton, Tollefson, V01004341
// # DESC: This program implements the main function for the Mech458 final report
// # DATA
// # REVISED ############################################################### *//*
#include <avr/interrupt.h>
#include <avr/io.h>


int main()
{

	//set system clock to 8MHz
	CLKPR = _BV(CLKPCE);
	CLKPR = _BV(CLKPS0);

	while (1)
	{ 
		
	}
	return 0;
} // end main
