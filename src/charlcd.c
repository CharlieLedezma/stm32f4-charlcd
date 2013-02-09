/*
 *
 * charlcd.c
 *
 * Interfaces an stm32f4 series microcontroller with an HD44780 LCD.
 *
 * Should be simple enough to adapt this to your needs, may need some changes 
 * to the .h file as well.
 *
 * Copyright 2013 Tom McLeod, please see the LICENSE file in the projects root 
 * directory for more info.
 *
 */

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "charlcd.h"

void CharLCD_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Open the clocks we want
	RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,ENABLE);

	// Configure the LCD pins for push-pull output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOE,&GPIO_InitStructure);

	// Control pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}

void CharLCD_Init(void)
{
	Set_RS;
	Set_RW;
	Set_Clk;

	CharLCD_Delay(0xFFFFFF);

	Clr_RS;
	Clr_RW;
	Clr_Clk;

	Set_Clk;

	CharLCD_Delay(0xFFFFF);			// Long delay to see if it helps

	// 8-bit, 2-line (4-line displays use 2-line with more characters
	// per line)
	CharLCD_WriteData(0x38);

	CharLCD_Delay(0xFFFFFF);			// Long delay to see if it helps

	Clr_Clk;

	CharLCD_Delay(0xFFFFFF);

	Set_Clk;

	CharLCD_Delay(0xFFFFF);

	// increment left, no screen shift
	CharLCD_WriteData(0x06);

	CharLCD_Delay(0xFFFFFF);

	Clr_Clk;

	// Turn display on, with cursor on and blinking
	CharLCD_WriteData(0x0F);

	Set_Clk;

	CharLCD_Delay(0xFFFFF);

	GPIO_SetBits(GPIOE,GPIO_Pin_4);

	CharLCD_Delay(0xFFFFFF);

	Clr_Clk;

	CharLCD_Delay(0xFFFFFF);

	GPIO_ResetBits(GPIOE,GPIO_Pin_4);

	Set_Clk;

	CharLCD_Delay(0xFFFFFF);

	Clr_Clk;

	// Clear the pins (just in case)
	CharLCD_WriteData(0x00);
}

/*
 * Host write timing diagram:
 *     ------\ /-----------------\ /------
 * RS (low if X writing register, X high if not)
 *     ______/ \_________________/ \______
 *
 *     ------\                    /-------
 * R/W        \                  /
 *             \________________/
 *
 *             /-------\          /-------
 * E          /  175ns  \        /
 *     ______/           \______/
 *
 *                   /-------\
 * DB0-DB7          /         \
 *     ____________/           \__________
 *
 */
void CharLCD_WriteRegister(u16 index,u16 data)
{

}

void CharLCD_SetCursor(u16 line,u16 column)
{

}

void CharLCD_Clear(void)
{
	CharLCD_WriteData(0x01);
}

void CharLCD_Delay(int Count)
{
	while(Count--)
	{
	}
}

void CharLCD_Test(void)
{

}

void CharLCD_WriteData(u16 data)
{
	GPIOE->ODR=((GPIOE->ODR & 0xF00F) | (data << 4));
}

void CharLCD_WriteIndex(u16 index)
{

}

void CharLCD_Backlight(u16 status)
{

}
/*
u16 CharLCD_ReadData(void)
{

}

u16 CharLCD_ReadRegister(u16 index)
{

}
*/
