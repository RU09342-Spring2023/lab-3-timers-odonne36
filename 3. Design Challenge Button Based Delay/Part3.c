/*
 * Part3.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Matt O'Donnell
 *
 *      YOU NEED TO FILL IN THIS AUTHOR BLOCK
 */


#include<msp430.h>


int main(void){

WDTCTL = WDTPW | WDTHOLD;
__bis_SR_register(LPM3_bits | GIE);
PM5CTL0 &= ~LOCKLPM5;


P1DIR |= BIT0;
P1OUT &= ~BIT0;

        P2OUT |= BIT3;
        P2REN |= BIT3;
        P2IES &= ~BIT3;                         // P2.3 Low --> High edge
        P2IE |= BIT3;

        TB1CCTL0 = CCIE;
        TB1CCR0 = 25000;
        TB1CTL = TBSSEL_1 | MC_2;


}


#pragma vector = TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void)
{


    P1OUT ^= BIT0;
    TB1CCR0 += 25000;
}

















