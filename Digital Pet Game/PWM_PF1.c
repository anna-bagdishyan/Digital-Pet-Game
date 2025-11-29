/**
 * @file PWM_PF1.c
 *
 * @brief Software PWM driver for PF1 LED.
 *
 * This driver generates a PWM signal on PF1 using SysTick delays.
 * Duty cycle can be updated at runtime to change LED brightness.
 *
 * @author Anna Bagdishyan and Mario Perez
 */

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "Timer_0B_Interrupt.h"

// PF1 PWM configuration
static uint8_t PF1_Duty_Cycle = 50;  // default 50%
static uint16_t PF1_Period_ms = 20;  // 20 ms period
static uint8_t PWM_Counter = 0;

// update duty cycle
void PF1_PWM_Update_Duty_Cycle(uint8_t led_state)
{
  uint8_t count = 0;
	if (led_state & 0x01) {
		count++;
	}
	if (led_state & 0x02) {
		count++;
	}
	if (led_state & 0x04) {
		count++;
	}
	if (led_state & 0x08) {
		count++;
	}
	
	switch(count)
	{
		case 4:
			PF1_Duty_Cycle = 100;
			break;
		case 3:
			PF1_Duty_Cycle = 50;
			break;
		case 2:
			PF1_Duty_Cycle = 25;
			break;
		case 1:
			PF1_Duty_Cycle = 10;
			break;
		default:
			PF1_Duty_Cycle = 0;
			break;
	}
}

void PF1_PWM_Timer_Handler(void) 
{
	if (PWM_Counter < ((PF1_Period_ms * PF1_Duty_Cycle) / 100))
	{
		GPIOF->DATA |= 0x02;
	}
	else
	{
		GPIOF->DATA &= ~0x02;
	}
	PWM_Counter++;
	
	if (PWM_Counter >= PF1_Period_ms)
	{
		PWM_Counter = 0;
	}
}

void PF1_PWM_Init(void)
{
    // enable clock to Port F
    SYSCTL->RCGCGPIO |= 0x20;

    // set PF1 as output
    GPIOF->DIR |= 0x02;
    // enable digital functionality
    GPIOF->DEN |= 0x02;
	
   Timer_0B_Interrupt_Init(&PF1_PWM_Timer_Handler);
}