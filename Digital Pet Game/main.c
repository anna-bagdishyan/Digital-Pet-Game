/*
 * @file main.c
 *
 * @brief Main source code for Virtual Pet Game program.
 *
 * This file implements the virtual pet gameplay system, including the LCD menu,
 * difficulty selection using the PMOD rotary encoder, the LED hunger bar, heartbeat
 * LED via software PWM, and the seven-segment survival timer. Periodic timers handle
 * hunger decay and timing updates. 

 * @author Anna Bagdishyan and Mario Perez
 */
 
#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
#include "EduBase_LCD.h"
#include "PMOD_ENC.h"
#include "Timer_0A_Interrupt.h"
#include "Timer_1A_Interrupt.h"
#include "Timer_0B_Interrupt.h"
#include "PWM_PF1.h"
#include "Seven_Segment_Display.h"
#include "Pets.h"


#define MAX_COUNT 5

// LED Variables
static uint8_t led_state = 0x00;  // all LEDs off
static int current_led = 3;       // start from LED3
static uint32_t led_delay = 1000; // default 1 second
static uint8_t difficulty_set = 0;

static uint32_t ms_counter = 0;
static uint8_t state = 0;
static uint8_t last_state = 0;
static uint8_t pmod_enc_btn_pressed = 0;
static int main_menu_counter = 0;
static int prev_main_menu_counter = -1;

static uint32_t survival_time = 0;	// milliseconds stayed alive
static uint8_t game_won = 0;
static uint8_t game_lost = 0;

void Display_Main_Menu(int menu_state);
void PMOD_ENC_Task(void);

void Timer_1A_Periodic_Task(void)
{
	if (!game_won && difficulty_set && !game_lost)
  {
		ms_counter++;
    if (ms_counter >= 1000)
    {
			ms_counter = 0;
			if (survival_time >= 1000)
			{
				survival_time -= 1000;
			}
    }
  }
}

// perform refill (reset leds to full) call only when needed
static void refill_leds_if_allowed(void)
{
  // only refill when at least one LED is currently on
	if (led_state != 0x00)
  {
    led_state = 0x0F;
    current_led = 3;
  }
}

int main(void)
{
  SysTick_Delay_Init();
  EduBase_LCD_Init();
  EduBase_LEDs_Init();
  RGB_LED_Init();
  PMOD_ENC_Init();
	Seven_Segment_Display_Init();

  Timer_0A_Interrupt_Init(&PMOD_ENC_Task);
  last_state = PMOD_ENC_Get_State();
	
	PF1_PWM_Init();
	PF1_PWM_Update_Duty_Cycle(0);
	Timer_1A_Interrupt_Init(&Timer_1A_Periodic_Task);
	EduBase_LCD_Create_Custom_Character(RIGHT_ARROW_LOCATION, right_arrow);
	
	while (1)
	{
		// menu display
		if (!difficulty_set)
		{
			if (prev_main_menu_counter != main_menu_counter)
			{
				EduBase_LCD_Clear_Display();
				Display_Main_Menu(main_menu_counter);
				prev_main_menu_counter = main_menu_counter;
			}
		}
		if (pmod_enc_btn_pressed)
		{
			pmod_enc_btn_pressed = 0;
			if (!difficulty_set && main_menu_counter == 5)
			{
				Turtle_Display();
								
				EduBase_LCD_Clear_Display();
				EduBase_LCD_Set_Cursor(0, 0);
				EduBase_LCD_Send_Data(0x00);
				EduBase_LCD_Set_Cursor(1, 0);
				EduBase_LCD_Send_Data(0x01);
				EduBase_LCD_Set_Cursor(2, 0);
				EduBase_LCD_Send_Data(0x02);
				SysTick_Delay1ms(300);
						
				for (int i = 0; i < 13; i++)
				{
					EduBase_LCD_Scroll_Display_Right();
					SysTick_Delay1ms(300);
				}
							
				EduBase_LCD_Clear_Display();
				EduBase_LCD_Set_Cursor(0, 0);
				EduBase_LCD_Display_String("Moonwalk!");
				SysTick_Delay1ms(1500);
				EduBase_LCD_Clear_Display();
							
				Turtle_Display();
							
				EduBase_LCD_Set_Cursor(14, 0);
				EduBase_LCD_Send_Data(0x00);
				EduBase_LCD_Set_Cursor(15, 0);
				EduBase_LCD_Send_Data(0x01);
				EduBase_LCD_Set_Cursor(16, 0);
				EduBase_LCD_Send_Data(0x02);
						
											
				for (int i = 0; i < 14; i++)
				{
					EduBase_LCD_Scroll_Display_Left();
					SysTick_Delay1ms(300);
				}
								
				EduBase_LCD_Clear_Display();
				prev_main_menu_counter = -1;
							
				EduBase_LCD_Create_Custom_Character(RIGHT_ARROW_LOCATION, right_arrow);
				continue;
			}
			if (!difficulty_set)
			{
				difficulty_set = 1;
				led_state = 0x0F;
				current_led = 3;
				game_won = 0;
				
				EduBase_LCD_Clear_Display();
				EduBase_LCD_Set_Cursor(0, 0);
				EduBase_LCD_Display_String("Keep Pet Alive");
				EduBase_LCD_Set_Cursor(0, 1);
				EduBase_LCD_Display_String("For 8 Seconds!");
				SysTick_Delay1ms(3000);
							
				survival_time = 8000; // 8 second countdown
				ms_counter = 0; 
				
				switch (main_menu_counter)
				{
					case 0x00: 
						led_delay = 1000; // easy
						Dog_Display();
						break;
					case 0x01:
						led_delay = 500; // medium
						Crow_Display();
						break;
					case 0x02:
						led_delay = 500; // medium
						Crow_Display();
						break;
					case 0x03:    // hard
						led_delay = 250; 
						Cat_Display();
						break;
					case 0x04:    // hard
						led_delay = 250;
						Cat_Display();									
						break;
				}
			}
			else if (!game_won)
			{
				refill_leds_if_allowed();
			}
		}
		if (difficulty_set && !game_won)
		{
			EduBase_LEDs_Output(led_state);
			// update PF1 PWM duty cycle based on current LED state
			PF1_PWM_Update_Duty_Cycle(led_state);
			
			Seven_Segment_Display(survival_time / 1000);
			if (led_state == 0x00 && !game_won && !game_lost) 
			{		
				game_lost = 1;
				EduBase_LCD_Clear_Display();
				EduBase_LCD_Set_Cursor(0, 0);
				EduBase_LCD_Display_String("YOU LOSE!");
			}		
			if (survival_time == 0 && !game_lost)   // 10 seconds to win
			{
				game_won = 1;
				// display player has won
				EduBase_LCD_Clear_Display();
				EduBase_LCD_Set_Cursor(0, 0);
				EduBase_LCD_Display_String("YOU WIN!");
			}
		}
		// winning condition met, flash leds
		if (game_won)
		{
			uint8_t leds = 0x00;
			for (int i = 0; i < 12; i++) //flashes leds 6 times
			{
				leds ^= 0x0F;
				EduBase_LEDs_Output(leds);
				SysTick_Delay1ms(200);
			}
			// stops leds from flashing, ends game
			while(1);
		}
			
		// only runs while winning condition is not met
		if (difficulty_set && !game_won)
		{
			if (current_led >= 0)
			{
				EduBase_LEDs_Output(led_state);
				SysTick_Delay1ms(led_delay);

				if (pmod_enc_btn_pressed)
				{
						pmod_enc_btn_pressed = 0;
						refill_leds_if_allowed();
						EduBase_LEDs_Output(led_state);
						continue;
				}
				// turn off current led
				led_state &= ~(1 << current_led);
				current_led--;
				EduBase_LEDs_Output(led_state);
				}
		}
		SysTick_Delay1ms(50);
	}
}

