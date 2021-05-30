/*
 * boppit_game_timer.c
 *
 *  Created on: May 31, 2021
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

Basic_tim_handler_t Tim6;

uint32_t count = 600000;
uint8_t check = 0;

void LED_configuration();
void Button_configuration();
void TIM6_init();
void delay();
void Blink();
void button_check();
void button_check_main();
void LED_loop();
int main(void)
{
	LED_configuration();
	Button_configuration();
	TIM6_PCLK_EN();
	TIM6_init();
	Ba_tim_init(&Tim6,TIM_COUNTER_EN);
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
	while(!(TIM6->SR & 1));
	TIM6->SR = 0;
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx, GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx, GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, SET);
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	while(!(TIM6->SR & 1));
	TIM6->SR = 0;
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx, GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_green.pGPIOx, GPIO_led_green.GPIO_PinConfig.GPIO_PinNumber, SET);
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	while(!(TIM6->SR & 1));
	TIM6->SR = 0;
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	GPIO_WriteToOutputPin(GPIO_led_green.pGPIOx, GPIO_led_green.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_red.pGPIOx, GPIO_led_red.GPIO_PinConfig.GPIO_PinNumber, SET);
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	while(!(TIM6->SR & 1));
	TIM6->SR = 0;
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	GPIO_WriteToOutputPin(GPIO_led_red.pGPIOx, GPIO_led_red.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_yellow.pGPIOx, GPIO_led_yellow.GPIO_PinConfig.GPIO_PinNumber, SET);
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	while(!(TIM6->SR & 1));
	TIM6->SR = 0;
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	GPIO_WriteToOutputPin(GPIO_led_yellow.pGPIOx, GPIO_led_yellow.GPIO_PinConfig.GPIO_PinNumber, RESET);
	GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx, GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, SET);
	button_check_main();
	if(check == 1)
	{
		check = 0;
		goto end;
	}
	else check = 0;
	end:
	do{}while(0);
}

void button_check_main()
{
	if(GPIO_ReadFromInputPin(GPIO_button.pGPIOx, GPIO_button.GPIO_PinConfig.GPIO_PinNumber)==1)
		{
			delay(270000);
			if(GPIO_led_white_left.pGPIOx->ODR == 1 || GPIO_led_white_left.pGPIOx->ODR == 16)
			{
				TIM6->ARR = 62500-1;
				GPIO_WriteToOutputPin(GPIO_led_white_left.pGPIOx,GPIO_led_white_left.GPIO_PinConfig.GPIO_PinNumber, RESET);
				GPIO_WriteToOutputPin(GPIO_led_white_right.pGPIOx,GPIO_led_white_right.GPIO_PinConfig.GPIO_PinNumber, RESET);
				check = 1;
			}
			button_check();
		}
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
		//Tim6.pba_tim_config.Period = 9000;
		TIM6->ARR -= 10000;
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

void TIM6_init()
{
	Tim6.pba_tim = TIM6;
	Tim6.pba_tim_config.Period = 62500-1;
	Tim6.pba_tim_config.Prescaler = 256;
}

void delay(uint32_t value)
{
	for(uint32_t i = 0; i < value; i++)
	{

	}
}



