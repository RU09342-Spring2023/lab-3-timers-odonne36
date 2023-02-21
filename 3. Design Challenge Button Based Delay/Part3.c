/*
 * Part3.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Matt O'Donnell
 *
 *      YOU NEED TO FILL IN THIS AUTHOR BLOCK
 */


#include <msp430.h>

unsigned int t = 25000;
unsigned int led = 0;
void main(){

WDTCTL = WDTPW | WDTHOLD;                       //Disable watchdog
__bis_SR_register(GIE);
PM5CTL0 &= ~LOCKLPM5;


P1DIR |= BIT0;
P1OUT &= ~BIT0;

        P2OUT |= BIT3;
        P2REN |= BIT3;
        P2IES &= ~BIT3;                         // P2.3 Low --> High edge
        P2IE |= BIT3;
        P2IFG &= ~BIT3;


        TB1CCTL0 = CCIE;
        TB1EX0 = 0x011;
     while (1) {


        TB1CCR0 = t;
        TB1CTL = TBSSEL_1 | MC_2;

     }

}


#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{


    P1OUT ^= BIT0;
    TB1CCR0 += t;
}



#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{

P2IFG &= ~BIT3;

if (!led) {

    led = 1;
    P2IES ^= BIT3;
    TB1CTL = TBSSEL_1 | MC_1;

   }

if (led) {

    P2IES ^= BIT3;
     led = 0;
     TB1CTL = TBSSEL_1 | MC_0;
     t = TB1R;
     TB1CTL = TBSSEL_1 | MC_2;

   }







}