// display the current menu on LCD
void Display_Main_Menu(int menu_state)
{
  switch(menu_state)
  {
		case 0x00:
    {
			EduBase_LCD_Set_Cursor(0,0);
      EduBase_LCD_Send_Data(0x03);
      EduBase_LCD_Set_Cursor(1,0);
      EduBase_LCD_Display_String("EASY");
      EduBase_LCD_Set_Cursor(1,1);
			EduBase_LCD_Display_String("MEDIUM");
      break;
    }
    case 0x01:
    {
      EduBase_LCD_Set_Cursor(0,1);
      EduBase_LCD_Send_Data(0x03);
      EduBase_LCD_Set_Cursor(1,0);
      EduBase_LCD_Display_String("EASY");
      EduBase_LCD_Set_Cursor(1,1);
			EduBase_LCD_Display_String("MEDIUM");
      break;
    }
    case 0x02:
    {
      EduBase_LCD_Set_Cursor(0,0);
      EduBase_LCD_Send_Data(0x03);
      EduBase_LCD_Set_Cursor(1,0);
      EduBase_LCD_Display_String("MEDIUM");
			EduBase_LCD_Set_Cursor(1,1);
      EduBase_LCD_Display_String("HARD");
      break;
    }
		case 0x03:
    {
      EduBase_LCD_Set_Cursor(0,1);
      EduBase_LCD_Send_Data(0x03);
      EduBase_LCD_Set_Cursor(1,0);
      EduBase_LCD_Display_String("MEDIUM");
      EduBase_LCD_Set_Cursor(1,1);
      EduBase_LCD_Display_String("HARD");
      break;
    }
		case 0x04:
		{
			EduBase_LCD_Set_Cursor(0,0);
      EduBase_LCD_Send_Data(0x03);
      EduBase_LCD_Set_Cursor(1,0);
			EduBase_LCD_Display_String("HARD");
      EduBase_LCD_Set_Cursor(1,1);
      EduBase_LCD_Display_String("DISPLAY PET");
      break;
		}
		case 0x05:
		{
			EduBase_LCD_Set_Cursor(0,1);
      EduBase_LCD_Send_Data(0x03);
      EduBase_LCD_Set_Cursor(1,0);
      EduBase_LCD_Display_String("HARD");
      EduBase_LCD_Set_Cursor(1,1);
      EduBase_LCD_Display_String("DISPLAY PET");
      break;
		}				
  }
}

void PMOD_ENC_Task(void)
{
  state = PMOD_ENC_Get_State();
	
  // detect button press ALWAYS (even after difficulty is set)
  if (PMOD_ENC_Button_Read(state) && !PMOD_ENC_Button_Read(last_state))
  {
		pmod_enc_btn_pressed = 1;
  }

  // only allow menu rotation before difficulty is set
	// PMOD ENC button can now be used otherwise
  if (!difficulty_set)
  {
		main_menu_counter = main_menu_counter + PMOD_ENC_Get_Rotation(state, last_state);
    if (main_menu_counter < 0)
		{
      main_menu_counter = 0;
		}
    else if (main_menu_counter > MAX_COUNT)
		{
      main_menu_counter = MAX_COUNT;
		}
  }
	last_state = state;
}