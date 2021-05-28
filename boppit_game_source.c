/*
 * boppit_game_2.c
 *
 *  Created on: May 29, 2021
 *      Author: Minh Long Nguyen
 */

/*
 * boppit_game.c
 *
 *  Created on: May 28, 2021
 *      Author: Minh Long Nguyen
 */

#include "stm32f4xx.h"
#include <stdio.h>
#include <string.h>

GPIO_Handler_t GPIO_led_red;
GPIO_Handler_t GPIO_led_green;
GPIO_Handler_t GPIO_led_yellow;
GPIO_Handler_t GPIO_led_white_left;
GPIO_Handler_t GPIO_led_white_right;

GPIO_Handler_t GPIO_button;

uint32_t count = 600000;

void LED_configuration();
void Button_configuration();
void delay();
void Blink();
void button_check();
void LED_loop();
int main(void)
{
	LED_configuration();
	Button_configuration();
	while(1)
	{
		LED_loop();
	}
}

void LED_configuration()
{
	GPIO_led_white_left.pGPIOx = GPIOA;
	GPIO_led_green.pGPIOx = GPIOA;
	GPIO_led_red.pGPIOx = GPIOA;
	GPIO_led_yellow.pGPIOx = GPIOA;
	GPIO_led_white_right.pGPIOx = GPIOA;

	GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber = GPIO_NO_0;
	GPIO_led_green.GPIO_PinConfig.GPIO_PinNumber = GPIO_NO_1;
	GPIO_led_red.GPIO_PinConfig.GPIO_PinNumber = GPIO_NO_2;
	GPIO_led_yellow.GPIO_PinConfig.GPIO_PinNumber = GPIO_NO_3;
	GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber = GPIO_NO_4;

	GPIO_led_white_left.GPIO_PinConfig.GPIO_PinMode = GPIO_ModeOUT;
	GPIO_led_green.GPIO_PinConfig.GPIO_PinMode = GPIO_ModeOUT;
	GPIO_led_red.GPIO_PinConfig.GPIO_PinMode = GPIO_ModeOUT;
	GPIO_led_yellow.GPIO_PinConfig.GPIO_PinMode = GPIO_ModeOUT;
	GPIO_led_white_right.GPIO_PinConfig.GPIO_PinMode = GPIO_ModeOUT;

	GPIO_led_white_left.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GPIO_led_green.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GPIO_led_red.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GPIO_led_yellow.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;
	GPIO_led_white_right.GPIO_PinConfig.GPIO_PinOType = GPIO_OP_TYPE_PP;

	GPIO_led_white_left.GPIO_PinConfig.GPIO_PinPuPd = DR_GPIO_PUPD_NONE;
	GPIO_led_green.GPIO_PinConfig.GPIO_PinPuPd = DR_GPIO_PUPD_NONE;
	GPIO_led_red.GPIO_PinConfig.GPIO_PinPuPd = DR_GPIO_PUPD_NONE;
	GPIO_led_yellow.GPIO_PinConfig.GPIO_PinPuPd = DR_GPIO_PUPD_NONE;
	GPIO_led_white_right.GPIO_PinConfig.GPIO_PinPuPd = DR_GPIO_PUPD_NONE;

	GPIO_led_white_left.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_H;
	GPIO_led_green.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_H;
	GPIO_led_red.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_H;
	GPIO_led_yellow.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_H;
	GPIO_led_white_right.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_H;

	GPIOA_PCLK_EN();

	GPIO_Init(&GPIO_led_white_right);
	GPIO_Init(&GPIO_led_yellow);
	GPIO_Init(&GPIO_led_red);
	GPIO_Init(&GPIO_led_green);
	GPIO_Init(&GPIO_led_white_left);
}

