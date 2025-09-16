/*
 * Printf_debug_l4p5.c
 *
 *  Created on: Aug 14, 2025
 *      Author: prath
 */


#include <stdio.h>
#include <stdint.h>
#include <stm32l4xx.h>
#include "Printf_debug_l4p5.h"


void USART2_INIT(void);
void USART2_WriteChar(char c);
void USART2_WriteString(const char *str);

void USART2_INIT(void){

	RCC->AHB2ENR |= (1 << 6);

	RCC->APB1ENR2 |= (1 << 0);

	GPIOG->MODER &= ~(0xF << 14);
	GPIOG->MODER |= (0xA << 14);

	GPIOG->AFR[0] &= ~(0xF << 28);
	GPIOG->AFR[0] |= (0x8 << 28);

	GPIOG->AFR[1] &= ~(0xF << 0);
	GPIOG->AFR[1] |= (0x8 << 0);

	RCC->CCIPR &= ~(0b11 << 10);
	RCC->CCIPR |= (0b01 << 10);

	LPUART1->CR1 &= ~(1 << 0);

	LPUART1->BRR = 0x27100;

	LPUART1->CR1 |= (0b11 << 2);
	LPUART1->CR1 |= (1 << 0);
}


void USART2_WriteChar(char c)
{
    while (!(LPUART1->ISR & (1 << 7))); // Wait until TXE
    LPUART1->TDR = c;
}

void USART2_WriteString(const char *str)
{
    while (*str)
    {
        USART2_WriteChar(*str++);
    }
}
