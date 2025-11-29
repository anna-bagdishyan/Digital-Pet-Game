/**
 * @file EduBase_LCD.c
 *
 * @brief Source code for the EduBase_LCD driver.
 *
 * This file contains the function definitions for the EduBase_LCD driver.
 * It interfaces with the EduBase Board 16x2 Liquid Crystal Display (LCD). 
 * The following pins are used:
 *  - Data Pin 4      [D4]  (PA2)
 *  - Data Pin 5      [D5]  (PA3)
 *  - Data Pin 6      [D6]  (PA4)
 *  - Data Pin 7      [D7]  (PA5)
 *	- LCD Enable      [E]   (PC6)
 *  - Register Select [RS]  (PE0)
 *
 * @note For more information regarding the LCD, refer to the HD44780 LCD Controller Datasheet.
 * Link: https://www.sparkfun.com/datasheets/LCD/HD44780.pdf
 *
 * @author Aaron Nanas
 */
 
#include "EduBase_LCD.h"

static uint8_t display_control = 0x00;
static uint8_t display_mode = 0x00;

void EduBase_LCD_Ports_Init(void)
{
	SYSCTL->RCGCGPIO |= 0x01;
	GPIOA->DIR |= 0x3C;
	GPIOA->AFSEL &= ~0x3C;
	GPIOA->DEN |= 0x3C;
	GPIOA->DATA &= ~0x3C;
	
	SYSCTL->RCGCGPIO |= 0x04;
	GPIOC->DIR |= 0x40;
	GPIOC->AFSEL &= ~0x40;
	GPIOC->DEN |= 0x40;
	GPIOC->DATA &= ~0x40;
	
	SYSCTL->RCGCGPIO |= 0x10;
	GPIOE->DIR |= 0x01;
	GPIOE->AFSEL &= ~0x01;
	GPIOE->DEN |= 0x01;
	GPIOE->DATA &= ~0x01;
}

void EduBase_LCD_Pulse_Enable(void)
{
	GPIOC->DATA &= ~0x40;
	SysTick_Delay1us(1);
	
	GPIOC->DATA |= 0x40;
	SysTick_Delay1us(1);
	GPIOC->DATA &= ~0x40;
}

void EduBase_LCD_Write_4_Bits(uint8_t data, uint8_t control_flag)
{
	GPIOA->DATA |= (data & 0xF0) >> 0x2;
	
	if (control_flag & 0x01)
	{
		GPIOE->DATA |= 0x01;
	}
	else
	{
		GPIOE->DATA &= ~0x01;
	}
	
	EduBase_LCD_Pulse_Enable();
	
	GPIOA->DATA &= ~0x3C;
	SysTick_Delay1us(1000);
}

void EduBase_LCD_Send_Command(uint8_t command)
{
	EduBase_LCD_Write_4_Bits(command & 0xF0, SEND_COMMAND_FLAG);
	
	EduBase_LCD_Write_4_Bits(command << 0x4, SEND_COMMAND_FLAG);
	
	if (command <3)
	{
		SysTick_Delay1us(1520);
	}
	else
	{
		SysTick_Delay1us(37);
	}
}

void EduBase_LCD_Send_Data(uint8_t data)
{

	EduBase_LCD_Write_4_Bits(data & 0xF0, SEND_DATA_FLAG);
	
	EduBase_LCD_Write_4_Bits(data << 0x4, SEND_DATA_FLAG);
}

void EduBase_LCD_Init(void)
{
	EduBase_LCD_Ports_Init();
	
	SysTick_Delay1us(500000);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(4500);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(4500);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_EIGHT_BIT_MODE, SEND_COMMAND_FLAG);
	SysTick_Delay1us(150);
	
	EduBase_LCD_Write_4_Bits(FUNCTION_SET | CONFIG_FOUR_BIT_MODE, SEND_COMMAND_FLAG);
	
	EduBase_LCD_Send_Command(FUNCTION_SET | CONFIG_5x8_DOTS | CONFIG_TWO_LINES);
	
	EduBase_LCD_Enable_Display();
	
	EduBase_LCD_Return_Home();
	
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Disable_Cursor_Blink();
	EduBase_LCD_Disable_Cursor();
	
	
}
// Sends the clear display command to the LCD
void EduBase_LCD_Clear_Display(void)
{
	EduBase_LCD_Send_Command(CLEAR_DISPLAY);
}
// Sends the return home command to the LCD

void EduBase_LCD_Return_Home(void)
{
	EduBase_LCD_Send_Command(RETURN_HOME);
}

// Sets the cursor position on the LCD based on the specified column and row
void EduBase_LCD_Set_Cursor(uint8_t col, uint8_t row)
{
	if (col <16)
	{
		if (row == 0)
		{
			EduBase_LCD_Send_Command(SET_DDRAM_ADDR | col);
		}
		else if (row ==1)
		{
			EduBase_LCD_Send_Command(SET_DDRAM_ADDR | (col + 0x40));
		}
	}
}