void Button_configuration()
{
	GPIO_button.pGPIOx = GPIOD;
	GPIO_button.GPIO_PinConfig.GPIO_PinNumber = GPIO_NO_1;
	GPIO_button.GPIO_PinConfig.GPIO_PinMode = GPIO_ModeIN;
	GPIO_button.GPIO_PinConfig.GPIO_PinPuPd = DR_GPIO_PUPD_PD;
	GPIO_button.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OP_SPEED_H;

	GPIOD_PCLK_EN();

	GPIO_Init(&GPIO_button);
}


void Blink()
{
	GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx, GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, SET);
	GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx, GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, SET);
	GPIO_WriteToOutputPin(GPIO_led_green.pGPIOx, GPIO_led_green.GPIO_PinConfig.GPIO_PinNumber, SET);
	GPIO_WriteToOutputPin(GPIO_led_red.pGPIOx, GPIO_led_red.GPIO_PinConfig.GPIO_PinNumber, SET);
	GPIO_WriteToOutputPin(GPIO_led_yellow.pGPIOx, GPIO_led_yellow.GPIO_PinConfig.GPIO_PinNumber, SET);
}

void LED_loop()
{
	GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx, GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx, GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, SET);
	if(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
			{
				delay(270000);
				if(GPIO_led_white_left.pGPIOx->ODR == 1 || GPIO_led_white_left.pGPIOx->ODR == 16)
				{
					count = 600000;
					GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx,GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
					GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx,GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
					goto end;
				}
				button_check();
			}
	delay(count);
	GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx, GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_green.pGPIOx, GPIO_led_green.GPIO_PinConfig.GPIO_PinNumber, SET);
	if(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
			{
				delay(270000);
				if(GPIO_led_white_left.pGPIOx->ODR == 1 || GPIO_led_white_left.pGPIOx->ODR == 16)
				{
					count = 600000;
					GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx,GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
					GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx,GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
					goto end;
				}
				button_check();
			}
	delay(count);
	GPIO_WriteToOutputPin(GPIO_led_green.pGPIOx, GPIO_led_green.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_red.pGPIOx, GPIO_led_red.GPIO_PinConfig.GPIO_PinNumber, SET);
	if(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
			{
				delay(270000);
				if(GPIO_led_white_left.pGPIOx->ODR == 1 || GPIO_led_white_left.pGPIOx->ODR == 16)
				{
					count = 600000;
					GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx,GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
					GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx,GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
					goto end;
				}
				button_check();
			}
	delay(count);
	GPIO_WriteToOutputPin(GPIO_led_red.pGPIOx, GPIO_led_red.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_yellow.pGPIOx, GPIO_led_yellow.GPIO_PinConfig.GPIO_PinNumber, SET);
	if(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
			{
				delay(270000);
				if(GPIO_led_white_left.pGPIOx->ODR == 1 || GPIO_led_white_left.pGPIOx->ODR == 16)
				{
					count = 600000;
					GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx,GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
					GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx,GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
					goto end;
				}
				button_check();
			}
	delay(count);
	GPIO_WriteToOutputPin(GPIO_led_yellow.pGPIOx, GPIO_led_yellow.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx, GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, SET);
	if(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
			{
				delay(270000);
				if(GPIO_led_white_left.pGPIOx->ODR == 1 || GPIO_led_white_left.pGPIOx->ODR == 16)
				{
					count = 600000;
					GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx,GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
					GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx,GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
					goto end;
				}
				button_check();
			}
	delay(count);
	end:
	do{}while(0);
}

void button_check()
{
	if(GPIO_led_green.pGPIOx->ODR == 2)
	{
		while(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
		{

		}
		goto end;
	}
	else if(GPIO_led_red.pGPIOx->ODR == 4)
	{
		count -= 100000;
		goto end;
	}
	else if(GPIO_led_yellow.pGPIOx->ODR == 8)
	{
		while(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
		{

		}
		goto end;
	}
	end:
	do{}while(0);
}


void delay(uint32_t value)
{
	for(uint32_t i = 0; i < value; i++)
	{

	}
}








