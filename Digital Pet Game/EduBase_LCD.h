/**
 * @file EduBase_LCD.h
 *
 * @brief Header file for the EduBase_LCD driver.
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

#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include <string.h>
#include <stdio.h>

static uint8_t dog_shape1[8] = {
  0x03,
  0x0C,
  0x10,
  0x10,
  0x10,
  0x11,
  0x16,
  0x1A
};
static uint8_t dog_shape2[8] = {
  0x18,
  0x07,
  0x00,
  0x10,
  0x10,
  0x00,
  0x08,
  0x18
};

static uint8_t dog_shape3[8] = { //h
  0x03,
  0x1C,
  0x00,
  0x01,
  0x01,
  0x00,
  0x02,
  0x03
};

static uint8_t dog_shape4[8] = {
  0x18,
  0x06,
  0x01,
  0x01,
  0x01,
  0x11,
  0x0D,
  0x0B
};

static uint8_t dog_shape5[8] = {
  0x02,
  0x02,
  0x02,
  0x02,
  0x01,
  0x00,
  0x00,
  0x00
};

static uint8_t dog_shape6[8] = {
	0x18,
  0x18,
  0x03,
  0x01,
  0x00,
  0x11,
  0x0E,
  0x01
};

static uint8_t dog_shape7[8] = {
  0x03,
  0x03,
  0x18,
  0x10,
  0x00,
  0x11,
  0x0E,
  0x10
};

static uint8_t dog_shape8[8] = {
	0x08,
  0x08,
  0x08,
  0x08,
  0x10,
  0x00,
  0x00,
  0x00
};

static uint8_t turtle_shape1[8] = {
	0x01,
  0x02,
  0x04,
  0x08,
  0x1C,
  0x13,
  0x18,
  0x09
};

static uint8_t turtle_shape2[8] = {
	 0x10,
  0x0B,
  0x04,
  0x05,
  0x04,
  0x18,
  0x03,
  0x12
};

static uint8_t turtle_shape3[8] = {
	0x00,
  0x10,
  0x18,
  0x08,
  0x08,
  0x18,
  0x10,
  0x00
};

static uint8_t turtle_shape4[8] = {
	0x0E,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

static uint8_t turtle_shape5[8] = {
	0x0E,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

static uint8_t crow_shape1[8] = {
	0x03,
  0x07,
  0x0A,
  0x11,
  0x0F,
  0x03,
  0x07,
  0x07
};

static uint8_t crow_shape2[8] = {
  0x18,
  0x1C,
  0x1C,
  0x1E,
  0x1F,
  0x1F,
  0x0F,
  0x0F
};

static uint8_t crow_shape3[8] = {
	0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00,
  0x10,
  0x10
};

static uint8_t crow_shape4[8] = {
  0x07,
  0x03,
  0x01,
  0x00,
  0x00,
  0x00,
  0x00,
  0x00
};

static uint8_t crow_shape5[8] = {
  0x17,
  0x1B,
  0x1D,
  0x0F,
  0x1B,
  0x00,
  0x00,
  0x00
};

static uint8_t crow_shape6[8] = {
  0x18,
  0x1C,
  0x1E,
  0x10,
  0x00,
  0x00,
  0x00,
  0x00
};

static uint8_t cat_shape1[8] = {
  0x0E,
  0x09,
  0x08,
  0x08,
  0x13,
  0x17,
  0x17,
  0x10
};

static uint8_t cat_shape2[8] = {
	0x01,
  0x02,
  0x1C,
  0x00,
  0x01,
  0x03,
  0x03,
  0x08
};

static uint8_t cat_shape3[8] = {
  0x18,
  0x08,
  0x08,
  0x08,
  0x14,
  0x14,
  0x14,
  0x04
};

static uint8_t cat_shape4[8] = {
  0x0C,
  0x02,
  0x02,
  0x02,
  0x04,
  0x04,
  0x04,
  0x03
};

static uint8_t cat_shape5[8] = {
  0x00,
  0x01,
  0x01,
  0x01,
  0x00,
  0x14,
  0x14,
  0x1F
};

static uint8_t cat_shape6[8] = {
  0x18,
  0x00,
  0x02,
  0x05,
  0x15,
  0x19,
  0x12,
  0x1C
};


static uint8_t up_arrow[8] =
{
	0x00,
	0x04,
	0x0E,
	0x15,
	0x04,
	0x04,
	0x04,
	0x04
};
	
static uint8_t down_arrow[8] = 
{
	0x04,
	0x04,
	0x04,
	0x04,
	0x04,
	0x15,
	0x0E,
	0x04
};
	
static uint8_t left_arrow[8] =
{
	0x00,
	0x04,
	0x08,
	0x1F,
	0x08,
	0x04,
	0x00,
	0x00
};
	
static uint8_t right_arrow[8] =
{
	0x00,
	0x04,
	0x02,
	0x1F,
	0x02,
	0x04,
	0x00,
	0x00
};

enum LCD_Commands
{
	CLEAR_DISPLAY         	= 0x01,
	RETURN_HOME             = 0x02,
	ENTRY_MODE_SET          = 0x04,
	DISPLAY_CONTROL         = 0x08,
	CURSOR_OR_DISPLAY_SHIFT =	0x10,
	FUNCTION_SET            =	0x20,
	SET_CGRAM_ADDR          =	0x40,
	SET_DDRAM_ADDR          =	0x80
};

enum Entry_Mode_Bits
{
	ENTRY_SHIFT_DISABLE     =	0x00,
	ENTRY_SHIFT_ENABLE      =	0x01,
	ENTRY_SHIFT_DECREMENT   = 0x00,
	ENTRY_SHIFT_INCREMENT   = 0x02
};

enum Display_Control_Bits
{
	CURSOR_BLINK_OFF        = 0x00,
	CURSOR_BLINK_ON         = 0x01,
	CURSOR_OFF              = 0x00,
	CURSOR_ON               = 0x02,
	DISPLAY_OFF             = 0x00,
	DISPLAY_ON              = 0x04
};

enum Cursor_or_Display_Shift_Bits
{
	CURSOR_MOVE             = 0x00,
	DISPLAY_MOVE            = 0x08,
	MOVE_LEFT               = 0x00,
	MOVE_RIGHT              = 0x04
};

enum Function_Set_Bits
{
	CONFIG_5x8_DOTS         = 0x00,
	CONFIG_5x10_DOTS        = 0x04,
	CONFIG_FOUR_BIT_MODE    = 0x00,
	CONFIG_EIGHT_BIT_MODE   = 0x10,
	CONFIG_ONE_LINE         = 0x00,
	CONFIG_TWO_LINES        = 0x08
};

enum LCD_Register_Select_Flags
{
	SEND_COMMAND_FLAG       = 0x00,
	SEND_DATA_FLAG          = 0x01
};

enum Custom_Character_CGRAM_Locations
{
	UP_ARROW_LOCATION       = 0x00,
	DOWN_ARROW_LOCATION     = 0x01,
	LEFT_ARROW_LOCATION     = 0x02,
	RIGHT_ARROW_LOCATION    = 0x03,
	
	DOG_SHAPE1_LOCATION			= 0x00,
	DOG_SHAPE2_LOCATION			= 0x01,
	DOG_SHAPE3_LOCATION			= 0x02,
	DOG_SHAPE4_LOCATION			= 0x03,
	DOG_SHAPE5_LOCATION			= 0x04,
	DOG_SHAPE6_LOCATION			= 0x05,
	DOG_SHAPE7_LOCATION			= 0x06,
	DOG_SHAPE8_LOCATION			= 0x07,
	
	TURTLE_SHAPE1_LOCATION  = 0x00,
	TURTLE_SHAPE2_LOCATION  = 0x01,
	TURTLE_SHAPE3_LOCATION  = 0x02,
	TURTLE_SHAPE4_LOCATION  = 0x03,
	TURTLE_SHAPE5_LOCATION  = 0x04,
	
	CROW_SHAPE1_LOCATION			= 0x00,
	CROW_SHAPE2_LOCATION			= 0x01,
	CROW_SHAPE3_LOCATION			= 0x02,
	CROW_SHAPE4_LOCATION			= 0x03,
	CROW_SHAPE5_LOCATION			= 0x04,
	CROW_SHAPE6_LOCATION			= 0x05,
	
	CAT_SHAPE1_LOCATION			= 0x00,
	CAT_SHAPE2_LOCATION			= 0x01,
	CAT_SHAPE3_LOCATION			= 0x02,
	CAT_SHAPE4_LOCATION			= 0x03,
	CAT_SHAPE5_LOCATION			= 0x04,
	CAT_SHAPE6_LOCATION			= 0x05
};


/**
 * @brief Initializes the GPIO pins used by the 16x2 LCD on the EduBase board.
 *
 * This function initializes the following output GPIO pins used by the 
 * 16x2 Liquid Crystal Display (LCD) on the EduBase board.
 *  - Data Pin 4      [D4]  (PA2)
 *  - Data Pin 5      [D5]  (PA3)
 *  - Data Pin 6      [D6]  (PA4)
 *  - Data Pin 7      [D7]  (PA5)
 *	- LCD Enable      [E]   (PC6)
 *  - Register Select [RS]  (PE0)
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Ports_Init(void);

/**
 * @brief Generates a short pulse on the LCD enable pin to initiate data transmission.
 *
 * This function generates a short pulse on the LCD enable pin (PC6) to initiate
 * data transmission to the 16x2 Liquid Crystal Display (LCD) on the EduBase board.
 * A minimum pulse width greater than 450 nanoseconds is provided as specified in the datasheet.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Pulse_Enable(void);

/**
 * @brief Transmits a 4-bit data at a time to the LCD.
 *
 * This function transmits a 4-bit data at a time to the LCD. It takes an 8-bit data input 
 * and extracts the upper nibble, which is then shifted to align with the pins connected 
 * to the LCD's data lines (PA2 - PA5). The control flag determines whether the operation is a data write
 * or a command write. After setting the data lines and control pin accordingly, it pulses 
 * the LCD enable pin to signal the LCD to latch in the data.
 *
 * @param data The 8-bit data to be sent to the LCD.
 
 * @param control_flag A flag indicating whether the operation is a data write or a command write.
 *                     Indicates a command write if cleared (0); Otherwise, it performs a data write
 *                     operation when set (1).
 *
 * @return None
 */
