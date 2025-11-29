/**
 * @file PWM_PF1.c
 *
 * @brief Header file for the PWM_PF1 driver
 *
 * @author Anna Bagdishyan and Mario Perez
 */
 
#include "TM4C123GH6PM.h"

/**
* @brief Initializes PF1 for software PWM using Timer 0B
*/
void PF1_PWM_Init(void);

/**
* @brief Updates the duty cycle based on the current hunger LED state*
*
* @param led_state (PB0-PB3)
*/
void PF1_PWM_Update_Duty_Cycle(uint8_t led_state);

/**
* @brief Timer interrupt handler used for generated PWM
*/
void PF1_PWM_Timer_Handler(void);