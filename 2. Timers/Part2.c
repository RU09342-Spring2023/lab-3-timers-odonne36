/*
 * Part2.c
 *
 *  Created on: Feb 11, 2023
 *      Author: Russell Trafford
 *
 *      This code will need to change the speed of an LED between 3 different speeds by pressing a button.
 */

#include <msp430.h>

void gpioInit();
void timerInit();

unsigned int t = 50000;
void main(){

    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    gpioInit();
    timerInit();

    // Disable the GPIO power-on default high-impedance mode
    // to activate previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    __bis_SR_register(LPM3_bits | GIE);

}


void gpioInit(){
    // @TODO Initialize the Red or Green LED
        P1DIR |= BIT0;
        P1OUT &= ~BIT0;
    // @TODO Initialize Button 2.3
        P2OUT |= BIT3;                          // Configure P2.3 as pulled-up
        P2REN |= BIT3;                          // P2.3 pull-up register enable
        P2IES &= ~BIT3;                         // P2.3 Low --> High edge
        P2IE |= BIT3;

}

void timerInit(){
    // @TODO Initialize Timer B1 in Continuous Mode using ACLK as the source CLK with Interrupts turned on
TB1CCTL0 = CCIE;
TB1CCR0 = 50000;
TB1CTL = TBSSEL_1 | MC_2;
}


/*
 * INTERRUPT ROUTINES
 */

// Port 2 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if (t == 50000)
        t = 25000;
    else if (t==25000)
        t= 5000;
    else if (t== 5000)
        t=50000;
    // @TODO Remember that when you service the GPIO Interrupt, you need to set the interrupt flag to 0.
        P2IFG &= ~BIT3;
    // @TODO When the button is pressed, you can change what the CCR0 Register is for the Timer. You will need to track what speed you should be flashing at.


}


// Timer B1 interrupt service routine
#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{

    P1OUT ^= BIT0;
    TB1CCR0 += t;
}