void EduBase_LCD_Write_4_Bits(uint8_t data, uint8_t control_flag);

/**
 * @brief Sends a command to the LCD.
 *
 * This function sends an 8-bit command to the LCD using the EduBase_LCD_Write_4_Bits function.
 * It transmits the upper nibble of the command first, and then it transmits the lower nibble. The timing 
 * of the delays after sending the command depends on the specific command being executed.
 * For the first two commands (i.e. Clear Display and Return Home), a delay of 1.52 ms is required.
 * The rest of the commands require a delay of 37 us.
 *
 * @param command The 8-bit command to be sent to the LCD.
 *
 * @return None
 *
 * @note The commands are listed on pages 24-25 of the HD44780 LCD Controller datasheet.
 */
void EduBase_LCD_Send_Command(uint8_t command);

/**
 * @brief Sends an 8-bit data byte to the LCD.
 *
 * This function sends an 8-bit data byte to the LCD using the EduBase_LCD_Write_4_Bits function.
 * It transmits the upper nibble of the command first, and then it transmits the lower nibble.
 *
 * @param data The 8-bit data byte to be sent to the LCD.
 *
 * @return None
 */
void EduBase_LCD_Send_Data(uint8_t data);

/**
 * @brief Initializes the LCD module connected to the EduBase board.
 *
 * This function initializes the LCD module by performing the following steps:
 * - Initializes the required GPIO pins for interfacing with the LCD.
 * - Waits for 50 ms to allow the LCD to power up.
 * - Sends the function commands several times as part of the LCD initialization sequence
 *   specified in pages 45-46 of the HD44780 LCD Controller datasheet.
 * - Sets up the LCD configuration
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Init(void);

/**
 * @brief Clears the display of the LCD.
 *
 * This function sends the Clear Display command (0x01) to the LCD to clear its display.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Clear_Display(void);

/**
 * @brief Returns the cursor to the original position.
 *
 * This function sends the Return Home command (0x02) to the LCD to move the cursor to the home position.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Return_Home(void);

/**
 * @brief Sets the cursor position on the LCD.
 *
 * This function sets the cursor position on the LCD based on the specified column and row.
 * It assumes that a 16x2 LCD is used.
 *
 * @param col The column index (0-15) where the cursor should be positioned.
 *
 * @param row The row index (0 or 1) where the cursor should be positioned.
 *
 * @return None
 */
