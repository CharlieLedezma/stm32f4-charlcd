/*
 * main.c
 *
 * STM32F4 Character LCD demo, by: Tom McLeod
 *
 * This code is used to test a character LCD interface with the STM32F4.
 *
 * If you end up using this code please let me know!
 *
 * THIS CODE IS PROVIDED AS IS, WITH NO WARRANTY. Please see the LICENSE file 
 * in the projects root directory for more info.
 *
 */ 

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "charlcd.h"

GPIO_InitTypeDef  GPIO_InitStructure;

void delay(float time);

int main(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);		// Start clock on GPIOD

	// This configures the Discovery LED pins D(12-15)
	// 12 = green/left
	// 13 = orange/top
	// 14 = red/right
	// 15 = blue/bottom
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	CharLCD_Config();
	CharLCD_Init();
	//CharLCD_Clear();

	// Enable FPU :D
	// Not really used in this case, but doesn't hurt and proves that it works to 
	// some degree.
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));

	/*CharLCD_SetCursor(1,1);
	CharLCD_WriteLineNoWrap("Hello World!");
	CharLCD_SetCursor(2,1);
	CharLCD_WriteLineNoWrap("STM32F4 example by:");
	CharLCD_SetCursor(3,1);
	CharLCD_WriteLineNoWrap("Tom McLeod");
	CharLCD_SetCursor(4,1);
	CharLCD_WriteLineNoWrap("!@#$%^&*()");*/
	CharLCD_Test();

  while (1)
  {
		GPIO_SetBits(GPIOD,GPIO_Pin_12);	// Turn on green
    
		delay(0xFFFFF); 
		
		GPIO_SetBits(GPIOD,GPIO_Pin_13);	// Turn on orange 
		
		delay(0xFFFFF); 
		
		GPIO_SetBits(GPIOD,GPIO_Pin_14);	// Turn on red 
		
		delay(0xFFFFF); 
		
		GPIO_SetBits(GPIOD,GPIO_Pin_15);	// Turn on blue 
		
		delay(0xFFFFF); 
		
		// Turn all off
		GPIO_ResetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15); 
		
		delay(0xFFFFF);
  }
}

void delay(float time) 
{
	while(time--)
	{
	}
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ 
  while (1)
  {
  }
}
#endif

