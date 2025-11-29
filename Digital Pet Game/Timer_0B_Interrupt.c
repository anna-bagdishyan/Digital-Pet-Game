/**
* @file Timer_0B_Interrupt.c
*
* @brief Source file for the Timer_0B_Interrupt driver.
*
* This file contains the function definitions for the Timer_0B_Interrupt driver.
* It uses the Timer 0B module to generate periodic interrupts.
*
* @author Anna Bagdishyan and Mario Perez
*/

#include "Timer_0B_Interrupt.h"

// Declare a pointer to the user-defined task
void (*Timer_0B_Task)(void);

void Timer_0B_Interrupt_Init(void(*task)(void))
{

    Timer_0B_Task = task;

    SYSCTL->RCGCTIMER |= 0x01;

    TIMER0->CTL &= ~0x100;

    TIMER0->CFG |= 0x04;

    TIMER0->TBMR |= 0x02;

    TIMER0->TBPR &= ~0x000000FF;

    TIMER0->TBPR = 50;

    TIMER0->TBILR = (1000 - 1);

    TIMER0->ICR |= 0x01;

    TIMER0->IMR |= 0x100;

		NVIC->IPR[5] = (NVIC->IPR[5] & 0x000000E0) | (1 << 7); 

    NVIC->ISER[0] |= (1 << 20);

    TIMER0->CTL |= 0x100;
}

void TIMER0B_Handler(void)
{
	if (TIMER0->MIS & 0x0100)
	{
		(*Timer_0B_Task)();
		TIMER0->ICR |= 0x100;
	}
}