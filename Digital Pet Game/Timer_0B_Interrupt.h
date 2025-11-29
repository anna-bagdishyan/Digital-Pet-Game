/**
* @file Timer_0B_Interrupt.h
*
* @brief Header file for the Timer_0B_Interrupt driver.
*
* This file contains the function definitions for the Timer_0B_Interrupt driver.
* It uses the Timer 0B module to generate periodic interrupts.
*
* Refer to Table 2-9 (Interrupts) on pages 104 - 106 from the TM4C123G Microcontroller Datasheet
* to view the Vector Number, Interrupt Request (IRO) Number, and the Vector Address
* for each peripheral.
*
* @author Anna Bagdishyan and Mario Perez
*/

#include "TM4C123GH6PM.h"

// Declare a pointer to the user-defined task
extern void (*Timer_0B_Task)(void);

/**
* @brief Initializes the Timer 0B peripheral to generate periodic interrupts.
*
* This function initializes the Timer 0B peripheral to generate periodic interrupts for executing a user-defined task.
* It configures Timer 0B with a 1 ms interval using the 5OMHz system clock source.
* The provided task function will be executed whenever Timer 0B generates an interrupt.
* The priority level is set to 1.
*
* @param task A pointer to the user-defined function to be executed upon Timer 0B interrupt.
*
* @return None
*/
void Timer_0B_Interrupt_Init(void(*task)(void));

/**
* @brief The interrupt service routine (ISR) for Timer 0B.
*
* This function is the interrupt service routine (ISR) for the Timer 0B peripheral.
* It checks the Timer 0B time-out interrupt flag and executes the user-defined task function if the flag is set.
* After executing the task function, it acknowledges the Timer 0B interrupt and clears it.
*
* @param None
*
* @return None
*/
void TIMER0B_Handler(void);