// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  


void main(void) {
	//call your initialisation functions to set up the hardware modules
    LATHbits.LATH3 = 0; // Set LAT register for LED 2
    LATDbits.LATD7 = 0; // Set LAT register for LED 1
    TRISHbits.TRISH3 = 0; // Set TRIS register for LED 2
    TRISDbits.TRISD7 = 0; // Set TRIS register for LED 1
    
    
    Interrupts_init(); // Initialize interrupt
    DAC_init(); // Initialize DAC
    Comp1_init(); // Initialize Comp1
    LEDarray_init(); // Initialize LED array
    Timer0_init(); // Initialize the timer0
    
    unsigned int a; // use a as a counter to check if sleep mode is entered
    a = 0;

    while (1) {
        if (LATDbits.LATD7 & PORTHbits.RH3) { // When both LEDs are turned ON system enters sleep mode
            Sleep();
        }
        
        LEDarray_disp_bin(get16bitTMR0val() >> 8); //display 8 MSB timer value in binary on LED array
    }
}