void EduBase_LCD_Set_Cursor(uint8_t col, uint8_t row);

/**
 * @brief Disables the display on the LCD.
 *
 * This function disables the display on the LCD by clearing the Display (D) bit.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Disable_Display(void);

/**
 * @brief Enables the display on the LCD.
 *
 * This function enables the display on the LCD by setting the Display (D) bit.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Enable_Display(void);

/**
 * @brief Disables the cursor on the LCD.
 *
 * This function disables the cursor on the LCD by clearing the Cursor (C) bit.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Disable_Cursor(void);

/**
 * @brief Enables the cursor on the LCD.
 *
 * This function enables the cursor on the LCD by setting the Cursor (C) bit.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Enable_Cursor(void);

/**
 * @brief Disables the cursor blink on the LCD.
 *
 * This function disables the cursor blink on the LCD by clearing the Cursor Blink (B) bit.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Disable_Cursor_Blink(void);

/**
 * @brief Enables the cursor blink on the LCD.
 *
 * This function enables the cursor blink on the LCD by setting the Cursor Blink (B) bit.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Enable_Cursor_Blink(void);

/**
 * @brief Scrolls the display content to the left on the LCD using the Display Shift command.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Scroll_Display_Left(void);

/**
 * @brief Scrolls the display content to the right on the LCD using the Display Shift command.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Scroll_Display_Right(void);

/**
 * @brief Sets the LCD to display text from left to right using the Entry Mode command.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Left_to_Right(void);

/**
 * @brief Sets the LCD to display text from right to left using the Entry Mode command.
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Right_to_Left(void);

/**
 * @brief Creates a custom character and stores it in the LCD's Character Generator RAM (CGRAM).
 *
 * This function creates a custom character and stores it in the LCD's 
 * Character Generator RAM (CGRAM) at the specified location.
 *
 * @param location The location (0-7) in CGRAM where the custom character will be stored.
 *
 * @param character_buffer An array containing the pixel pattern of the custom character.
 *
 * @return None
 */
