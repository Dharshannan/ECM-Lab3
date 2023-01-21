#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source 
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
    
    // Initialize TMR0 interrupts
    PIE0bits.TMR0IE=1; 	//enable interrupt source TMR0
    IPR0bits.TMR0IP = 0; // low priority
    
    // Initialize C1 interrupts
    PIE2bits.C1IE=1; 	//enable interrupt source C1
    IPR2bits.C1IP = 1; // high priority
    
    // Other interrupts
    INTCONbits.IPEN = 1; // Enable interrupt priority
    INTCONbits.PEIE = 1; // peripheral interrupts
    INTCONbits.GIE=1; 	//turn on interrupts globally (when this is off, all interrupts are deactivated)
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/

// Low priority interrupt
void __interrupt(low_priority) LowISR()
{
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
    if(PIR0bits.TMR0IF){ 	//check the interrupt source
        LATHbits.LATH3 = !LATHbits.LATH3; // Toggle LED 2
        TMR0H = 0b00001011; // Reset timer value to 3035 (decimal) this is to accurately measure 1s intervals
        TMR0L = 0b11011011;
        PIR0bits.TMR0IF=0; //clear the interrupt flag!     
    }
}

// High priority interrupt
void __interrupt(high_priority) HighISR()
{
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
    if(PIR2bits.C1IF){ 	//check the interrupt source
        LATDbits.LATD7 = !LATDbits.LATD7; // Toggle LED 1
        PIR2bits.C1IF=0; //clear the interrupt flag!
    }
}
