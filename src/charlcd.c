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

u8 CharLCD_line = 1;
u8 CharLCD_column = 1;

void CharLCD_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	// Open the clocks we want
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,ENABLE);

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
	CharLCD_WriteData(0x00);
	Set_RS;
	Set_RW;
	Set_Clk;

	CharLCD_Delay(0xFFFF);

	Clr_RS;
	Clr_RW;
	Clr_Clk;

	// 8-bit, 2-line (4-line displays use 2-lines with more characters per line)
	if(Num_Lines > 1)
	{
		CharLCD_WriteData(0x38);
	}else if(Num_Lines == 1)
	{
		CharLCD_WriteData(0x30);
	}
	// Turn display on, with cursor on and blinking
	CharLCD_WriteData(0x0F);

	CharLCD_Clear();
	// increment left, no screen shift
	CharLCD_WriteData(0x06);

	CharLCD_Delay(0xFFF);
}

void CharLCD_WriteLineWrap(const char* string) 
{
	char line[(Num_Characters + 1)];

	u8 i,j,k,l;
	k = 0;
	l = 0;
	for(j = CharLCD_line;j <= Num_Lines;j++){
		for(i = CharLCD_column;i <= Num_Characters;i++){
			line[l] = string[k];
			if(line[l] == '\0') {
				CharLCD_WriteString(line);
				return;
			}
			k++;
			l++;
		}
		line[l] = '\0';
		CharLCD_WriteString(line);
		CharLCD_SetCursor(j+1,1);
		l = 0;
	}
}

void CharLCD_WriteLineNoWrap(const char* string) 
{
	char line[(Num_Characters + 1)];

	u8 i,j;
	j = 0;
	for(i = CharLCD_column;i <= Num_Characters;i++){
		line[j] = string[j];
		j++;
	}
	line[j] = '\0';

	CharLCD_WriteString(line);
}

void CharLCD_WriteString(const char* line) 
{
	int i;
	Set_RS;
	for(i = 0;i < 80;i++){
		if(line[i] == '\0' || !line[i]){
			return;
		}else {
			CharLCD_WriteData((int)line[i]);
		}
	}
	Clr_RS;
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
void CharLCD_SetCursor(u8 line,u8 column)
{
	CharLCD_line = line;
	CharLCD_column = column;
	
	Clr_RS;
	Clr_RW;
	u8 position;
	
	switch(line) {
		case 1:
			position = column - 0x01;
			break;
		case 2:
			position = column + 0x3F;
			break;
		case 3:
			position = column + 0x13;
			break;
		case 4:
			position = column + 0x53;
			break;
		default:
			break;
	}

	CharLCD_WriteData(position | 0x80);
}

void CharLCD_Clear(void)
{
	Clr_RS;
	Clr_RW;
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
	int i;
	Set_RS;
	for(i = 33;i < 33+(Num_Characters*Num_Lines);i++){
		CharLCD_WriteData(i);
	}
}

void CharLCD_WriteData(u8 data)
{
	GPIOE->ODR=((GPIOE->ODR & 0xF00F) | (data << 4));

	Set_Clk;

	CharLCD_Delay(0xFF);

	Clr_Clk;

	CharLCD_Delay(0xFF);

	GPIOE->ODR=((GPIOE->ODR & 0xF00F));
}

void CharLCD_Backlight(u8 status)
{
	if(status)
	{
		Backlight_On;
	}else
	{
		Backlight_Off;
	}
}