// will send the required values to disable the display
void EduBase_LCD_Disable_Display(void)
{
	display_control = display_control & ~(DISPLAY_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

// will send the required values to enable the display
void EduBase_LCD_Enable_Display(void)
{
display_control = display_control | DISPLAY_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Disable_Cursor(void)
{
	display_control = display_control & ~(CURSOR_ON);
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Enable_Cursor(void)
{
	display_control = display_control | CURSOR_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Disable_Cursor_Blink(void)
{
	display_control = display_control & ~CURSOR_BLINK_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}

void EduBase_LCD_Enable_Cursor_Blink(void)
{
	display_control = display_control | CURSOR_BLINK_ON;
	EduBase_LCD_Send_Command(DISPLAY_CONTROL | display_control);
}
// The Display Shift command scrolls the display’s content based on the specified direction 
void EduBase_LCD_Scroll_Display_Left(void)
{
	EduBase_LCD_Send_Command(CURSOR_OR_DISPLAY_SHIFT | DISPLAY_MOVE | MOVE_LEFT);
}

void EduBase_LCD_Scroll_Display_Right(void)
{
	EduBase_LCD_Send_Command(CURSOR_OR_DISPLAY_SHIFT | DISPLAY_MOVE | MOVE_RIGHT);

}
// The Entry Mode command configures the LCD to display text based on the orientation given.
void EduBase_LCD_Left_to_Right(void)
{
	display_mode = display_mode | ENTRY_SHIFT_INCREMENT;
	EduBase_LCD_Send_Command(ENTRY_MODE_SET | display_mode);
}

void EduBase_LCD_Right_to_Left(void)
{
	display_mode = display_mode & ~ENTRY_SHIFT_INCREMENT;
	EduBase_LCD_Send_Command(ENTRY_MODE_SET | display_mode);
}

// This function will be used to create a custom character and store it in the LCD’s Character
// Generator RAM (CGRAM) at the specified location
void EduBase_LCD_Create_Custom_Character(uint8_t location, uint8_t character_buffer[])
{
	location = location & 0x7;
	EduBase_LCD_Send_Command(SET_CGRAM_ADDR | (location << 3));
	for (int i = 0; i < 8; i++)
	{
		EduBase_LCD_Send_Data(character_buffer[i]);
	}
}


// This function will be used to display a null-terminated string on the LCD, transmitting 
// each character to the LCD one at a time until the end of the string is reached. It uses 
// the strlen function to determine the length of the string. 
void EduBase_LCD_Display_String(char* string)
{
	for (unsigned int i = 0; i < strlen(string); i++)
	{
		EduBase_LCD_Send_Data(string[i]);
	}
}
// These functions will be used to convert integer and double values and convert them to string 
// in order to display them on the LCD using the EduBase_LCD_Display_String function. It uses 
// the sprintf function which is used to format and store a string in a buffer. 
void EduBase_LCD_Display_Integer(int value)
{
	char integer_buffer[32];
	sprintf(integer_buffer, "%d", value);
	EduBase_LCD_Display_String(integer_buffer);
}

void EduBase_LCD_Display_Double(double value)
{
	char double_buffer[32];
	sprintf(double_buffer, "%.6f", value);
	EduBase_LCD_Display_String(double_buffer);
}

void EduBase_LCD_Display_Dog1(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE1_LOCATION);
}

void EduBase_LCD_Display_Dog2(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE2_LOCATION);
}

void EduBase_LCD_Display_Dog3(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE3_LOCATION);
}

void EduBase_LCD_Display_Dog4(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE4_LOCATION);
}

void EduBase_LCD_Display_Dog5(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE5_LOCATION);
}

void EduBase_LCD_Display_Dog6(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE6_LOCATION);
}

void EduBase_LCD_Display_Dog7(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE7_LOCATION);
}

void EduBase_LCD_Display_Dog8(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(DOG_SHAPE8_LOCATION);
}

void EduBase_LCD_Display_Turtle1(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(TURTLE_SHAPE1_LOCATION);
}

void EduBase_LCD_Display_Turtle2(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(TURTLE_SHAPE2_LOCATION);
}

void EduBase_LCD_Display_Turtle3(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(TURTLE_SHAPE3_LOCATION);
}

void EduBase_LCD_Display_Turtle4(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(TURTLE_SHAPE4_LOCATION);
}

void EduBase_LCD_Display_Turtle5(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(TURTLE_SHAPE5_LOCATION);
}

void EduBase_LCD_Display_Crow1(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CROW_SHAPE1_LOCATION);
}

void EduBase_LCD_Display_Crow2(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CROW_SHAPE2_LOCATION);
}

void EduBase_LCD_Display_Crow3(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CROW_SHAPE3_LOCATION);
}

void EduBase_LCD_Display_Crow4(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CROW_SHAPE4_LOCATION);
}

void EduBase_LCD_Display_Crow5(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CROW_SHAPE5_LOCATION);
}

void EduBase_LCD_Display_Crow6(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CROW_SHAPE6_LOCATION);
}

void EduBase_LCD_Display_Cat1(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CAT_SHAPE1_LOCATION);
}

void EduBase_LCD_Display_Cat2(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CAT_SHAPE2_LOCATION);
	
}

void EduBase_LCD_Display_Cat3(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CAT_SHAPE3_LOCATION);
	
}

void EduBase_LCD_Display_Cat4(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CAT_SHAPE4_LOCATION);
	
}

void EduBase_LCD_Display_Cat5(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CAT_SHAPE5_LOCATION);
	
}

void EduBase_LCD_Display_Cat6(void)
{
	EduBase_LCD_Enable_Display();
	EduBase_LCD_Clear_Display();
	
	EduBase_LCD_Set_Cursor(0, 0);
	EduBase_LCD_Send_Data(CAT_SHAPE6_LOCATION);
	
}