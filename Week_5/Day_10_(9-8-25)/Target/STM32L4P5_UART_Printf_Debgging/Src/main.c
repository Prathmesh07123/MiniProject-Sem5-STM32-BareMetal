

#include <stdint.h>
#include <stm32l4xx.h>
#include "Printf_debug_l4p5.h"

void clock_init(void){

	RCC->CR |= (1 << 8);

	while(!(RCC->CR & (1 << 10)));

	FLASH->ACR |= (3 << 0);
	FLASH->ACR |= (1 << 8);
	FLASH->ACR |= (1 << 9);
	FLASH->ACR |= (1 << 10);


	RCC->PLLCFGR = 0;
	RCC->PLLCFGR |= (0b10 << 0);
	RCC->PLLCFGR |= (0x1 << 4);
	RCC->PLLCFGR |= (18 << 8);
	RCC->PLLCFGR |= (0b00 << 25);
	RCC->PLLCFGR |= (1 << 24);

	RCC->CR |= (1 << 24);
	while(!(RCC->CR & (1 << 25)));

	RCC->CFGR &= ~(0b11 << 0);
	RCC->CFGR |= (0b11 << 0);
	while((RCC->CFGR & (0b11 << 2)) != (0b11 << 2));

	RCC->CFGR &= ~(0xF << 4);
	RCC->CFGR &= ~(0b111 << 8);
	RCC->CFGR &= ~(0b111 << 11);

}

void Systick_delay_ms(int delay){

	SysTick->LOAD = 71999;

	SysTick->VAL = 0;

	SysTick->CTRL |= (1 << 2);
	SysTick->CTRL |= (1 << 0);

	for(int i = 0; i < delay; i++){
		while(!(SysTick->CTRL & (1 << 16)));
	}

}

int main(void)
{
	clock_init();
	USART2_INIT();

	while(1){

		USART2_WriteString("Hello World!!!!");
		for (volatile int i = 0; i < 500000; i++);
	}


}
