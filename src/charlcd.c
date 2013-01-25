/*
 * Host write timing diagram:
 *     ------\ /-----------------\ /------
 * RS (low if X writing register, X low if not)
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

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "charlcd.h"

void CharLCD_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Open the clock we want
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE,ENABLE);

	// Configure the LCD pins for push-pull output
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	// Control pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}

void CharLCD_Init(void)
{
	Clr_RS;
	Clr_RW;
	Clr_Clk;
}

void CharLCD_Reset(void)
{

}

void CharLCD_WriteRegister(u16 index,u16 data)
{

}

void CharLCD_SetCursor(u16 line,u16 column)
{

}

void CharLCD_Clear(void)
{
	GPIOE->ODR=((GPIOE->ODR&0xFF00) | (1 << 4));
}

void CharLCD_Delay(u32 Count)
{

}

void CharLCD_Test(void)
{

}

void CharLCD_WriteData(u16 data)
{

}

void CharLCD_WriteIndex(u16 index)
{

}

void CharLCD_Backlight(u16 status)
{

}

u16 CharLCD_ReadData(void)
{

}

u16 CharLCD_ReadRegister(u16 index)
{

}

