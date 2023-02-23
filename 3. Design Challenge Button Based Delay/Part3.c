/*
 * Part3.c
 *
 *  Created on: Feb 16, 2023
 *      Author: Matt O'Donnell
 *
 *      YOU NEED TO FILL IN THIS AUTHOR BLOCK
 */


#include <msp430.h>

int t = 25000;
unsigned int led = 0;
void main(){

WDTCTL = WDTPW | WDTHOLD;                       //Disable watchdog
__bis_SR_register(GIE);
PM5CTL0 &= ~LOCKLPM5;


P1DIR |= BIT0;
P1OUT &= ~BIT0;

        P2OUT |= BIT3;                          //Set 2.3 as an input
        P2REN |= BIT3;                          //Enable pull-up resistor
        P2IES &= ~BIT3;                         // P2.3 Low --> High edge
        P2IE |= BIT3;                           // Enable interrupts on 2.3
        P2IFG &= ~BIT3;                         //Clear interrupt flag


        TB1CCTL0 = CCIE;                        //Init timer B1 in mode 2 (continuous) with a /2 div
        TB1EX0 = 0x010;
        TB1CCR0 = 25000;
        TB1CTL = TBSSEL_1 | MC_2;


        TB2CCTL0 = CCIE;                        //Init timer b2 in mode 0 (stopped) with a /4 div
        TB2EX0 = 0x011;
        TB2CCR0 = 50000;
        TB2CTL = TBSSEL_1 | MC_0 | TBCLR;






}


#pragma vector = TIMER1_B0_VECTOR               //Timer B1 interrupt
__interrupt void Timer1_B0_ISR(void)            //Blink led and adjust offset
{


    P1OUT ^= BIT0;
    TB1CCR0 += t;
}

#pragma vector = TIMER2_B0_VECTOR               //Timer B2 interrupt
__interrupt void Timer2_B0_ISR(void)            //Adjust offset
{


    P1OUT ^= BIT0;
    TB2CCR0 += t;
}



#pragma vector=PORT2_VECTOR                 //Button 2.3 interrupt
__interrupt void Port_2(void)
{

P2IFG &= ~BIT3;

if (!led) {                                 //Check edge transition

    led = 1;
    P2IES ^= BIT3;                          // Changes edge transition to high -> low
    TB1CTL = TBSSEL_1 | MC_0 | TBCLR;       // Disables timer 1 and starts timer 2
    TB2CTL = TBSSEL_1 | MC_2 | TBCLR;
   }

else if (led) {                                  //Check edge transition

    P2IES ^= BIT3;                          //Changes to low -> high
     led = 0;

     t = TB2R;                              //Reads time in b2 register
     TB2CTL = TBSSEL_1 | MC_0;              //Disables timer b2
     TB1CTL = TBSSEL_1 | MC_2;      //Enables timer b1

   }







}