void EduBase_LCD_Create_Custom_Character(uint8_t location, uint8_t character_buffer[]);

/**
 * @brief Displays a string on the LCD.
 *
 * This function displays a null-terminated string on the LCD. The string is iterated 
 * character by character until the end of the string is reached.
 *
 * @param string A char pointer that holds the address of a sequence of char values (i.e. string).
 *
 * @return None
 */
void EduBase_LCD_Display_String(char* string);

/**
 * @brief Converts the integer value to string to display it on the LCD using sprintf.
 *
 * @param value An integer that will be converted to string.
 *
 * @return None
 */
void EduBase_LCD_Display_Integer(int value);

/**
 * @brief Converts the double value to string to display it on the LCD using sprintf.
 *
 * @param value A double that will be converted to string.
 *
 * @return None
 */
void EduBase_LCD_Display_Double(double value);

/**
* @brief Displays dog frame 1 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog1(void);

/**
* @brief Displays dog frame 2 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog2(void);

/**
* @brief Displays dog frame 3 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog3(void);

/**
* @brief Displays dog frame 4 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog4(void);

/**
* @brief Displays dog frame 5 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog5(void);

/**
* @brief Displays dog frame 6 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog6(void);

/**
* @brief Displays dog frame 7 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog7(void);

/**
* @brief Displays dog frame 8 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Dog8(void);

/**
* @brief Displays turtle frame 1 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Turtle1(void);

/**
* @brief Displays turtle frame 2 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Turtle2(void);

/**
* @brief Displays turtle frame 3 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Turtle3(void);

/**
* @brief Displays turtle frame 4 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Turtle4(void);

/**
* @brief Displays turtle frame 5 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Turtle5(void);

/**
* @brief Displays crow frame 1 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Crow1(void);

/**
* @brief Displays crow frame 2 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Crow2(void);

/**
* @brief Displays crow frame 3 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Crow3(void);

/**
* @brief Displays crow frame 4 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Crow4(void);

/**
* @brief Displays crow frame 5 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Crow5(void);

/**
* @brief Displays cat frame 1 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Cat1(void);

/**
* @brief Displays cat frame 2 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Cat2(void);

/**
* @brief Displays cat frame 3 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Cat3(void);

/**
* @brief Displays cat frame 4 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Cat4(void);

/**
* @brief Displays cat frame 5 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Cat5(void);

/**
* @brief Displays cat frame 6 on the LCD
 *
 * @param None
 *
 * @return None
 */
void EduBase_LCD_Display_Cat6(void);