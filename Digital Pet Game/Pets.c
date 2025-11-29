/**
* @file Pets.c
*
* @brief Source file for the custom LCD pet display functions.
*
* This file provides the implementations for drawing the dog,
* turtle, crow, and cat images on the EduBase LCD using custom characters.
*
* @author Anna Bagdishyan and Mario Perez
*
*/

#include "EduBase_LCD.h"


void Dog_Display(void) 
{
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE1_LOCATION, dog_shape1);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE2_LOCATION, dog_shape2);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE3_LOCATION, dog_shape3);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE4_LOCATION, dog_shape4);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE5_LOCATION, dog_shape5);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE6_LOCATION, dog_shape6);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE7_LOCATION, dog_shape7);
	EduBase_LCD_Create_Custom_Character(DOG_SHAPE8_LOCATION, dog_shape8);
							
	EduBase_LCD_Clear_Display();
	EduBase_LCD_Set_Cursor(6, 0);
	EduBase_LCD_Send_Data(0x00);
	EduBase_LCD_Set_Cursor(7, 0);
	EduBase_LCD_Send_Data(0x01);
	EduBase_LCD_Set_Cursor(8, 0);
	EduBase_LCD_Send_Data(0x02);
	EduBase_LCD_Set_Cursor(9, 0);
	EduBase_LCD_Send_Data(0x03);
	EduBase_LCD_Set_Cursor(6, 1);
	EduBase_LCD_Send_Data(0x04);
	EduBase_LCD_Set_Cursor(7, 1);
	EduBase_LCD_Send_Data(0x05);
	EduBase_LCD_Set_Cursor(8, 1);
	EduBase_LCD_Send_Data(0x06);
	EduBase_LCD_Set_Cursor(9, 1);
	EduBase_LCD_Send_Data(0x07);
}

void Turtle_Display(void) 
{
	EduBase_LCD_Create_Custom_Character(TURTLE_SHAPE1_LOCATION, turtle_shape1);
	EduBase_LCD_Create_Custom_Character(TURTLE_SHAPE2_LOCATION, turtle_shape2);
	EduBase_LCD_Create_Custom_Character(TURTLE_SHAPE3_LOCATION, turtle_shape3);
	EduBase_LCD_Create_Custom_Character(TURTLE_SHAPE4_LOCATION, turtle_shape4);
	EduBase_LCD_Create_Custom_Character(TURTLE_SHAPE5_LOCATION, turtle_shape5);
						
}

void Crow_Display(void) 
{
	EduBase_LCD_Create_Custom_Character(CROW_SHAPE1_LOCATION, crow_shape1);
	EduBase_LCD_Create_Custom_Character(CROW_SHAPE2_LOCATION, crow_shape2);
	EduBase_LCD_Create_Custom_Character(CROW_SHAPE3_LOCATION, crow_shape3);
	EduBase_LCD_Create_Custom_Character(CROW_SHAPE4_LOCATION, crow_shape4);
	EduBase_LCD_Create_Custom_Character(CROW_SHAPE5_LOCATION, crow_shape5);
	EduBase_LCD_Create_Custom_Character(CROW_SHAPE6_LOCATION, crow_shape6);

							
	EduBase_LCD_Clear_Display();
	EduBase_LCD_Set_Cursor(6, 0);
	EduBase_LCD_Send_Data(0x00);
	EduBase_LCD_Set_Cursor(7, 0);
	EduBase_LCD_Send_Data(0x01);
	EduBase_LCD_Set_Cursor(8, 0);
	EduBase_LCD_Send_Data(0x02);;
	EduBase_LCD_Set_Cursor(6, 1);
	EduBase_LCD_Send_Data(0x03);
	EduBase_LCD_Set_Cursor(7, 1);
	EduBase_LCD_Send_Data(0x04);
	EduBase_LCD_Set_Cursor(8, 1);
	EduBase_LCD_Send_Data(0x05);
}

void Cat_Display(void) 
{
	EduBase_LCD_Create_Custom_Character(CAT_SHAPE1_LOCATION, cat_shape1);
	EduBase_LCD_Create_Custom_Character(CAT_SHAPE2_LOCATION, cat_shape2);
	EduBase_LCD_Create_Custom_Character(CAT_SHAPE3_LOCATION, cat_shape3);
	EduBase_LCD_Create_Custom_Character(CAT_SHAPE4_LOCATION, cat_shape4);
	EduBase_LCD_Create_Custom_Character(CAT_SHAPE5_LOCATION, cat_shape5);
	EduBase_LCD_Create_Custom_Character(CAT_SHAPE6_LOCATION, cat_shape6);
							
	EduBase_LCD_Clear_Display();
	EduBase_LCD_Set_Cursor(6, 0);
	EduBase_LCD_Send_Data(0x00);
	EduBase_LCD_Set_Cursor(7, 0);
	EduBase_LCD_Send_Data(0x01);
	EduBase_LCD_Set_Cursor(8, 0);
	EduBase_LCD_Send_Data(0x02);;
	EduBase_LCD_Set_Cursor(6, 1);
	EduBase_LCD_Send_Data(0x03);
	EduBase_LCD_Set_Cursor(7, 1);
	EduBase_LCD_Send_Data(0x04);
	EduBase_LCD_Set_Cursor(8, 1);
	EduBase_LCD_Send_Data(0x05);
}