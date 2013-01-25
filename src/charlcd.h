/* 
 * See pinout.txt in the root directory of this project for the
 * LCD pinout.
 */

#ifndef __CHARLCD_H__
#define __CHARLCD_H__

// Device Defines (set these for your device!)
#define Num_Lines 4
#define Num_Characters 20  // Per line

#define Set_RS GPIO_SetBits(GPIOD,GPIO_Pin_7)
#define Clr_RS GPIO_ResetBits(GPIOD,GPIO_Pin_8)

#define Set_RW GPIO_SetBits(GPIOD,GPIO_Pin_8)
#define Clr_RW GPIO_ResetBits(GPIOD,GPIO_Pin_8)

#define Set_Clk GPIO_SetBits(GPIOD,GPIO_Pin_9)
#define Clr_Clk GPIO_ResetBits(GPIOD,GPIO_Pin_9)

// May use pwm and a transistor on the 5V rail in the final version
#define Backlight_On GPIO_SetBits(GPIOD,GPIO_Pin_10)
#define Backlight_Off GPIO_ResetBits(GPIOD,GPIO_Pin_10)

void CharLCD_Config(void);
void CharLCD_Init(void);
void CharLCD_Reset(void);
void CharLCD_WriteRegister(u16 index,u16 data);
void CharLCD_SetCursor(u16 line,u16 column);
void CharLCD_Clear(void);
void CharLCD_Delay(u32 Count);
void CharLCD_Test(void);
void CharLCD_WriteData(u16 data);
void CharLCD_WriteIndex(u16 index);
void CharLCD_Backlight(u16 status);

u16 CharLCD_ReadData(void);
u16 CharLCD_ReadRegister(u16 index);

#endif // endif for __CHARLCD_H__
